#include "commonmenuwidget.h"
#include "ui_commonmenuwidget.h"

#include "doublespinboxdelegate.h"
#include "comboboxdelegate.h"

#include <QResizeEvent>

CommonMenuWidget::CommonMenuWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CommonMenuWidget)
{
  ui->setupUi(this);
  this->resize(800, 72);

  initStandardModel();
}

CommonMenuWidget::~CommonMenuWidget()
{
  delete ui;
}

void CommonMenuWidget::initStandardModel()
{
  model = new QStandardItemModel(1, COMMON_MENU_NUMBER, this);
  ui->tableView->setModel(model);
//  ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableView->horizontalHeader()->setFixedHeight(height * 45 / 70);
  ui->tableView->verticalHeader()->setDefaultSectionSize(height * 25 / 70);
  ui->tableView->verticalHeader()->hide();
  ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section"
                                                   "{font: 11pt 'Times New Roman';background-color: rgba(0, 130, 195, 255);"
                                                   "color:rgba(255, 255, 255, 255);"
                                                   "border: 0px solid black;"
                                                   "border-left:1px solid qlineargradient(spread:reflect, x1:0.5, y1:0.068, x2:0.5, y2:0.75, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(255, 255, 255, 255));"
                                                   "border-right:1px solid qlineargradient(spread:reflect, x1:0.5, y1:0.028, x2:0.5, y2:1, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(0, 0, 0, 255));}");

  ui->tableView->setStyleSheet("QTableView::item{"
                               "border-left:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1, stop:0.158192 rgb(255, 255, 255), stop:0.757062 rgb(0, 120, 195));"
                               "border-right:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1, stop:0.158192 rgb(0, 0, 0), stop:0.757062 rgb(0, 120, 195));}");


  for(int k = 0; k < COMMON_MENU_NUMBER; k++)
  {
    QModelIndex index = model->index(k, 0, QModelIndex());
    model->setData(index, k);

    widgetStyleChoice(k);
  }

  ui->tableView->show();
}

void CommonMenuWidget::setCommonMenuName()
{
  initStandardModel();
  for(int k = 0; k < COMMON_MENU_NUMBER; k ++)
  {
    if(COMMON_MENU_STRING[k] != NULL)
    {
      widgetStyleChoice(k);
      model->item(0, k)->setTextAlignment(Qt::AlignCenter);
      model->item(0, k)->setForeground(Qt::yellow);
      model->item(0, k)->setFont(QFont("Times New Roman", 11));
      QLinearGradient linearGradient(QPointF(0, 0), QPointF(0, 25));
      linearGradient.setColorAt(0.4, QColor(0, 0, 0));
      linearGradient.setColorAt(1,QColor(0, 120, 195));
      linearGradient.setSpread(QGradient::PadSpread);
      model->item(0, k)->setBackground(QBrush(linearGradient));
    }
  }
}

void CommonMenuWidget::widgetStyleChoice(int k)
{
  model->setHeaderData(k, Qt::Horizontal, COMMON_MENU_STRING[k]);
  switch(CHOICE_WIDGET_CHAR[k].toInt())
  {
  case 1:
    {
      DoubleSpinBoxDelegate *doubleSpinBox = new DoubleSpinBoxDelegate(this);
      model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
      QStandardItem *item = new QStandardItem(QString::number(0, 'f', 2));
      model->setItem(0, k, item);
      ui->tableView->setItemDelegateForColumn(k, doubleSpinBox);
      ui->tableView->setEditTriggers(QAbstractItemView::CurrentChanged);
      break;
    }
  case 2:
    {
      ComboBoxDelegate *comboBox = new ComboBoxDelegate(this);
      model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
      QStandardItem *item = new QStandardItem(QString("off"));
      model->setItem(0, k, item);
      ui->tableView->setItemDelegateForColumn(k, comboBox);
      break;
    }
  case 3:
    {
      model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
      QStandardItem *item = new QStandardItem(QString("on"));
      model->setItem(0, k, item);
      model->item(0, k)->setFlags(Qt::NoItemFlags);
      break;
    }
  default:
    break;
  }
}

void CommonMenuWidget::resizeEvent(QResizeEvent *event)
{
  width = event->size().width();
  height = event->size().height();
  model->clear();
  initStandardModel();
  setCommonMenuName();
}
