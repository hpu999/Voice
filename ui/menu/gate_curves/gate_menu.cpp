/**
 * @file gate_menu.cpp
 * @brief gate menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "gate_menu.h"

#include <global.h>
#include <device/device.h>
#include <ui/tool/tool.h>
#include "ui_base_menu.h"

namespace DplGateCurvesMenu {

GateMenu::GateMenu(QWidget *parent) :
    BaseMenu(parent),
    m_gateItem(new ComboMenuItem(this, tr("Gate"))),
    m_switchItem(new ComboMenuItem(this, tr("Switch"))),
    m_paramsItem(new ComboMenuItem(this, tr("Parameters"))),
    m_startItem(new SpinMenuItem(this, tr("Start"))),
    m_widthItem(new SpinMenuItem(this, tr("Width"), "mm")),
    m_thresholdItem(new SpinMenuItem(this, tr("Threshold"), "%")),
    m_synchroItem(new ComboMenuItem(this, tr("Synchro"))),
    m_measureModeItem(new ComboMenuItem(this, tr("Measure"))),
    m_modeItem(new ComboMenuItem(this, tr("Mode")))
{
    ui->layout0->addWidget(m_gateItem);
    ui->layout1->addWidget(m_switchItem);
    ui->layout2->addWidget(m_paramsItem);
    ui->layout3->addWidget(m_startItem);
    ui->layout4->addWidget(m_widthItem);
    ui->layout5->addWidget(m_thresholdItem);
    ui->layout3->addWidget(m_synchroItem);
    ui->layout4->addWidget(m_measureModeItem);
    ui->layout5->addWidget(m_modeItem);

    m_gateItem->add_item(tr("A"));
    m_gateItem->add_item(tr("B"));
    m_gateItem->add_item(tr("I"));
    connect(m_gateItem, SIGNAL(value_changed(int)),
            this, SLOT(do_gateItem_changed(int)));

    m_switchItem->set(s_onOff);
    connect(m_switchItem, SIGNAL(value_changed(int)),
            this, SLOT(do_switchItem_changed(int)));

    m_paramsItem->add_item(tr("Position"));
    m_paramsItem->add_item(tr("Mode"));
    connect(m_paramsItem, SIGNAL(value_changed(int)),
            this, SLOT(do_paramsItem_changed(int)));

    m_startItem->set_decimals(2);
    m_startItem->set_step(0.01);
    connect(m_startItem, SIGNAL(value_changed(double)),
            this, SLOT(do_startItem_changed(double)));

    connect(m_widthItem, SIGNAL(value_changed(double)),
            this, SLOT(do_widthItem_changed(double)));

    m_thresholdItem->set(0, 100, 0);
    connect(m_thresholdItem, SIGNAL(value_changed(double)),
            this, SLOT(do_thresholdItem_changed(double)));

    m_measureModeItem->add_item(tr("Edge"));
    m_measureModeItem->add_item(tr("Peak"));
    connect(m_measureModeItem,
            SIGNAL(value_changed(int)),
            this,
            SLOT(do_measureModeItem_changed(int)));

    m_modeItem->add_item(tr("Sound Path"));
    m_modeItem->add_item(tr("Depth"));

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(update(DplDevice::GroupPointer)));
    update(DplDevice::Device::instance()->current_group());
    do_paramsItem_changed(0);
}

void GateMenu::update_items()
{
    update_switchItem();
    update_startItem();
    update_widhtItem();
    update_thresholdItem();
    update_synchroItem();
    update_measureModeItem();
}

void GateMenu::update_switchItem()
{
    m_switchItem->set_current_index(!m_gate->is_visible());
}

void GateMenu::update_startItem()
{
    if (m_group->ut_unit() == DplDevice::Group::Time) {
        m_startItem->set_unit(US_STR);
    } else {
        m_startItem->set_unit(MM_STR);
    }

    m_startItem->set_range(Tool::cnf_to_display(m_group, m_group->sample()->start()),
                           Tool::cnf_to_display(m_group, m_group->sample()->start()+m_group->sample()->range()));
    m_startItem->set_value(Tool::cnf_to_display(m_group, m_gate->start()));
}

void GateMenu::update_widhtItem()
{
    if (m_group->ut_unit() == DplDevice::Group::Time) {
        m_widthItem->set_unit(US_STR);
    } else {
        m_widthItem->set_unit(MM_STR);
    }

    m_widthItem->set(Tool::cnf_to_display(m_group, 0),
                     Tool::cnf_to_display(m_group, m_group->sample()->range()),
                     2, 0.01);

    m_widthItem->set_value(Tool::cnf_to_display(m_group, m_gate->width()));
}

void GateMenu::update_synchroItem()
{
    disconnect(m_synchroItem,
               SIGNAL(value_changed(int)),
               this,
               SLOT(do_synchroItem_changed(int)));

    m_synchroItem->set(QStringList());
    m_synchroItem->add_item(tr("Pulser"));
    m_synchroItem->add_item("I/");
    if (m_gate->type() == DplFpga::Group::GATE_B) {
        m_synchroItem->add_item("A/");
    }
    m_synchroItem->set_current_index(m_gate->synchro_mode());

    connect(m_synchroItem,
            SIGNAL(value_changed(int)),
            this,
            SLOT(do_synchroItem_changed(int)));
}

void GateMenu::update_measureModeItem()
{
    m_measureModeItem->set_current_index(m_gate->measure_mode());
}

void GateMenu::update_thresholdItem()
{
    m_thresholdItem->set_value(m_gate->height());
}

void GateMenu::do_gateItem_changed(int val)
{
    if (! m_gate.isNull()) {
        disconnect(static_cast<DplGate::Gate *>(m_gate.data()),
                   SIGNAL(start_changed(float)),
                   this, SLOT(update_startItem()));
        disconnect(static_cast<DplGate::Gate *>(m_gate.data()),
                   SIGNAL(height_changed(int)),
                   this, SLOT(update_thresholdItem()));
        disconnect(static_cast<DplGate::Gate *>(m_gate.data()),
                   SIGNAL(width_changed(float)),
                   this, SLOT(update_widhtItem()));
    }

    m_gate = m_group->gate(static_cast<DplFpga::Group::GateType>(val));

    connect(static_cast<DplGate::Gate *>(m_gate.data()),
               SIGNAL(start_changed(float)),
               this, SLOT(update_startItem()));
    connect(static_cast<DplGate::Gate *>(m_gate.data()),
               SIGNAL(height_changed(int)),
               this, SLOT(update_thresholdItem()));
    connect(static_cast<DplGate::Gate *>(m_gate.data()),
               SIGNAL(width_changed(float)),
               this, SLOT(update_widhtItem()));
    update_items();
}

void GateMenu::do_startItem_changed(double val)
{
    m_gate->set_start(Tool::display_to_cnf(m_group, val));
}

void GateMenu::do_widthItem_changed(double val)
{
    m_gate->set_width(Tool::display_to_cnf(m_group, val));
}

void GateMenu::do_thresholdItem_changed(double val)
{
    m_gate->set_height(val+0.5);
}

void GateMenu::do_switchItem_changed(int index)
{
    m_gate->set_visible(!index);
}

void GateMenu::do_paramsItem_changed(int index)
{
    if (m_synchroItem->isVisible()) {
        m_synchroItem->setVisible(!!index);
        m_measureModeItem->setVisible(!!index);
        m_modeItem->setVisible(!!index);
        m_startItem->setVisible(!index);
        m_widthItem->setVisible(!index);
        m_thresholdItem->setVisible(!index);
    } else {
        m_startItem->setVisible(!index);
        m_widthItem->setVisible(!index);
        m_thresholdItem->setVisible(!index);
        m_synchroItem->setVisible(!!index);
        m_measureModeItem->setVisible(!!index);
        m_modeItem->setVisible(!!index);
    }
}

void GateMenu::do_sample_changed()
{
    do_gateItem_changed(m_gateItem->current_index());
}

void GateMenu::do_synchroItem_changed(int index)
{
    m_gate->set_synchro_mode(static_cast<DplFpga::Group::SynchroMode>(index));
}

void GateMenu::do_measureModeItem_changed(int index)
{
    m_gate->set_measure_mode(static_cast<DplFpga::Group::MeasureMode>(index));
}

void GateMenu::update(const DplDevice::GroupPointer &group)
{
    if (!m_group.isNull()) {
        disconnect(m_group->sample().data(), SIGNAL(start_changed(float)),
                   this, SLOT(do_sample_changed()));
        disconnect(m_group->sample().data(), SIGNAL(range_changed(float)),
                   this, SLOT(do_sample_changed()));
    }

    m_group = group;

    connect(m_group->sample().data(),
            SIGNAL(start_changed(float)),
            this, SLOT(do_sample_changed()));
    connect(m_group->sample().data(),
            SIGNAL(range_changed(float)),
            this, SLOT(do_sample_changed()));

    do_gateItem_changed(DplFpga::Group::GATE_A);
}

}
