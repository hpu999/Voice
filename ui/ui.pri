
INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/menuwidget
INCLUDEPATH += $$PWD/dialogwidget
INCLUDEPATH += $$PWD/qitemdelegate
INCLUDEPATH += $$PWD/spinbox
INCLUDEPATH += $$PWD/fake_keyboard
INCLUDEPATH += $$PWD/scan_layout

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
    $$PWD/qitemdelegate/doublespinboxdelegate.cpp \
    $$PWD/scan_layout/scan_group_layout.cpp \
    $$PWD/scan_layout/ascan_layout.cpp \
    $$PWD/scan_layout/cscan_layout.cpp \
    $$PWD/scan_layout/sscan_layout.cpp \
    $$PWD/scan_layout/abc_layout.cpp \
    $$PWD/scan_layout/stb_layout.cpp

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
    $$PWD/qitemdelegate/doublespinboxdelegate.h \
    $$PWD/scan_layout/scan_group_layout.h \
    $$PWD/scan_layout/ascan_layout.h \
    $$PWD/scan_layout/cscan_layout.h \
    $$PWD/scan_layout/sscan_layout.h \
    $$PWD/scan_layout/abc_layout.h \
    $$PWD/scan_layout/stb_layout.h

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
    $$PWD/fake_keyboard/virtualkeyboard.ui \
    $$PWD/scan_layout/group_1/ascan_1.ui \
    $$PWD/scan_layout/group_1/ascan_b_c_1.ui \
    $$PWD/scan_layout/group_1/ascan_b_s_1.ui \
    $$PWD/scan_layout/group_1/ascan_s_1.ui \
    $$PWD/scan_layout/group_1/ascan_s_c_1.ui \
    $$PWD/scan_layout/group_1/cscan_1.ui \
    $$PWD/scan_layout/group_1/sscan_1.ui \
    $$PWD/scan_layout/group_1/sscan_c_1.ui \
    $$PWD/scan_layout/group_1/tab_1.ui \
    $$PWD/scan_layout/group_2/ascan_2.ui \
    $$PWD/scan_layout/group_2/ascan_s_2.ui \
    $$PWD/scan_layout/group_2/ascan_b_c_2.ui \
    $$PWD/scan_layout/group_2/ascan_b_s_2.ui \
    $$PWD/scan_layout/group_2/ascan_s_c_2.ui \
    $$PWD/scan_layout/group_2/cscan_2.ui \
    $$PWD/scan_layout/group_2/sscan_2.ui \
    $$PWD/scan_layout/group_2/sscan_c_2.ui \
    $$PWD/scan_layout/group_2/sscan_c_tab_2.ui \
    $$PWD/scan_layout/group_2/tab_2.ui \
    $$PWD/scan_layout/group_3/ascan_3.ui \
    $$PWD/scan_layout/group_3/ascan_b_c_3.ui \
    $$PWD/scan_layout/group_3/ascan_b_s_3.ui \
    $$PWD/scan_layout/group_3/ascan_s_c_3.ui \
    $$PWD/scan_layout/group_3/ascan_s3_3.ui \
    $$PWD/scan_layout/group_3/cscan_3.ui \
    $$PWD/scan_layout/group_3/cscan_s_tab_3.ui \
    $$PWD/scan_layout/group_3/cscan_s2_tab_3.ui \
    $$PWD/scan_layout/group_3/cscan_s3_3.ui \
    $$PWD/scan_layout/group_3/sscan_3.ui \
    $$PWD/scan_layout/group_3/sscan_tb_3.ui \
    $$PWD/scan_layout/group_3/sscan_tb2_3.ui \
    $$PWD/scan_layout/group_4/ascan_4.ui \
    $$PWD/scan_layout/group_4/cscan_4.ui \
    $$PWD/scan_layout/group_4/sscan_c4_4.ui \
    $$PWD/scan_layout/group_4/cscan_tb2_4.ui \
    $$PWD/scan_layout/group_4/sscan_tb2_4.ui \
    $$PWD/scan_layout/group_4/sscan_4.ui \
    $$PWD/scan_layout/group_4/sscan_ta2_4.ui \
    $$PWD/scan_layout/group_4/ascan_s4_4.ui \
    $$PWD/scan_layout/group_4/sscan_c_ta_b_4.ui \
    $$PWD/scan_layout/group_5/ascan_5.ui \
    $$PWD/scan_layout/group_5/sscan_tb1_5.ui \
    $$PWD/scan_layout/group_5/sscan_tb2_5.ui \
    $$PWD/scan_layout/group_6/ascan_6.ui \
    $$PWD/scan_layout/group_6/sscan_tb_6.ui \
    $$PWD/scan_layout/scan_group_layout.ui \
    $$PWD/scan_layout/ascan_layout.ui \
    $$PWD/scan_layout/cscan_layout.ui \
    $$PWD/scan_layout/sscan_layout.ui \
    $$PWD/scan_layout/abc_layout.ui \
    $$PWD/scan_layout/stb_layout.ui


