#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_mcu = Mcu::get_mcu();
    ui->setupUi(this);

    connect(ui->pushButtonCoreTemp, &QPushButton::clicked, m_mcu, &Mcu::query_core_temp);
    connect(ui->pushButtonFpgaTemp, &QPushButton::clicked, m_mcu, &Mcu::query_fpga_temp);
    connect(ui->pushButtonPowerTemp, &QPushButton::clicked, m_mcu, &Mcu::query_power_temp);
    connect(ui->pushButtonMcuTemp, &QPushButton::clicked, m_mcu, &Mcu::query_mcu_temp);
    connect(ui->pushButtonFstBattery, &QPushButton::clicked, m_mcu, &Mcu::query_first_battery);
    connect(ui->pushButtonFstBatteryStatus, &QPushButton::clicked, m_mcu, &Mcu::query_first_battery_status);
    connect(ui->pushButtonSndBattery, &QPushButton::clicked, m_mcu, &Mcu::query_second_battery);
    connect(ui->pushButtonSndBatteryStatus, &QPushButton::clicked, m_mcu, &Mcu::query_second_battery_status);

    connect(m_mcu, &Mcu::event, this, &MainWindow::on_mcu_event);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_mcu_event(Mcu::PkgCmd type, QByteArray &data)
{
    switch (type) {
    case Mcu::CORE_TEMPERATURE:
        ui->labelCoreTemp->setText(QString::number(data.toHex().toInt(0, 16)));
        break;
    case Mcu::MCU_TEMPERATUREE:
        ui->labelMcuTemp->setText(QString::number(data.toHex().toInt(0, 16)));
        break;
    case Mcu::FPGA_TEMPERATURE:
        ui->labelFpgaTemp->setText(QString::number(data.toHex().toInt(0, 16)));
        break;
    case Mcu::POWER_TEMPERATURE:
        ui->labelPowerTemp->setText(QString::number(data.toHex().toInt(0, 16)));
        break;
    case Mcu::BATTERY1_STATUS:
        ui->labelFstBatteryStatus->setText(QString::number(data.toHex().toInt(0, 16)));
        break;
    case Mcu::BATTERY1_QUANTITY:
        ui->labelFstBattery->setText(QString::number(data.toHex().toInt(0, 16)));
        break;
    case Mcu::BATTERY2_STATUS:
        ui->labelSndBatteryStatus->setText(QString::number(data.toHex().toInt(0, 16)));
        break;
    case Mcu::BATTERY2_QUANTITY:
        ui->labelSndBattery->setText(QString::number(data.toHex().toInt(0, 16)));
        break;
    case Mcu::KEY:
    case Mcu::ROTARY:
        ui->labelKey->setText(QString::number(data.toHex().toInt(0, 16)));
        break;
    default:
        break;
    }
}
