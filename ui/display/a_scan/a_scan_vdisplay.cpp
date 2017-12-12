/**
 * @file a_scan_vdisplay.cpp
 * @brief A扫纵向布局
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-19
 */
#include "a_scan_vdisplay.h"

#include "a_scan_scene.h"
#include "wave_item.h"
#include "tcg_item.h"

AscanVDisplay::AscanVDisplay(const DplDevice::GroupPointer &group, QWidget *parent) :
    AscanDisplay(group, parent)
{  
    m_view->rotate(90);
}

Ruler *AscanVDisplay::amplitude_ruler()
{
    return m_bottomRuler;
}

Ruler *AscanVDisplay::ultrasound_ruler()
{
    return m_leftRuler;
}

void AscanVDisplay::resize_event(const QSize &size)
{
    m_scene->setSceneRect(-size.height()/2, -size.width()/2 + 1,
                               size.height(), size.width());
    m_waveItem->set_size(QSize(size.height(), size.width()));
    m_tcgItem->set_size(QSize(size.height(), size.width()));

    AscanDisplay::resize_event(size);
}
