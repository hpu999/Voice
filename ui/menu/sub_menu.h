/**
 * @file sub_menu.h
 * @brief Third menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __SUB_MENU_H__
#define __SUB_MENU_H__

#include "main_menu.h"
#include "base_menu.h"

#include <QMap>

namespace Ui {
class BaseMenu;
}

class SubMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SubMenu(QWidget *parent = 0);
    ~SubMenu();

public slots:
    void set_menu(MainMenu::Type type);

private:
    Ui::BaseMenu *ui;

    void init_map();

    QMap<MainMenu::Type, BaseMenu*> m_map;

    MainMenu::Type m_preType;
};

#endif // SUB_MENU_H
