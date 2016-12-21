/**
 * @file system_menu.cpp
 * @brief system menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-21
 */
#include "system_menu.h"
#include "label_menu_item.h"
#include "combo_menu_item.h"

#include <QDate>

namespace DplPreferenceMenu {

SystemMenu::SystemMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Date */
    m_dateItem = new LabelMenuItem;
    m_dateItem->set(tr("Date"), QDate::currentDate().toString("yyyy-MM-dd"));
//    connect(m_dateItem, SIGNAL(clicked()), this, SLOT(show_date_dialog()));

    /* Time */
    m_timeItem = new LabelMenuItem;
    m_timeItem->set(tr("Time"), QTime::currentTime().toString("hh:mm:ss"));
//    connect(m_timeItem, SIGNAL(clicked()), this, SLOT(show_time_dialog()));

    /* Cert Import menu item */
    m_certItem = new ComboMenuItem;
    QStringList m_list_certImport;
    m_list_certImport.append(tr("U-Disk"));
    m_list_certImport.append(tr("Network"));
    m_certItem->set(tr("Cert Import"), m_list_certImport);

    /* Update */
    m_updateItem = new LabelMenuItem;
    m_updateItem->set(tr("Update"), "");

    /* Reset Configuration */
    m_resetCfgItem = new LabelMenuItem;
    m_resetCfgItem->set(tr("Reset Config"), "");
//    connect(m_resetItem, SIGNAL(clicked()), this, SLOT(show_resetconfig_dialog()));

    /* System Information */
    m_infoItem = new LabelMenuItem;
    m_infoItem->set(tr("System Info."), "");
//    connect(m_informationItem, SIGNAL(clicked()), this, SLOT(show_info_dialog()));

}

SystemMenu::~SystemMenu()
{
    delete m_timeItem;
    delete m_dateItem;
    delete m_certItem;
    delete m_updateItem;
    delete m_resetCfgItem;
    delete m_infoItem;
}

void SystemMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_timeItem);
    ui->menuItem1->layout()->addWidget(m_dateItem);
    ui->menuItem2->layout()->addWidget(m_certItem);
    ui->menuItem3->layout()->addWidget(m_updateItem);
    ui->menuItem4->layout()->addWidget(m_resetCfgItem);
    ui->menuItem5->layout()->addWidget(m_infoItem);
    m_timeItem->show();
    m_dateItem->show();
    m_certItem->show();
    m_updateItem->show();
    m_resetCfgItem->show();
    m_infoItem->show();
}

void SystemMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_timeItem);
    ui->menuItem1->layout()->removeWidget(m_dateItem);
    ui->menuItem2->layout()->removeWidget(m_certItem);
    ui->menuItem3->layout()->removeWidget(m_updateItem);
    ui->menuItem4->layout()->removeWidget(m_resetCfgItem);
    ui->menuItem5->layout()->removeWidget(m_infoItem);
    m_timeItem->hide();
    m_dateItem->hide();
    m_certItem->hide();
    m_updateItem->hide();
    m_resetCfgItem->hide();
    m_infoItem->hide();
}

}
