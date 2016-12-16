/**
 * @file tcg_menu.h
 * @brief Gate/Curves tcg menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __TCG_MENU_H__
#define __TCG_MENU_H__

#include "base_menu.h"

class TcgMenu : public BaseMenu
{
    Q_OBJECT
public:
    TcgMenu(Ui::SubMenu *ui, QObject *parent);

    void show();
    void hide();

private:
    MenuItem *m_pointItem;
    MenuItem *m_positionItem;
    MenuItem *m_gainItem;
    MenuItem *m_addPointItem;
    MenuItem *m_deletePointItem;

    bool m_settingFlag;

    void show_edit();
    void hide_edit();

private slots:
    void do_mode_event(int pos);
};

#endif // __TCG_MENU_H__