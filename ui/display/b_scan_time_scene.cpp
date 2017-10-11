#include "b_scan_time_scene.h"
#include <QDebug>
#include <QByteArray>

#include <source/source.h>
#include <device/device.h>
#include <source/beams.h>
#include <source/scan.h>

#include <ui/display/Tracer.h>


BscanTimeScene::BscanTimeScene(const DplDisplay::PaletteColorPointer &palette, int group, QObject *parent) :
    BscanScene(palette, group, parent)
{
    m_driving = DplSource::Axis::TIMER;
}

bool BscanTimeScene::need_refresh()
{
    if(BscanScene::need_refresh()) {
        return true;
    }
}


void BscanTimeScene::draw_vertical_beam()
{
    DEBUG_INIT("BscanTimeScene", __FUNCTION__);

    S_CommonProperties commonProperties;

    calculate_common_properties(commonProperties);

    const quint8 *waveData = (quint8 *) m_beamsPointer->raw_data();

    if(m_scrolling) {
        /* 整个显示区域画满beam，开始滚动显示后续的beam */
        scroll_vertical_image(commonProperties, waveData);
    } else {
        set_vertical_image_data(m_beamsShowedCount, commonProperties, waveData);
    }

    ++m_beamsShowedCount;
}


void BscanTimeScene::redraw_vertical_beam()
{
    DEBUG_INIT("BscanTimeScene", __FUNCTION__);

    if(!((m_beamsShowedCount > 0)
         && (!m_beamsPointer.isNull())
        && (m_image != NULL))) {
        return;
    }

    S_CommonProperties commonProperties;
    S_RedrawProperties redrawProperties;

    calculate_common_properties(commonProperties);
    calculate_redraw_properties(commonProperties, redrawProperties);

    DplSource::BeamsPointer tmp;
    int tmpBeamsShowedCount = 0;

    for(int i = 0; i < redrawProperties.redrawCount; ++i) {

        if(redrawProperties.beginShowIndex >= 0) {
            /* 顺序显示beams */
            tmp = DplSource::Source::instance()->beams(m_group, redrawProperties.beginShowIndex + i);

        } else {
            /*
             * ________________________________________________________
             * |__0__|__1__|____|____|____|.....  |__20__|__21__|__22__|
             * 以上为例子：
             * 当前帧为：1
             * 已显示帧数为：5
             * 则显示帧数顺序为：20、21、22、0、1
             */

            /* 从倒数第（totalFrameCount - lastIndex）个开始显示 */

            if(i < abs(redrawProperties.beginShowIndex)) {
                int index = redrawProperties.totalFrameCount + redrawProperties.beginShowIndex + i;
                tmp = DplSource::Source::instance()->beams(m_group, index);
            } else {
                tmp = DplSource::Source::instance()->beams(m_group, i - abs(redrawProperties.beginShowIndex));
            }
        }

        if(tmp.isNull()) {

            qDebug() << "[" << __FUNCTION__ << "]" << " BeamsPointer is NULL. tmpBeamsShowedCount = " << tmpBeamsShowedCount;
        }

        set_vertical_image_data(tmpBeamsShowedCount, commonProperties, (quint8 *)tmp->raw_data());

        ++tmpBeamsShowedCount;
    }

    m_beamsShowedCount = tmpBeamsShowedCount;

}