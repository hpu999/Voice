/**
 * @file label_menu_item.cpp
 * @brief label menu item
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "label_menu_item.h"

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

LabelMenuItem::LabelMenuItem(QWidget *parent, const QString &title, const QString &text) :
    MenuItem(parent),
    m_pushBtn(new QPushButton(title, this)),
    m_label(new QLabel(text, this))
{
    update_layout(m_pushBtn, m_label);
    m_label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    m_pushBtn->setFocusPolicy(Qt::NoFocus);

    connect(m_pushBtn, SIGNAL(clicked()),
            this, SIGNAL(clicked()));
}

LabelMenuItem::~LabelMenuItem()
{
}

QString LabelMenuItem::title() const
{
    return m_pushBtn->text();
}

void LabelMenuItem::set_title(const QString &title)
{
    m_pushBtn->setText(title);
}

QString LabelMenuItem::text() const
{
    return m_label->text();
}

void LabelMenuItem::set_text(const QString &text)
{
    m_label->setText(text);
}
