#include "measurementdialog.h"
#include "ui_measurementdialog.h"

MeasurementDialog::MeasurementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeasurementDialog)
{
    ui->setupUi(this);
}

MeasurementDialog::~MeasurementDialog()
{
    delete ui;
}
