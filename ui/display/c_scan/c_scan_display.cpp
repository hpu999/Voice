#include "c_scan_display.h"
#include "c_scan_encoder_image_item.h"
#include "c_scan_time_image_item.h"
#include "c_scan_scene.h"

#include "../base_image_item.h"
#include "../scan_view.h"
#include "../color_bar.h"
#include "../ruler/ruler.h"

#include <device/device.h>
#include <source/axis.h>
#include <source/scan.h>
#include <source/source.h>

#include <QLabel>

CscanDisplay::CscanDisplay(const DplDevice::GroupPointer &grp, Qt::Orientation orientation, QWidget *parent) : ScanDisplay(parent),
    m_group(grp),
    m_view(new ScanView),
    m_scene(new CscanScene),
    m_orientation(orientation),
    m_cscanImageItem(NULL)
{
    m_scanLayout->addWidget(m_view);
    m_view->setScene(m_scene);

    init_scan_env();
    init_ruler();

    connect(m_view, SIGNAL(size_changed(QSize)),
            this, SLOT(do_view_size_changed(QSize)));

    m_colorBar->set_palette(DplDevice::Device::instance()->display()->palette());
    m_titleLabel->setText(QString("C-Scan|Grp%1").arg(m_group->index()+1));

    if(m_orientation == Qt::Horizontal) {
        m_view->rotate(-90);
    }

    /* source setting */
    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this, SLOT(do_data_event(DplSource::BeamsPointer)),
            Qt::DirectConnection);

    connect(this, SIGNAL(refresh_scan_env()), this, SLOT(do_refresh_scan_env()));
    connect(this, SIGNAL(update_ruler(double)), this, SLOT(do_update_ruler(double)));
}


CscanDisplay::~CscanDisplay()
{
    disconnect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this, SLOT(do_data_event(DplSource::BeamsPointer)));

    disconnect(this, SIGNAL(refresh_scan_env()), this, SLOT(do_refresh_scan_env()));
    disconnect(this, SIGNAL(update_ruler(double)), this, SLOT(do_update_ruler(double)));

    delete m_view;
    delete m_scene;

    m_view = NULL;
    m_scene = NULL;
}


void CscanDisplay::do_data_event(const DplSource::BeamsPointer &beams)
{
    if(m_scene == NULL
            || m_view == NULL) {
        return;
    }

    if(m_scene->width() == 0
            || m_scene->height() == 0) {
        qDebug("[%s] w/h is 0.", __FUNCTION__);
        return;
    }

    if(beams.isNull()) {
        qDebug("[%s] beams is NULL.", __FUNCTION__);
        return;
    }

    DplFocallaw::ProbePointer probe = m_group->focallawer()->probe();
    if((!probe.isNull()) && probe->is_pa()) {
        DplFocallaw::PaProbePointer paProbe = probe.staticCast<DplFocallaw::PaProbe>();
        m_scanCnfPointer = paProbe->scan_configure();
    }

    if(m_cscanImageItem->need_refresh(beams) || focallaw_mode_changed()) {
        emit refresh_scan_env();
        wait_for_refresh_finished();
    }

    if(m_cscanImageItem->driving() == DplSource::Axis::TIMER) {
        draw_timer_beams(beams);
    } else {
        draw_encoder_beams(beams);
    }
}


void CscanDisplay::init_ruler()
{
    if(m_orientation == Qt::Vertical) {
        m_scanTypeRuler = m_bottomRuler;
        m_lawTypeRuler  = m_leftRuler;
    } else {
        m_scanTypeRuler = m_leftRuler;
        m_lawTypeRuler  = m_bottomRuler;
    }

    m_rightRuler->set_range(100, 0);
    m_rightRuler->set_unit("(%)");
}


