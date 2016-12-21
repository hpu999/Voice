#include "preference_menu.h"
#include "combo_menu_item.h"
#include "spin_menu_item.h"
#include "label_menu_item.h"

namespace DplPreferenceMenu {

PreferenceMenu::PreferenceMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Units menu item */
    m_unitItem = new ComboMenuItem;
    QStringList unitList;
    unitList.append("Millimeters");
    unitList.append("Inches");
    m_unitItem->set(tr("Units"), unitList);

    /* Bright menu item */
    m_brightItem = new SpinMenuItem;
    m_brightItem->set(tr("Bright"), "%", 1, 100, 0);
//    connect(m_brightItem, SIGNAL(spin_event(double)), this, SLOT(set_brightness(double)));

    /* Opacity menu item */
    m_opacityItem = new SpinMenuItem;
    m_opacityItem->set(tr("Opacity"), "%", 1, 100, 0);

    /* Language menu item */
    m_languageItem = new ComboMenuItem;
    QStringList languageList;
    languageList.append("English");
    languageList.append("Chinese");
    m_languageItem->set(tr("Language"), languageList);

    /* Starting Page Menu Item */
    m_startingPageItem = new ComboMenuItem;
    m_startingPageItem->set(tr("Starting Page"), s_onOff);

    /* Gate Mode */
    m_gatemodeItem = new ComboMenuItem;
    m_gatemodeItem->set(tr("Gate Mode"), s_onOff);
}

PreferenceMenu::~PreferenceMenu()
{
    delete m_unitItem;
    delete m_brightItem;
    delete m_opacityItem;
    delete m_languageItem;
    delete m_startingPageItem;
    delete m_gatemodeItem;
}

void PreferenceMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_unitItem);
    ui->menuItem1->layout()->addWidget(m_brightItem);
    ui->menuItem2->layout()->addWidget(m_opacityItem);
    ui->menuItem3->layout()->addWidget(m_languageItem);
    ui->menuItem4->layout()->addWidget(m_startingPageItem);
    ui->menuItem5->layout()->addWidget(m_gatemodeItem);
    m_unitItem->show();
    m_brightItem->show();
    m_opacityItem->show();
    m_languageItem->show();
    m_startingPageItem->show();
    m_gatemodeItem->show();
}

void PreferenceMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_unitItem);
    ui->menuItem1->layout()->removeWidget(m_brightItem);
    ui->menuItem2->layout()->removeWidget(m_opacityItem);
    ui->menuItem3->layout()->removeWidget(m_languageItem);
    ui->menuItem4->layout()->removeWidget(m_startingPageItem);
    ui->menuItem5->layout()->removeWidget(m_gatemodeItem);
    m_unitItem->hide();
    m_brightItem->hide();
    m_opacityItem->hide();
    m_languageItem->hide();
    m_startingPageItem->hide();
    m_gatemodeItem->hide();
}

}