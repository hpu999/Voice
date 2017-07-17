/**
 * @file tcg_menu.cpp
 * @brief Gate/Curves tcg menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "tcg_menu.h"
#include "spin_menu_item.h"
#include "combo_menu_item.h"
#include "label_menu_item.h"

namespace DplGateCurvesMenu {

TcgMenu::TcgMenu(Ui::BaseMenu *ui, QObject *parent)
    : BaseMenu(ui, parent)
{
    QStringList modeList;
    QStringList curveXList;
    QStringList pointList;

    modeList.append(tr("Settings"));
    modeList.append(tr("Edit"));

    curveXList.append("1");
    curveXList.append("2");
    curveXList.append("3");
    curveXList.append("4");
    curveXList.append("5");

    pointList.append("1");
    pointList.append("2");

    m_modeItem.set(tr("Mode"), modeList);
    connect(&m_modeItem, SIGNAL(value_changed(int)), this, SLOT(do_mode_event(int)));

    /* Setting */

    m_curveNoItem.set(tr("Curve No."), "", 1, 5, 0);
    m_curveXItem.set(tr("Curve X"), curveXList);
    m_dbOffsetItem.set(tr("dB Offset"), "dB", -40, 40, 1);
    m_switchItem.set(tr("Switch"), s_onOff);

    /* Edit */
    m_pointItem.set(tr("Point"), pointList);
    m_positionItem.set(tr("Position"), "", 0, 10000, 2);
    m_gainItem.set(tr("Gain"), "dB", 0, 100, 1);
    m_addPointItem.set(tr("Add Point"), "");
    m_deletePointItem.set(tr("Delete Point"), "");
}

TcgMenu::~TcgMenu()
{
}

void TcgMenu::show()
{
    if (m_modeItem.current_index() == 0) {
        show_setting();
    } else {
        show_edit();
    }
}

void TcgMenu::hide()
{
    if (m_modeItem.current_index() == 0) {
        hide_setting();
    } else {
        hide_edit();
    }
}

void TcgMenu::show_setting()
{
    ui->layout0->addWidget(&m_modeItem);
    ui->layout1->addWidget(&m_curveNoItem);
    ui->layout2->addWidget(&m_curveXItem);
    ui->layout3->addWidget(&m_dbOffsetItem);
    ui->layout4->addWidget(&m_switchItem);

    m_modeItem.show();
    m_curveNoItem.show();
    m_curveXItem.show();
    m_dbOffsetItem.show();
    m_switchItem.show();
}

void TcgMenu::hide_setting()
{
    ui->layout0->removeWidget(&m_modeItem);
    ui->layout1->removeWidget(&m_curveNoItem);
    ui->layout2->removeWidget(&m_curveXItem);
    ui->layout3->removeWidget(&m_dbOffsetItem);
    ui->layout4->removeWidget(&m_switchItem);

    m_modeItem.hide();
    m_curveNoItem.hide();
    m_curveXItem.hide();
    m_dbOffsetItem.hide();
    m_switchItem.hide();
}

void TcgMenu::show_edit()
{
    ui->layout0->addWidget(&m_modeItem);
    ui->layout1->addWidget(&m_pointItem);
    ui->layout2->addWidget(&m_positionItem);
    ui->layout3->addWidget(&m_gainItem);
    ui->layout4->addWidget(&m_addPointItem);
    ui->layout5->addWidget(&m_deletePointItem);

    m_modeItem.show();
    m_pointItem.show();
    m_positionItem.show();
    m_gainItem.show();
    m_addPointItem.show();
    m_deletePointItem.show();
}

void TcgMenu::hide_edit()
{
    ui->layout0->removeWidget(&m_modeItem);
    ui->layout1->removeWidget(&m_pointItem);
    ui->layout2->removeWidget(&m_positionItem);
    ui->layout3->removeWidget(&m_gainItem);
    ui->layout4->removeWidget(&m_addPointItem);
    ui->layout5->removeWidget(&m_deletePointItem);

    m_modeItem.hide();
    m_pointItem.hide();
    m_positionItem.hide();
    m_gainItem.hide();
    m_addPointItem.hide();
    m_deletePointItem.hide();
}

void TcgMenu::do_mode_event(int pos)
{
    if (pos == 0) {
        hide_edit();
        show_setting();
    } else {
        hide_setting();
        show_edit();
    }
}

}
