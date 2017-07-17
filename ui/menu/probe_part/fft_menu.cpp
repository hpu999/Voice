#include "fft_menu.h"
#include "spin_menu_item.h"
#include "combo_menu_item.h"

namespace DplProbeMenu {

FftMenu::FftMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Gain */
    m_gainItem.set(tr("Gain"), "dB", 0, 100, 1);

    /* Start menu item */
    m_startItem.set(tr("Start"), "mm", 0, 16000, 2);

    /* Width menu item */
    m_widthItem.set(tr("Width"), "mm", 0.05, 525, 2);

    /* Switch menu item */
    m_switchItem.set(tr("Switch"), s_onOff);
}

FftMenu::~FftMenu()
{
}

void FftMenu::show()
{
    ui->layout0->addWidget(&m_gainItem);
    ui->layout1->addWidget(&m_startItem);
    ui->layout2->addWidget(&m_widthItem);
    ui->layout3->addWidget(&m_switchItem);
    m_gainItem.show();
    m_startItem.show();
    m_widthItem.show();
    m_switchItem.show();
}

void FftMenu::hide()
{
    ui->layout0->removeWidget(&m_gainItem);
    ui->layout1->removeWidget(&m_startItem);
    ui->layout2->removeWidget(&m_widthItem);
    ui->layout3->removeWidget(&m_switchItem);
    m_gainItem.hide();
    m_startItem.hide();
    m_widthItem.hide();
    m_switchItem.hide();
}

}
