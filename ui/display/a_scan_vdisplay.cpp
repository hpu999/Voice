/**
 * @file a_scan_vdisplay.cpp
 * @brief A扫纵向布局
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-19
 */
#include "global.h"
#include "a_scan_vdisplay.h"
#include "ui_a_scan_display.h"

#include <qmath.h>

#include <QDebug>

AscanVDisplay::AscanVDisplay(const DplDevice::GroupPointer &group,
                             QWidget *parent) :
    AscanDisplay(group, Qt::Vertical, parent)
{  
    /* ruler setting */
    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
            this,
            SLOT(update_left_ruler()));
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(start_changed(float)),
            this,
            SLOT(update_left_ruler()));
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(range_changed(float)),
            this,
            SLOT(update_left_ruler()));
    update_left_ruler();

    ui->bottomRulerWidget->set_range(0, 100);
    ui->bottomRulerWidget->set_unit("(%)");
    ui->bottomRulerWidget->set_backgroup_color(QColor("#ffff7f"));
}

AscanVDisplay::~AscanVDisplay()
{
}

void AscanVDisplay::update_left_ruler()
{
    double start = m_group->sample()->start();
    double end = (start + m_group->sample()->range());

    qDebug("%s[%d]: start(%f) end(%f) precision(%f)",__func__, __LINE__, start, end, m_group->sample()->precision());

    start = Dpl::ns_to_us(start);
    end = Dpl::ns_to_us(end);

    DplDevice::Group::UtUnit unit = m_group->ut_unit();

    if (DplDevice::Group::Time == unit) {
        ui->leftRulerWidget->set_unit("(us)");
        ui->leftRulerWidget->set_backgroup_color(QColor("#F9CCE2"));
    } else{
        ui->leftRulerWidget->set_unit("(mm)");
        start *= m_group->sample()->velocity() * Dpl::m_to_mm(1) / Dpl::s_to_us(1);
        start /= 2;
        end   *= m_group->sample()->velocity() * Dpl::m_to_mm(1) / Dpl::s_to_us(1);
        end /= 2;
        ui->leftRulerWidget->set_backgroup_color(QColor("#f29cb1"));
        if (DplDevice::Group::TruePath == unit) {
            start *= qCos(m_group->current_angle());
            end   *= qCos(m_group->current_angle());
            ui->leftRulerWidget->set_backgroup_color(QColor("#ff00ff"));
        }
    }

    ui->leftRulerWidget->set_range(start, end);

    ui->leftRulerWidget->update();
}
