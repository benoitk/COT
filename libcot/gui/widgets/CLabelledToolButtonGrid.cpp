#include "CLabelledToolButtonGrid.h"
#include "CLabelledToolButton.h"

#include <QGridLayout>

CLabelledToolButtonGrid::CLabelledToolButtonGrid(QWidget *parent)
    : QWidget(parent)
    , m_layout(Q_NULLPTR)
    , m_layoutWidth(2)
{
}

CLabelledToolButtonGrid::CLabelledToolButtonGrid(int layoutWidth, QWidget *parent)
    : QWidget(parent)
    , m_layout(Q_NULLPTR)
    , m_layoutWidth(layoutWidth)
{
}

void CLabelledToolButtonGrid::setButtons(const QList<CLabelledToolButton *> buttons)
{
    delete m_layout;
    m_layout = new QGridLayout(this);
    m_layout->setMargin(0);

    qDeleteAll(m_buttons.values());
    m_buttons.clear();

    int x = 0;
    int y = 0;

    foreach (CLabelledToolButton *button, buttons) {
        Q_ASSERT(!m_buttons.contains(button->type()));
        m_buttons[button->type()] = button;
        m_layout->addWidget(button, y, x, Qt::AlignCenter);
        connect(button, &CLabelledToolButton::clicked, this, &CLabelledToolButtonGrid::slotClicked);

        x++;
        if (x == m_layoutWidth) {
            x = 0;
            y++;
        }
    }
}

void CLabelledToolButtonGrid::setButtons(const QList<CToolButton::Type> buttons)
{
    QList<CLabelledToolButton *> buttonsList;

    foreach (CToolButton::Type type, buttons) {
        buttonsList << new CLabelledToolButton(type, this);
    }

    setButtons(buttonsList);
}

CLabelledToolButton *CLabelledToolButtonGrid::button(CToolButton::Type type) const
{
    return m_buttons.value(type, Q_NULLPTR);
}

void CLabelledToolButtonGrid::slotClicked()
{
    CLabelledToolButton *button = qobject_cast<CLabelledToolButton *>(sender());

    emit clicked(button);
    emit typeClicked(button->type());
}
