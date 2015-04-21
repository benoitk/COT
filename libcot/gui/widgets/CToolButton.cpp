#include "CToolButton.h"

#include <QAction>
#include <QTimer>
#include <QPainter>

CToolButton::CToolButton(QWidget *parent)
    : QToolButton(parent)
{
    initialize();

}

CToolButton::CToolButton(QAction *action, QWidget *parent)
    : QToolButton(parent)
{
    Q_ASSERT(action);
    initialize(CToolButton::Invalid, action);
}

CToolButton::CToolButton(CToolButton::Type type, QWidget *parent)
    : QToolButton(parent)
{
    initialize(type);
}

CToolButton::CToolButton(CToolButton::Type type, QAction *action, QWidget *parent)
    : QToolButton(parent)
{
    Q_ASSERT(action);
    initialize(type, action);
}

void CToolButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (isEnabled()) {
        if (isChecked()) {
            icon().paint(&painter, rect(), Qt::AlignCenter, QIcon::Selected, QIcon::Off);
        }
        else {
            icon().paint(&painter, rect(), Qt::AlignCenter, QIcon::Normal, QIcon::Off);
        }
    }
    else {
        icon().paint(&painter, rect(), Qt::AlignCenter, QIcon::Disabled, QIcon::Off);
    }
}

void CToolButton::initialize(CToolButton::Type type, QAction *action)
{
    setFixedSize(30, 30);

    if (action) {
        setDefaultAction(action);
        QTimer::singleShot(25, this, &CToolButton::updateVisibility);
        connect(action, &QAction::changed, this, &CToolButton::updateVisibility);
    }

    if (icon().isNull()) {
        setIcon(CToolButton::buttonIcon(type));
    }
}

void CToolButton::updateVisibility()
{
    setVisible(defaultAction()->isVisible());
}

QPixmap CToolButton::buttonPixmap(const QString &name)
{
    // TODO_KDAB: To be computed
    const bool isHd = true;
    return QPixmap(isHd
            ? QString(":/hd-icons/pictohd/%1").arg(name)
            : QString(":/icons/picto/%1").arg(name)
    );
}

QIcon CToolButton::buttonIcon(CToolButton::Type type)
{
    QIcon icon;

    // enum Mode { Normal, Disabled, Selected };
    switch (type) {
    case CToolButton::Alarms:
    case CToolButton::Play:
    case CToolButton::Stop:
    case CToolButton::StopEndCycle:
    case CToolButton::NextStream:
    case CToolButton::ScrollUp:
    case CToolButton::ScrollDown:
    case CToolButton::Back:
    case CToolButton::Update:
        // TODO_KDAB:: Handle each icon set in picto / pictohd resources.
        break;

    case CToolButton::On:
        icon.addPixmap(buttonPixmap("30x30 on.png"), QIcon::Normal, QIcon::Off);
        icon.addPixmap(buttonPixmap("30x30 on active.png"), QIcon::Selected, QIcon::Off);
        icon.addPixmap(buttonPixmap("30x30 on grisee.png"), QIcon::Disabled, QIcon::Off);
        break;

    case CToolButton::Off:
        icon.addPixmap(buttonPixmap("30x30 off.png"), QIcon::Normal, QIcon::Off);
        icon.addPixmap(buttonPixmap("30x30 off active.png"), QIcon::Selected, QIcon::Off);
        icon.addPixmap(buttonPixmap("30x30 off grisee.png"), QIcon::Disabled, QIcon::Off);
        break;

    case CToolButton::Led:
        icon.addPixmap(buttonPixmap("30x30 Ana-tor inactive.png"), QIcon::Normal, QIcon::Off);
        icon.addPixmap(buttonPixmap("30x30 Ana-tor active.png"), QIcon::Selected, QIcon::Off);
        break;

    case CToolButton::Invalid:
        break;
    }

    return icon;
}
