/**
 * @file probe_selection_menu.cpp
 * @brief Probe/Part Select Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-19
 */
#include "selection_menu.h"
#include "probe_dialog.h"
#include "wedge_dialog.h"
#include <QDebug>

namespace DplProbeMenu {

SelectionMenu::SelectionMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    DplDevice::Device *dev = DplDevice::Device::instance();
    connect(dev, SIGNAL(current_group_changed()), this, SLOT(do_current_group_changed()));
    m_group = dev->current_group();

    m_groupItem = new ComboMenuItem;
    m_modeItem = new ComboMenuItem;
    m_probeItem = new LabelMenuItem;
    m_wedgeItem = new LabelMenuItem;
    m_autoDetectItem = new ComboMenuItem;

    QStringList groupList;
    QStringList modeList;

    groupList.append(tr("Add"));
    groupList.append("1");
    groupList.append("2");
    groupList.append("3");
    groupList.append("4");
    groupList.append("5");
    groupList.append("6");
    groupList.append("7");
    groupList.append("8");
    groupList.append(tr("Remove"));

    modeList.append(tr("UT (PA Connector)"));
    modeList.append(tr("PA (Phassed Array)"));
    modeList.append(tr("UT1 (Conventional UT)"));
    modeList.append(tr("UT2 (Conventional UT)"));

    m_groupItem->set(tr("Group"), groupList);

    m_modeItem->set(tr("Mode"), modeList);
    m_modeItem->set_dispay_mode(ComboMenuItem::PREFIX);
    connect(m_modeItem, SIGNAL(value_changed(int)),
            this, SLOT(do_groupModeItem_changed(int)));

    m_probeItem->set(tr("Probe"), "");
    connect(m_probeItem, SIGNAL(clicked()), this, SLOT(do_probeItem_clicked()));

    m_wedgeItem->set(tr("Wedge"), "");
    connect(m_wedgeItem, SIGNAL(clicked()), this, SLOT(do_wedgeItem_clicked()));

    m_autoDetectItem->set(tr("Auto Detect"), s_onOff);

    m_updateFlag = true;
}

SelectionMenu::~SelectionMenu()
{
    delete m_groupItem;
    delete m_modeItem;
    delete m_probeItem;
    delete m_wedgeItem;
    delete m_autoDetectItem;
}

void SelectionMenu::show()
{
    if (m_updateFlag) {
        update();
    }
    ui->menuItem0->layout()->addWidget(m_groupItem);
    ui->menuItem1->layout()->addWidget(m_modeItem);
    ui->menuItem2->layout()->addWidget(m_probeItem);
    ui->menuItem3->layout()->addWidget(m_wedgeItem);
    ui->menuItem4->layout()->addWidget(m_autoDetectItem);
    m_groupItem->show();
    m_modeItem->show();
    m_probeItem->show();
    m_wedgeItem->show();
    m_autoDetectItem->show();
}

void SelectionMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_groupItem);
    ui->menuItem1->layout()->removeWidget(m_modeItem);
    ui->menuItem2->layout()->removeWidget(m_probeItem);
    ui->menuItem3->layout()->removeWidget(m_wedgeItem);
    ui->menuItem4->layout()->removeWidget(m_autoDetectItem);
    m_groupItem->hide();
    m_modeItem->hide();
    m_probeItem->hide();
    m_wedgeItem->hide();
    m_autoDetectItem->hide();
}

void SelectionMenu::do_probeItem_clicked()
{
    ProbeDialog probeDialog;
    if (QDialog::Rejected == probeDialog.exec()) {
        return;
    }

    DplFocallaw::ProbePointer probePtr = probeDialog.get_probe();
    if (probePtr.isNull()) {
        m_probeItem->set_text("");
    } else {
        m_probeItem->set_text(probePtr->model());
        m_group->focallawer()->set_probe(probePtr);
    }
}

void SelectionMenu::do_wedgeItem_clicked()
{
    WedgeDialog wedgeDialog;
    if (QDialog::Rejected == wedgeDialog.exec()) {
        return;
    }

    DplFocallaw::WedgePointer wedgePointer = m_group->focallawer()->wedge();

    if (wedgePointer->load(wedgeDialog.get_path())) {
        m_wedgeItem->set_text(wedgePointer->model());
    }
}

void SelectionMenu::do_groupModeItem_changed(int index)
{
    m_group->set_mode(static_cast<DplDevice::Group::Mode>(index));
}

void SelectionMenu::do_current_group_changed()
{
    m_group = DplDevice::Device::instance()->current_group();
    if (m_probeItem->isHidden()) {
        m_updateFlag = true;
    } else {
        update();
    }
}

void SelectionMenu::update()
{
    m_modeItem->set_current_index(m_group->mode());

    m_updateFlag = false;
}

}
