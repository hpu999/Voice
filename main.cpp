#include "mainwindow.h"
#include <device/device.h>

#include <QApplication>
#include <QTextCodec>
#include <QFontDatabase>
#include <QDebug>

#if (PHASCAN | PHASCAN_II)
static const char *FONT_FILE = "/etc/mercury/font/SONGTI.TTC";
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTime time;
    time.restart();

    DplDevice::Device *dev = DplDevice::Device::instance();

    MainWindow w;

#if (PHASCAN | PHASCAN_II)
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

    int fontId = QFontDatabase::addApplicationFont(FONT_FILE);
    QStringList list = QFontDatabase::applicationFontFamilies(fontId);
    if (list.isEmpty()) {
        qWarning()<<"font families is empty";
    } else {
        QFont font(list.at(0), 16);
        qDebug()<<"font="<<list.at(0);
        w.setFont(font);
    }

    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
#endif
    w.show();

    qDebug("%s[%d]: Take Time%d(ms)",__func__, __LINE__, time.elapsed());

    return a.exec();
}