void CscanDisplay::update_scan_type_ruler(const QSize &size)
{
    if(m_scanTypeRuler == NULL) {
        return;
    }

    if(m_cscanImageItem->driving() == DplSource::Axis::ENCODER_X
           || m_cscanImageItem->driving() == DplSource::Axis::ENCODER_Y) {

        /* 扫查轴 */
        /* 根据scan start/end 及resolution（扫查分辨率）计算待显示的总beam数 */

        double scanStart        = DplSource::Scan::instance()->scan_axis()->start();
        double scanEnd          = DplSource::Scan::instance()->scan_axis()->end();
        double scanResolution   = DplSource::Scan::instance()->scan_axis()->resolution();

        double beamCount = (scanEnd - scanStart) / scanResolution;

        int width;
        if(m_orientation == Qt::Horizontal) {
            width = size.height();
        } else {
            width = size.width();
        }

        if(width >= beamCount) {
            /* 若显示区域大于beam数，则计算每条beam占多少pix */
            double pixCount = width / beamCount;
            m_scanTypeRuler->set_range(scanStart, scanEnd);
            m_cscanImageItem->set_pix_per_beam(pixCount);
            m_cscanImageItem->set_scroll_window(false);
            m_scanTypeRuler->set_range(scanStart, scanEnd);

        } else {
            /* 若显示区域小于beam数，则计算每条beam占一个pix */
            m_scanTypeRuler->set_range(scanStart, scanStart + width);
            m_cscanImageItem->set_pix_per_beam(DEFAULT_PIX_PER_BEAM);
            m_cscanImageItem->set_scroll_window(true);
            m_scanTypeRuler->set_range(scanStart, scanStart + width);
        }

        m_scanTypeRuler->set_unit("(mm)");

    } else {

        double scanTypeRulerEnd;

        double beamQtyPerSecond = SECOND / (double)DplSource::Source::instance()->interval();

        if(m_orientation == Qt::Horizontal) {
            scanTypeRulerEnd = size.height() / beamQtyPerSecond;
        } else {
            scanTypeRulerEnd = size.width() / beamQtyPerSecond;
        }

        m_scanTypeRuler->set_range(0.0, scanTypeRulerEnd);
        m_scanTypeRuler->set_unit("(s)");
    }

    m_scanTypeRuler->update();
}


void CscanDisplay::update_law_type_ruler()
{
    const DplFocallaw::ProbePointer &probe = m_group->focallawer()->probe();

    if(!probe->is_pa()) {
        return;
    }

    DplFocallaw::PaProbePointer paProbe = probe.staticCast<DplFocallaw::PaProbe>();

    if(paProbe.isNull()) {
        return;
    }

    if(paProbe->scan_configure()->mode() == DplFocallaw::ScanCnf::Linear) {
        /* 线扫 */
        m_lawTypeRuler->set_range(0.0, m_group->focallawer()->beam_qty());
        m_lawTypeRuler->set_unit("(VPA)");

    } else {
        /* 扇扫 */
        /* 获取起始角度、终止角度 */

         DplFocallaw::SectorialScanCnfPointer sectorialScanCnf =
                 paProbe->scan_configure().staticCast<DplFocallaw::SectorialScanCnf>();

         if(sectorialScanCnf.isNull()) {
            return;
         }

         double startAngle = sectorialScanCnf->first_angle();
         double lastAngle  = sectorialScanCnf->last_angle();

         m_lawTypeRuler->set_range(startAngle, lastAngle);
         m_lawTypeRuler->set_unit("(°)");
    }

    m_lawTypeRuler->update();
}


void CscanDisplay::wait_for_refresh_finished()
{
    m_refreshSemaphore.acquire(m_refreshSemaphore.available() + 1);
}


void CscanDisplay::do_refresh_scan_env()
{
    init_scan_env();

    update_scan_type_ruler(m_view->size());

    update_law_type_ruler();

    m_refreshSemaphore.release();
}


