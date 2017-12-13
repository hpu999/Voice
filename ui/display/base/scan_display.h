#ifndef __SCAN_DISPLAY_H__
#define __SCAN_DISPLAY_H__

#include <QWidget>
#include <QLayout>

class ColorBar;
class Ruler;
class ScanView;
class ScanScene;
class QLabel;

class ScanDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit ScanDisplay(QWidget *parent = 0);

protected slots:
    virtual void resize_event(const QSize &size) = 0;

protected:
    QLabel *m_titleLabel;
    Ruler *m_colorRuler;
    ColorBar *m_colorBar;
    QLayout *m_leftLayout;
    QLayout *m_bottomLayout;
    ScanView *m_view;
    ScanScene *m_scene;
};

#endif // __SCAN_DISPLAY_H__
