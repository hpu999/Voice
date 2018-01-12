/**
 * @file color_setting_menu.h
 * @brief Color Setting menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __COLOR_SETTING_MENU_H__
#define __COLOR_SETTING_MENU_H__

#include "../base_menu.h"

namespace DplDisplayMenu {

class ColorSettingMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit ColorSettingMenu(QWidget *parent);
    ~ColorSettingMenu();

private:
    LabelMenuItem *m_amplitudeItem;
    LabelMenuItem *m_depthItem;
    LabelMenuItem *m_tofdItem;

protected:
    void changeEvent(QEvent *e);
};

}
#endif // __COLOR_SETTING_MENU_H__
