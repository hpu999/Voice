#ifndef IPSETDIALOG_H
#define IPSETDIALOG_H

#include <QDialog>

namespace Ui {
class IPSetDialog;
}

class IPSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IPSetDialog(QWidget *parent = 0);
    ~IPSetDialog();

private:
    Ui::IPSetDialog *ui;

public:
    void retranslate_dialog_ui();
    QString str_ip;

private:
    void init_ui();

signals:
    void currentIPChanged(QString IP);

public slots:
    void on_buttonBox_accepted();

};

#endif // IPSETDIALOG_H
