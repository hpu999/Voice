#ifndef __START_MENU_H__
#define __START_MENU_H__

#include "../base_menu.h"

namespace DplScanMenu {

class StartMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit StartMenu(QWidget *parent);
    ~StartMenu();

protected slots:
    void do_startItem_clicked();
    void do_pauseItem_clicked();

private:
    LabelMenuItem *m_startItem;
    LabelMenuItem *m_pauseItem;
};

}
#endif // __START_MENU_H__
