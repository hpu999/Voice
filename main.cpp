#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

#if (PHASCAN | PHASCAN_II)
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

    int fontId = QFontDatabase::addApplicationFont(":/file/font/simhei.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(fontName, 16);
    w.setFont(font);

    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
#endif
    w.show();

    return a.exec();
}
