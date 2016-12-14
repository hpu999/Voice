#include "base_menu.h"

QList<double> BaseMenu::s_steps1;
QList<double> BaseMenu::s_steps2;
QStringList BaseMenu::s_onOff;

BaseMenu::BaseMenu(Ui::SubMenu *ui, QObject *parent)
    :QObject(parent)
{
    this->ui = ui;

    if (s_steps1.isEmpty()) {
        s_steps1.append(0.1);
        s_steps1.append(0.5);
        s_steps1.append(1.0);
        s_steps1.append(2.0);
        s_steps1.append(5.0);
    }

    if (s_steps2.isEmpty()) {
        s_steps2.append(0.01);
        s_steps2.append(0.1);
        s_steps2.append(1.00);
        s_steps2.append(10.0);
        s_steps2.append(100.0);
    }

    if (s_onOff.isEmpty()) {
        s_onOff.append(tr("On"));
        s_onOff.append(tr("Off"));
    }
}