
INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/menuwidget
INCLUDEPATH += $$PWD/dialogwidget
INCLUDEPATH += $$PWD/qitemdelegate
INCLUDEPATH += $$PWD/spinbox
INCLUDEPATH += $$PWD/fake_keyboard

include(vinput/vinput.pri)
include(icons_bar/icons_bar.pri)
include(measure_bar/measure_bar.pri)

SOURCES += \
    $$PWD/mainwindow.cpp \
    $$PWD/showinfowidget.cpp \
    $$PWD/menuwidget/firstsecondmenuwidget.cpp \
    $$PWD/menuwidget/thirdmenuwidget.cpp \
    $$PWD/menuwidget/commonmenuwidget.cpp \
    $$PWD/menuwidget/commonmenubutton.cpp \
    $$PWD/dialogwidget/timesetdialog.cpp \
    $$PWD/dialogwidget/probedialog.cpp \
    $$PWD/dialogwidget/wedgedialog.cpp \
    $$PWD/qitemdelegate/comboboxdelegate.cpp \
    $$PWD/qitemdelegate/pushbuttondelegate.cpp \
    $$PWD/dialogwidget/inputpanelcontext.cpp \
    $$PWD/dialogwidget/resetconfigdialog.cpp \
    $$PWD/dialogwidget/networkdialog.cpp \
    $$PWD/dialogwidget/datetimesetdialog.cpp \
    $$PWD/dialogwidget/filemanagerdialog.cpp \
    $$PWD/dialogwidget/about_dialog.cpp \
    $$PWD/dialogwidget/sysinfo_dialog.cpp \
    $$PWD/spinbox/spinbox.cpp \
    $$PWD/fake_keyboard/virtualkeyboard.cpp \
    $$PWD/qitemdelegate/lineeditdelegate.cpp \
    $$PWD/qitemdelegate/doublespinboxdelegate.cpp

HEADERS += \
    $$PWD/mainwindow.h \
    $$PWD/showinfowidget.h \
    $$PWD/menuwidget/firstsecondmenuwidget.h \
    $$PWD/menuwidget/thirdmenuwidget.h \
    $$PWD/menuwidget/commonmenuwidget.h \
    $$PWD/menuwidget/commonmenubutton.h \
    $$PWD/dialogwidget/timesetdialog.h \
    $$PWD/dialogwidget/probedialog.h \
    $$PWD/dialogwidget/wedgedialog.h \
    $$PWD/qitemdelegate/comboboxdelegate.h \
    $$PWD/qitemdelegate/pushbuttondelegate.h \
    $$PWD/dialogwidget/inputpanelcontext.h \
    $$PWD/dialogwidget/resetconfigdialog.h \
    $$PWD/dialogwidget/networkdialog.h \
    $$PWD/dialogwidget/datetimesetdialog.h \
    $$PWD/dialogwidget/filemanagerdialog.h \
    $$PWD/dialogwidget/about_dialog.h \
    $$PWD/dialogwidget/sysinfo_dialog.h \
    $$PWD/spinbox/spinbox.h \
    $$PWD/fake_keyboard/virtualkeyboard.h \
    $$PWD/qitemdelegate/lineeditdelegate.h \
    $$PWD/qitemdelegate/doublespinboxdelegate.h

FORMS += \
    $$PWD/mainwindow.ui \
    $$PWD/showinfowidget.ui \
    $$PWD/menuwidget/firstsecondmenuwidget.ui \
    $$PWD/menuwidget/thirdmenuwidget.ui \
    $$PWD/menuwidget/commonmenuwidget.ui \
    $$PWD/menuwidget/commonmenubutton.ui \
    $$PWD/dialogwidget/timesetdialog.ui \
    $$PWD/dialogwidget/probedialog.ui \
    $$PWD/dialogwidget/wedgedialog.ui \
    $$PWD/dialogwidget/inputpanelcontext.ui \
    $$PWD/dialogwidget/resetconfigdialog.ui \
    $$PWD/dialogwidget/networkdialog.ui \
    $$PWD/dialogwidget/datetimesetdialog.ui \
    $$PWD/dialogwidget/filemanagerdialog.ui \
    $$PWD/fake_keyboard/virtualkeyboard.ui 