void CscanDisplay::do_view_size_changed(const QSize &size)
{
    disconnect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this, SLOT(do_data_event(DplSource::BeamsPointer)));

    if (m_orientation == Qt::Vertical) {

        m_scene->setSceneRect(-size.width()/2.0, -size.height()/2.0,
                          size.width(), size.height());
        m_cscanImageItem->set_size(size);

    } else {

        m_scene->setSceneRect(-size.height()/2.0, -size.width()/2.0,
                                   size.height(), size.width());
        m_cscanImageItem->set_size(QSize(size.height(), size.width()));
    }

    update_scan_type_ruler(size);

    update();

    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this, SLOT(do_data_event(DplSource::BeamsPointer)),
            Qt::DirectConnection);
}


void CscanDisplay::do_update_ruler(double value)
{
    if(m_scanTypeRuler == NULL) {
        return;
    }

    m_scanTypeRuler->update();
}


void CscanDisplay::init_scan_env()
{
    if(m_cscanImageItem != NULL) {
        m_scene->removeItem(m_cscanImageItem);
        delete m_cscanImageItem;
        m_cscanImageItem = NULL;
    }

    if(DplSource::Scan::instance()->scan_axis()->driving() == DplSource::Axis::TIMER) {
        m_cscanImageItem = new CscanTimeImageItem(DplDevice::Device::instance()->display()->palette(), m_group);
    } else {
        m_cscanImageItem = new CscanEncoderImageItem(DplDevice::Device::instance()->display()->palette(), m_group);
    }

    m_scene->addItem(m_cscanImageItem);

    if (m_orientation == Qt::Horizontal) {
        m_cscanImageItem->set_size(QSize(m_view->height(), m_view->width()));
    } else {
        m_cscanImageItem->set_size(m_view->size());
    }
}


bool CscanDisplay::focallaw_mode_changed()
{
    if(m_scanCnfPointer->mode() == m_focallawMode) {
        m_focallawMode = m_scanCnfPointer->mode();
        return false;
    }

    m_focallawMode = m_scanCnfPointer->mode();
    return true;
}


void CscanDisplay::draw_timer_beams(const DplSource::BeamsPointer &beams)
{
    double currentTimeCount = TestStub::instance()->get_time();
    DplSource::Scan *scan = DplSource::Scan::instance();
    DplSource::AxisPointer axis = scan->scan_axis();
    double timeWidth = (axis->end() - axis->start()) / scan->speed();

    if(currentTimeCount > timeWidth) {
        return;
    }


    double rulerEnd;
    if(m_orientation == Qt::Horizontal) {
        rulerEnd = m_view->height() / (SECOND / (double)DplSource::Source::instance()->interval());
    } else {
        rulerEnd = m_view->width() / (SECOND / (double)DplSource::Source::instance()->interval());
    }

    if(!m_cscanImageItem->redraw_beams(beams)) {
        m_cscanImageItem->set_beams(beams);
    }

    if(rulerEnd < timeWidth && currentTimeCount > rulerEnd) {
        m_cscanImageItem->set_scroll_window(true);
        emit update_ruler(currentTimeCount);
    }
}


void CscanDisplay::draw_encoder_beams(const DplSource::BeamsPointer &beams)
{
    if(m_cscanImageItem->redraw_beams(beams)) {

        CscanEncoderImageItem *imageItem = static_cast<CscanEncoderImageItem*> (m_cscanImageItem);
        if(imageItem) {
            m_scanTypeRuler->set_range(imageItem->show_start(), imageItem->show_end());
        }
    }

    double x;

    if(DplSource::Scan::instance()->scan_axis()->driving() == DplSource::Axis::ENCODER_X) {
        x = ((int)((beams->get(0)->encoder_x() / DplSource::Scan::instance()->encoder_x()->resolution() + 0.005) * 100)) / 100.0; /* 保留小数点两位 */
    } else {
        x = ((int)((beams->get(0)->encoder_y() / DplSource::Scan::instance()->encoder_y()->resolution() + 0.005) * 100)) / 100.0; /* 保留小数点两位 */
    }

    m_cscanImageItem->set_beams(beams);
    emit update_ruler(x);
}
