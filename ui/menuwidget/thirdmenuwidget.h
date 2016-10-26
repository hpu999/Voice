#ifndef THIRDMENUWIDGET_H
#define THIRDMENUWIDGET_H

#include "firstsecondmenuwidget.h"
#include "verticalsliderdialog.h"
#include "datetimesetdialog.h"
#include "networkdialog.h"

#define THIRD_MENU_NUMBER 6

namespace Ui {
    class ThirdMenuWidget;
}

class ThirdMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ThirdMenuWidget(QWidget *parent = 0);
    ~ThirdMenuWidget();

private:
    Ui::ThirdMenuWidget *ui;

public:
    void init_standard_model();
    void set_third_menu_name(int i, int j);
    void choose_widget_style(int k, QVariantMap thirdMenuMap, QString thirdMenuString);
    void resizeEvent(QResizeEvent *event);
    void set_model_item(int startIndex, QStringList thirdMenuList);
    void set_currentDateToMenu();
    void set_currentTimeToMenu();
    void set_currentIPToMenu();
    void set_currentSubNetToMenu();

    QStringList get_third_menu_list();
    QStringList get_translate_third_menu_list();
    QList<int> get_spinBox_range_list(QVariantMap variantMap);
    QStringList get_spinBox_step_list(QVariantMap variantMap);
    QList<QStringList> get_comboBox_option_list(QVariantMap variantMap);
    QList<QStringList> get_translate_comboBox_option_list(QVariantMap variantMapEng, QVariantMap variantMapTran);
    QStringList get_abbreviate_comboBox_option_list(QStringList stringList);
    QString set_long_contents_header(int index, QString string);
    QVariantMap get_translate_option_map(QString thirdMenuString);
    QList<int> get_dialog_value_list(int index, QString str);

    int width;
    int height;
    int currFirstNum;
    int currSecondNum;
    int measurementIndex;
    int inputIndex;
    int brightIndex;
    int probeIndex;
    int wedgeIndex;
    int dateTimeSetIndex;
    int networkIndex;
    int languageOption;
    int opendSpinBoxIndex;
    bool keyboardShowFlag;

    QStandardItemModel *model;
    FirstSecondMenuWidget *widget;
    QVariantMap secondMenuMap;
    QVariantMap menuCacheMap;
    QString firstMenuString;
    QString secondMenuString;
    QString relatedMenuString;

signals:
    void retranslate_ui(QString);
    void send_dialog_title_content(QMap<QString, QString>);
    void send_spinbox_value(QList<int>);

private:
    VerticalSliderDialog *verticalSliderDialog;
    Mcu *m_mcu;
    DateTimeSetDialog *dateTimeSetDialog;
    NetworkDialog *networkDialog;

signals:
    void translater_ZH();
    void translater_EN();
    void send_string_to_delegate(QString);

protected slots:
    void do_rotary_event(Mcu::RotaryType type);
    void do_probe_event(const Probe& probe);

private slots:
    void onHeaderClicked(int index);
    void change_related_third_menu_data(QString str);
    void set_header_text_create(QStringList stringList) const ;
    void set_header_text_close(QWidget *editor) ;
    void on_tableView_clicked(const QModelIndex &index);
    void change_measurement_label(QString string);
    void select_probe(QString string);
    void select_wedge(QString string);
    void set_edited_text(QString string);
    void setBrightValue(int value);
    void set_autoDetect_probeModel(bool flag);
    void set_date(QString str_date);
    void set_time(QString str_time);
    void set_ip(QString str_ip);
    void set_subNet(QString str_subNet);
    void retranslate_third_menu_ui(QString string);
    void open_spinbox_persistent_editor(int index);
    void close_spinbox_persistent_editor(int index);
    void input_spinbox_number(QString string);


};

#endif // THIRDMENUWIDGET_H
