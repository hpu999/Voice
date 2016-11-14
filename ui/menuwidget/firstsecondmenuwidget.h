#ifndef FIRSTSECONDMENUWIDGET_H
#define FIRSTSECONDMENUWIDGET_H

#include <Parser>

#include <QWidget>
#include <QToolBox>
#include <QListView>
#include <QStandardItemModel>
#include <QFile>

#define FIRST_MENU_NUMBER 9
#define SECOND_MENU_NUMBER 5

namespace Ui{
class FirstSecondMenuWidget;
}

class FirstSecondMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FirstSecondMenuWidget(QWidget *parent = 0);
    ~FirstSecondMenuWidget();

private:
    Ui::FirstSecondMenuWidget *ui;

public:
    QList<QToolBox*> toolBox;
 //   QList<QWidget*> page;
    QList<QListView*> menuList;
    QList<QStandardItemModel*> modelList;
    QStringList firstMenuData;
    QVariantMap firstMenuMap;
    QVariantMap translateChineseMap;
    int languageOption;

    void set_second_menu_name(int i);
    void set_second_menu_item_style(int i, QModelIndex index);
    void init_ui();
    void retranslate_main_menu_ui(QString string);
    void resize_height(int i);
    QVariantMap read_json_file(QFile *file);
    QStringList get_second_menu_list(int i);    

private slots:

};

#endif // FIRSTSECONDMENUWIDGET_H
