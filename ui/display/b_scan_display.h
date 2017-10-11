#ifndef __B_SCAN_DISPLAY_H_
#define __B_SCAN_DISPLAY_H_

#include <QWidget>
#include <ui/display/b_scan_scene.h>
#include <device/device.h>
#include <QSemaphore>

class ScanView;
class BWaveItem;
class ScrollRulerWidget;
class QTimer;
class QLabel;

namespace Ui {
class BscanDisplay;
}

class BscanDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit BscanDisplay(const DplDevice::GroupPointer &grp, Qt::Orientation orientation, QWidget *parent = 0);
    ~BscanDisplay();

    bool set_current_beam(unsigned int index);



signals:
    void update_ruler(double value);
    void update_label(const QString &time);
    void refresh_scan_env();

protected slots:

    void do_data_event(const DplSource::BeamsPointer &beams);
    void update_sound_path_ruler();
    void do_update_label(const QString &time);

    void do_view_size_changed(const QSize &size);
    void do_refresh_scan_env();
    void do_update_ruler(double x);

protected:
    Ui::BscanDisplay *ui;

    DplDevice::GroupPointer m_group;
    ScrollRulerWidget      *m_scanTypeRuler;
    ScrollRulerWidget      *m_soundPathRuler;

    ScanView         *m_bscanView;
    BscanScene       *m_bscanScene;

    DplSource::Axis::Driving      m_driving;                /* 扫查类型：encoder_x/y / timer*/

    double           m_currentTimeCount;    /* 秒 */
    QLabel           *m_timeShowLabel;
    Qt::Orientation  m_orientation;
    QSemaphore       m_refreshSemaphore;    /* 切换时间扫查或编码器扫查时，刷新信号量 */

    DplSource::AxisPointer      m_axisPointer;
    DplSource::EncoderPointer   m_encoderPointer;

    virtual void init_ruler();
    void update_scan_type_ruler(const QSize &size);
    void wait_for_refresh_finished();
    void init_scan_env();

};

#endif // __B_SCAN_DISPLAY_H_