#include "b_scan_encoder_scene.h"
#include <QDebug>
#include <math.h>

#include <source/beams.h>
#include <source/source.h>
#include <source/scan.h>
#include <source/driving.h>
#include <fpga/fpga.h>

#include "Tracer.h"

BscanEncoderScene::BscanEncoderScene(const DplDisplay::PaletteColorPointer &palette,
                                     const DplDevice::GroupPointer &grp,
                                     QObject *parent) :
    EncoderScene(palette, grp, parent)
{
    set_driving(DplSource::Scan::instance()->scan_axis()->driving());
    init_encoder_properties();
    init_scan_properties();
}


bool BscanEncoderScene::need_refresh(const DplSource::BeamsPointer &beams)
{
    if(EncoderScene::need_refresh(beams)) {
        init_encoder_properties();
        init_scan_properties();
        return true;
    }

    /* 编码器参数改变，需要刷新 */
    if(m_encoder.mode() != m_encoderPointer->mode()
            || m_encoder.polarity() != m_encoderPointer->polarity()
            || (!is_equal(m_encoder.resolution(), m_encoderPointer->resolution()))
            || (!is_equal(m_encoder.origin(), m_encoderPointer->origin()))) {

        if(m_driving == DplSource::Axis::ENCODER_X) {
            m_encoderPointer = DplSource::Scan::instance()->encoder_x();
        } else if(m_driving == DplSource::Axis::ENCODER_Y) {
            m_encoderPointer = DplSource::Scan::instance()->encoder_y();
        }

        init_encoder_properties();
        init_scan_properties();
        return true;
    }

    /* 扫查参数改变，需要刷新 */
    if((!is_equal(m_axis.resolution(), DplSource::Scan::instance()->scan_axis()->resolution()))
            || (!is_equal(m_axis.start(), DplSource::Scan::instance()->scan_axis()->start()))
            || (!is_equal(m_axis.end(), DplSource::Scan::instance()->scan_axis()->end()))) {

        if(m_driving == DplSource::Axis::ENCODER_X) {
            m_encoderPointer = DplSource::Scan::instance()->encoder_x();
        } else if(m_driving == DplSource::Axis::ENCODER_Y) {
            m_encoderPointer = DplSource::Scan::instance()->encoder_y();
        }

        init_encoder_properties();
        init_scan_properties();

        return true;
    }

    return false;
}


void BscanEncoderScene::set_vertical_image_data(int beamsShowedCount, const BaseScanScene::S_CommonProperties &commonProperties, BaseScanScene::E_BEAM_TYPE type, const DplSource::BeamsPointer &beamsPointer)
{
    int pos = 0;
    for(int i = 0; i < m_image->height(); ++i) {

        quint8 *line    = (quint8*) m_image->scanLine(i);

        for(int j = 0; j < commonProperties.pixCount; ++j) {

            if(type == LAST_BEAM) {
                pos = m_image->width() - j - 1;
            } else {
                pos = (int)(beamsShowedCount * commonProperties.pixCount + j);
            }

            if(pos >= m_image->width() || pos < 0) {
                qDebug() << "[" << __FUNCTION__ << "]" << " last beam error pos = " << pos;
                continue;
            }

            line[pos] = beamsPointer->get(0)->wave().at((int)(i * commonProperties.ratio));
        }
    }
}


