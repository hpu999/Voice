/**
 * @file general_menu.h
 * @brief Ut Setting General Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */
#ifndef __GENERAL_MENU_H__
#define __GENERAL_MENU_H__

#include "../base_menu.h"

#include <device/device.h>

class GainMenuItem;
class StartMenuItem;
class RangeMenuItem;

namespace DplUtSettingMenu {

class GeneralMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit GeneralMenu(QWidget *parent = 0);
    ~GeneralMenu();

protected:

protected slots:
    void do_velocityItem_changed(double value);
    void do_wedgeDelayItem_changed(double value);
    void do_utUnitItem_changed(int index);

    /**
     * @brief update    更新菜单数据
     */
    void update(const DplDevice::GroupPointer &group);

private:
    GainMenuItem *m_gainItem;
    StartMenuItem *m_startItem;
    RangeMenuItem *m_rangeItem;
    SpinMenuItem *m_velocityItem;
    SpinMenuItem *m_wedgeDelayItem;
    ComboMenuItem *m_utUnitItem;

    DplDevice::GroupPointer m_group;
};

}
#endif // GENERALMENU_H
