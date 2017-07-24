/**
 * @file network_menu.cpp
 * @brief network menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-21
 */
#include "network_menu.h"
#include "ui_base_menu.h"
#include "networkdialog.h"

namespace DplPreferenceMenu {

NetworkMenu::NetworkMenu(QWidget *parent) :
    BaseMenu(parent),
    m_ipItem(new LabelMenuItem(this, tr("IP Address"), "192.168.1.2")),
    m_maskItem(new LabelMenuItem(this, tr("Subnet Mask"), "255.255.255.0"))
{
    ui->layout0->addWidget(m_ipItem);
    ui->layout1->addWidget(m_maskItem);

    /* IP Address menu item */
    connect(m_ipItem, SIGNAL(clicked()), this, SLOT(show_ip_address_dialog()));

    /* Subnet Mask menu item */
    connect(m_maskItem, SIGNAL(clicked()), this, SLOT(show_subnet_mask_dialog()));
}

NetworkMenu::~NetworkMenu()
{
}

void NetworkMenu::show_ip_address_dialog()
{
    NetworkDialog dialog;
    QString title = m_ipItem->title();
    QString str = m_ipItem->text();

    dialog.set_dialog_title(title);
    dialog.set_spinbox_value(str);

    if (dialog.exec() == NetworkDialog::Accepted) {
        m_ipItem->set_text(dialog.get_text());
    } else {
        m_ipItem->set_text(str);
    }
}

void NetworkMenu::show_subnet_mask_dialog()
{
    NetworkDialog dialog;
//    QMap<QString, QString> map;
//    map.insert("Subnet Mask Set", m_maskItem->get_title());
    QString title = m_maskItem->title();
    QString str = m_maskItem->text();

    dialog.set_dialog_title(title);
    dialog.set_spinbox_value(str);

    if (dialog.exec() == NetworkDialog::Accepted) {
        m_maskItem->set_text(dialog.get_text());
    } else {
        m_maskItem->set_text(str);
    }
}

}
