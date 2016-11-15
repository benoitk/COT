#include "CLabelledToolButton.h"
#include "StyleRepository.h"
#include <QLabel>
#include <QVBoxLayout>

CLabelledToolButton::CLabelledToolButton(CToolButton::Type type, QWidget *parent)
    : QWidget(parent)
    , m_toolButton(new CToolButton(type, this))
    , m_label(new QLabel(this))
{
    initialize();
}

CLabelledToolButton::CLabelledToolButton(CToolButton::Type type, QAction *action, QWidget *parent)
    : QWidget(parent)
    , m_toolButton(new CToolButton(type, action, this))
    , m_label(new QLabel(this))
{
    initialize();
}

CToolButton::Type CLabelledToolButton::type() const
{
    return m_toolButton->type();
}

void CLabelledToolButton::setType(CToolButton::Type type)
{
    m_toolButton->setType(type);
}

QString CLabelledToolButton::text() const
{
    return m_label->text();
}

void CLabelledToolButton::setText(const QString &text)
{
    m_label->setText(text);
}

void CLabelledToolButton::initialize()
{
    QVBoxLayout *vl = new QVBoxLayout(this);
    vl->setMargin(0);
    vl->addWidget(m_toolButton, 0, Qt::AlignCenter);
    vl->addWidget(m_label, 0, Qt::AlignCenter);
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_label->setFont(StyleRepository::labelledToolButtonFont());
    connect(m_toolButton, &CToolButton::clicked, this, &CLabelledToolButton::clicked);
}
