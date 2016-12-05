#ifndef INPUTPANELCONTEXT_H
#define INPUTPANELCONTEXT_H

#include <QDialog>

namespace Ui {
class InputPanelContext;
}

class InputPanelContext : public QDialog
{
    Q_OBJECT

public:
    explicit InputPanelContext(QWidget *parent = 0);
    ~InputPanelContext();

    void set_item_current_text(QString string);

private:
    Ui::InputPanelContext *ui;

    bool m_capsLock;

signals:
    void textEditFinished(QString);

private slots:
    void edit_text();
    void on_pushButton_capsLock_clicked();
    void on_pushButton_Space_clicked();
    void on_pushButton_BackSpace_clicked();
    void on_pushButton_ok_clicked();
    void on_pushButton_arrow_left_clicked();
    void show_cursor();
    void on_pushButton_arrow_right_clicked();
    void on_pushButton_arrow_up_clicked();
    void on_pushButton_arrow_down_clicked();
};

#endif // INPUTPANELCONTEXT_H