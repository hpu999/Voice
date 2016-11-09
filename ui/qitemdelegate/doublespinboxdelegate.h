#ifndef DOUBLESPINBOXDELEGATE_H
#define DOUBLESPINBOXDELEGATE_H

#include "mcu.h"

#include <QStyledItemDelegate>
#include <QDoubleSpinBox>

class DoubleSpinBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    DoubleSpinBoxDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void set_number_range(QList<int> list);
    void set_number_step_list(QStringList stringList);
    void set_number_step(QString string);   
    void set_decimal_amount(int amount);
    QString get_number_step();

    QList<QDoubleSpinBox*> spinBoxList;
    QList<int> rangeList;
    QMap<QModelIndex, QDoubleSpinBox*> spinBoxMap;
    QStringList stepList;
    QString step;
    int decimalAmount;
    int inputCount;
    bool editFlag;
    bool keyboardShowFlag;

//    void simulate_key(int fd, int value);

private:
    Mcu *m_mcu;

signals:
    void createEditorHeaderText(QStringList) const;
    void closeEditorHeaderText(QModelIndex) const;
    void stringChanged(double value);

private slots:
    void commit_and_close_editor();
    void do_rotary_event(Mcu::RotaryType type);
    void key_sure(Mcu::KeyType key);
    void input_number_to_lineedit(QString string);
    void valueChanged_signal(double value);

protected slots:
    void input_number(QString string);
};

#endif // DOUBLESPINBOXDELEGATE_H
