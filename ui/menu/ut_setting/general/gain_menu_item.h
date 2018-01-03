#ifndef __GAIN_MENU_ITEM_H__
#define __GAIN_MENU_ITEM_H__

#include "../../menu_item/spin_menu_item.h"

#include <device/group.h>

class GainMenuItem : public SpinMenuItem
{
    Q_OBJECT
public:
    GainMenuItem(QWidget *parent);

protected slots:
    void update(const DplDevice::GroupPointer &group);

    void update_range(DplDevice::Group::Mode mode);
    void update_value(float val);

    void do_value_changed(double val);

protected:
    void language_changed();

private:
    DplDevice::GroupPointer m_group;
};

#endif // __GAIN_MENU_ITEM_H__