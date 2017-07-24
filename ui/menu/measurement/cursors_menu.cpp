#include "cursors_menu.h"

#include "ui_base_menu.h"

namespace DplMeasurementMenu {

CursorsMenu::CursorsMenu(QWidget *parent) :
    BaseMenu(parent),
    m_selectionItem(new ComboMenuItem(this, tr("Selection"))),
    m_rItem(new SpinMenuItem(this, ("%(r)"), "%")),
    m_mItem(new SpinMenuItem(this, "%(m)", "%")),
    m_urItem(new SpinMenuItem(this, ("U(r)"), "mm")),
    m_umItem(new SpinMenuItem(this, "U(m)", "mm")),
    m_srItem(new SpinMenuItem(this, "S(r)", "s")),
    m_smItem(new SpinMenuItem(this, "S(m)", "s")),
    m_irItem(new SpinMenuItem(this, "I(r)", "mm")),
    m_imItem(new SpinMenuItem(this, "I(m)", "mm")),
    m_angelItem(new SpinMenuItem(this, tr("Angle"), "\260"))
{
    /* Selection menu item */
    QStringList selectionList;
    selectionList.append(tr("A-Scan"));
    selectionList.append(tr("B-Scan"));
    selectionList.append(tr("C-Scan"));
    selectionList.append(tr("S-Scan"));
    m_selectionItem->set(selectionList);
    connect(m_selectionItem, SIGNAL(value_changed(int)), this, SLOT(do_selectionItem_changed(int)));

    /* %(r) menu item */
    m_rItem->set(0, 100, 1);

    /* %(m) menu item */
    m_mItem->set(0, 100, 1);

    /* U(r) menu item */
    m_urItem->set(0, 2000, 2);

    /* U(m) menu item */
    m_umItem->set(0, 2000, 2);

    /* S(r) menu item */
    m_srItem->set(0, 10000, 1);

    /* S(m) menu item */
    m_smItem->set(0, 10000, 1);

    /* I(r) menu item */
    m_irItem->set(0, 2000, 1);

    /* I(m) menu item */
    m_imItem->set(0, 2000, 1);

    /* Angle menu item */
    m_angelItem->set(25, 75, 0);

    do_selectionItem_changed(0);
}

CursorsMenu::~CursorsMenu()
{
}

void CursorsMenu::show_scan()
{
    ui->layout0->addWidget(m_selectionItem);
    m_selectionItem->show();
    switch (m_selectionItem->current_index()) {
    case 0:
        /* A-Scan */
        show_a_scan();
        break;
    case 1:
        /* B-Scan */
        show_b_scan();
        break;
    case 2:
        /* C-Scan */
        show_c_scan();
        break;
    case 3:
        /* S-Scan */
        show_s_scan();
        break;
    default:
        break;
    }
}

void CursorsMenu::show_a_scan()
{
    ui->layout1->addWidget(m_rItem);
    ui->layout2->addWidget(m_mItem);
    ui->layout3->addWidget(m_urItem);
    ui->layout4->addWidget(m_umItem);
    m_rItem->show();
    m_mItem->show();
    m_urItem->show();
    m_umItem->show();
}

void CursorsMenu::hide_a_scan()
{
    ui->layout1->removeWidget(m_rItem);
    ui->layout2->removeWidget(m_mItem);
    ui->layout3->removeWidget(m_urItem);
    ui->layout4->removeWidget(m_umItem);
    m_rItem->hide();
    m_mItem->hide();
    m_urItem->hide();
    m_umItem->hide();
}

void CursorsMenu::show_b_scan()
{
    ui->layout1->addWidget(m_srItem);
    ui->layout2->addWidget(m_smItem);
    ui->layout3->addWidget(m_urItem);
    ui->layout4->addWidget(m_umItem);
    m_srItem->show();
    m_smItem->show();
    m_urItem->show();
    m_umItem->show();
}

void CursorsMenu::hide_b_scan()
{
    ui->layout1->removeWidget(m_srItem);
    ui->layout2->removeWidget(m_smItem);
    ui->layout3->removeWidget(m_urItem);
    ui->layout4->removeWidget(m_umItem);
    m_srItem->hide();
    m_smItem->hide();
    m_urItem->hide();
    m_umItem->hide();
}

void CursorsMenu::show_c_scan()
{
    ui->layout1->addWidget(m_srItem);
    ui->layout2->addWidget(m_smItem);
    ui->layout3->addWidget(m_irItem);
    ui->layout4->addWidget(m_imItem);
    m_srItem->show();
    m_smItem->show();
    m_irItem->show();
    m_imItem->show();
}

void CursorsMenu::hide_c_scan()
{
    ui->layout1->removeWidget(m_srItem);
    ui->layout2->removeWidget(m_smItem);
    ui->layout3->removeWidget(m_irItem);
    ui->layout4->removeWidget(m_imItem);
    m_srItem->hide();
    m_smItem->hide();
    m_irItem->hide();
    m_imItem->hide();
}

void CursorsMenu::show_s_scan()
{
    ui->layout1->addWidget(m_angelItem);
    ui->layout2->addWidget(m_urItem);
    ui->layout3->addWidget(m_umItem);
    ui->layout4->addWidget(m_irItem);
    ui->layout5->addWidget(m_imItem);
    m_angelItem->show();
    m_urItem->show();
    m_umItem->show();
    m_irItem->show();
    m_imItem->show();
}

void CursorsMenu::hide_s_scan()
{
    ui->layout1->removeWidget(m_angelItem);
    ui->layout2->removeWidget(m_urItem);
    ui->layout3->removeWidget(m_umItem);
    ui->layout4->removeWidget(m_irItem);
    ui->layout5->removeWidget(m_imItem);
    m_angelItem->hide();
    m_urItem->hide();
    m_umItem->hide();
    m_irItem->hide();
    m_imItem->hide();
}

void CursorsMenu::do_selectionItem_changed(int index)
{
    Q_UNUSED(index);
    hide_a_scan();
    hide_b_scan();
    hide_c_scan();
    hide_s_scan();
    show_scan();
}

}
