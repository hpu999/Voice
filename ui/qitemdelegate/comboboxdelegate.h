#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QItemDelegate>
#include <QWidget>

class ComboBoxDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    ComboBoxDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index)const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index)const;
    void set_comboBox_item_list(QStringList stringList);
    void set_model_item_list(QStringList stringList);
    void set_minimum_contents_length(int width);
    int find_list_index(QStringList stringList, QString string) const;

    QStringList itemList;
    QStringList modelItemList;
    int minimumContentLength;

signals:
    void comboBox_current_text(QString);

private slots:
    void commit_and_close_editor(const QString &str);
};

#endif // COMBOBOXDELEGATE_H
