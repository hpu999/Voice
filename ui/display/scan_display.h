#ifndef __SCAN_DISPLAY_H__
#define __SCAN_DISPLAY_H__

#include <QWidget>
#include <QLayout>

class ColorBar;
class Ruler;
class QLabel;
class ScanView;

class ScanDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit ScanDisplay(QWidget *parent = 0);

protected slots:
    virtual void resize_event(const QSize &size) = 0;

protected:
    QLabel *m_titleLabel;
    ColorBar *m_colorBar;
    Ruler *m_leftRuler;
    Ruler *m_rightRuler;
    Ruler *m_bottomRuler;
    ScanView *m_view;
};

#endif // __SCAN_DISPLAY_H__
