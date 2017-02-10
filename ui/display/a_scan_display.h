#ifndef __A_SCAN_DISPLAY_H__
#define __A_SCAN_DISPLAY_H__

#include <device/device.h>

#include <QWidget>

namespace Ui {
class AscanDisplay;
}

class AscanDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit AscanDisplay(DplDevice::GroupPointer &group, QWidget *parent = 0);
    ~AscanDisplay();

protected slots:
    void update();

private:
    Ui::AscanDisplay *ui;

    DplDevice::GroupPointer m_group;

private slots:
    void update_bottom_ruler();
};

#endif // __A_SCAN_DISPLAY_H__
