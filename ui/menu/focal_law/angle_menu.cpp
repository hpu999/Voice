#include "angle_menu.h"
#include "spin_menu_item.h"

namespace DplFocalLawMenu {

AngleMenu::AngleMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Min.Angle Menu Item */
    m_minAngleItem.set(tr("Min.Angle"), "°", 25, 75, 0);

    /* Max.Angle Menu Item */
    m_maxAngleItem.set(tr("Max.Angle"), "°", 25, 75, 0);

    /* Angle Step Menu Item */
    m_angleStepItem.set(tr("Angle Step"), "°", 1, 10, 0);
}

AngleMenu::~AngleMenu()
{
}

void AngleMenu::show()
{
    ui->layout0->addWidget(&m_minAngleItem);
    ui->layout1->addWidget(&m_maxAngleItem);
    ui->layout2->addWidget(&m_angleStepItem);
    m_minAngleItem.show();
    m_maxAngleItem.show();
    m_angleStepItem.show();
}

void AngleMenu::hide()
{
    ui->layout0->removeWidget(&m_minAngleItem);
    ui->layout1->removeWidget(&m_maxAngleItem);
    ui->layout2->removeWidget(&m_angleStepItem);
    m_minAngleItem.hide();
    m_maxAngleItem.hide();
    m_angleStepItem.hide();
}

}
