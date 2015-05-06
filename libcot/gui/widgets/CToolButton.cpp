#include "CToolButton.h"

#include <QAction>
#include <QTimer>
#include <QPainter>
#include <QFile>
#include <QDebug>

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

CToolButton::Type CToolButton::type() const
{
    return m_type;
}

void CToolButton::setType(CToolButton::Type type)
{
    if (m_type != type) {
        m_type = type;
        setIcon(buttonIcon(type));
    }
}

QVariant CToolButton::userData() const
{
    return m_userData;
}

void CToolButton::setUserData(const QVariant &userData)
{
    m_userData = userData;
}

void CToolButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (isEnabled()) {
        if (isChecked() || isDown()) {
            icon().paint(&painter, rect(), Qt::AlignCenter, QIcon::Selected, QIcon::Off);
        }
        else {
            icon().paint(&painter, rect(), Qt::AlignCenter, QIcon::Normal, QIcon::Off);
        }
    }
    else {
        icon().paint(&painter, rect(), Qt::AlignCenter, QIcon::Disabled, QIcon::Off);
    }

    // TODO_KDAB: Just for debug until all icons types are handled
    if (icon().isNull()) {
        painter.setPen(Qt::black);
        painter.drawRect(rect());
    }
}

void CToolButton::initialize(CToolButton::Type type, QAction *action)
{
    Q_ASSERT(type != CToolButton::AlarmsActive); // That's not a real button but a state.
    m_type = type;

    setFixedSize(50, 50);

    if (action && action->icon().isNull()) {
        action->setIcon(CToolButton::buttonIcon(type));
    }

    if (action) {
        setDefaultAction(action);
        QTimer::singleShot(25, this, &CToolButton::updateVisibility);
        connect(action, &QAction::changed, this, &CToolButton::updateVisibility);
    }
    else {
        setIcon(CToolButton::buttonIcon(type));
    }

    if (type == CToolButton::ScrollUp || type == CToolButton::ScrollDown) {
        setAutoRepeat(true);
    }
}

void CToolButton::updateVisibility()
{
    setVisible(defaultAction()->isVisible());
}

QIcon CToolButton::iconFromPixmaps(const QString &baseName)
{
    QIcon icon;
    const QString mainPixmapPath = pixmapFilePath(baseName + ".png");
    if (!QFile::exists(mainPixmapPath)) {
        qWarning() << "Icon not found:" << mainPixmapPath;
        return icon;
    }
    icon.addPixmap(QPixmap(mainPixmapPath), QIcon::Normal, QIcon::Off);

    // Try adding the selected and disabled versions as well.
    // If they don't exist, we'll get a null QPixmap, and addPixmap won't do anything to the QIcon.
    icon.addPixmap(QPixmap(pixmapFilePath(baseName + " active.png")), QIcon::Selected, QIcon::Off);
    icon.addPixmap(QPixmap(pixmapFilePath(baseName + " grisee.png")), QIcon::Disabled, QIcon::Off);
    return icon;
}

QString CToolButton::pixmapFilePath(const QString &name)
{
    // TODO_KDAB: To be computed
    const bool isHd = true;
    return isHd ? QString(":/hd-icons/pictohd/%1").arg(name)
                : QString(":/icons/picto/%1").arg(name);
}

QIcon CToolButton::buttonIcon(CToolButton::Type type)
{
    QIcon icon;

    // enum Mode { Normal, Disabled, Selected };
    switch (type) {
        case CToolButton::StopEndCycle:
        case CToolButton::NextStream:
        case CToolButton::Update:
            // TODO_KDAB:: Handle each icon set in picto / pictohd resources.
            break;

        case CToolButton::Add:
            icon = iconFromPixmaps("30x30 Plus");
            break;

        case CToolButton::Remove:
            icon = iconFromPixmaps("30x30 moins");
            break;

        case CToolButton::Play:
            icon = iconFromPixmaps("30x30 lancer maintenance");
            break;

        case CToolButton::Stop:
            icon = iconFromPixmaps("40x40 stop mesure");
            break;

        case CToolButton::Alarms:
            icon = iconFromPixmaps("40x40 alarme mesure");
            break;

        case CToolButton::AlarmsActive:
            icon = iconFromPixmaps("40x40 alarme mesure gif");
            break;

        case CToolButton::ScrollUp:
            icon = iconFromPixmaps("75x75 fleche haut");
            break;

        case CToolButton::ScrollDown:
            icon = iconFromPixmaps("75x75 fleche bas");
            break;

        case CToolButton::Back:
        case CToolButton::Quit:
            icon = iconFromPixmaps("40x40 quitter");
            break;

        case CToolButton::On:
            icon = iconFromPixmaps("30x30 on");
            break;

        case CToolButton::Off:
            icon = iconFromPixmaps("30x30 off");
            break;

        case CToolButton::Led:
            icon = iconFromPixmaps("30x30 Ana-tor");
            break;

        case CToolButton::Maintenance:
            icon = iconFromPixmaps("50x50 menu maintenance");
            break;

        case CToolButton::ElectricalTests:
            icon = iconFromPixmaps("50x50 menu carte mesure");
            break;

        case CToolButton::Options:
            icon = iconFromPixmaps("50x50 menu sequenceur");
            break;

        case CToolButton::History:
            icon = iconFromPixmaps("50x50 historique");
            break;

        case CToolButton::LogFiles:
            icon = iconFromPixmaps("50x50 transfert copie");
            break;

        case CToolButton::MeasureDetails:
        case CToolButton::Configure: // TODO: need a different icon for this one
            icon = iconFromPixmaps("35x35 detail mesure");
            break;

        case CToolButton::Ok:
            icon = iconFromPixmaps("40x40 appliquer");
            break;

        case CToolButton::Cancel:
        case CToolButton::Delete:
            icon = iconFromPixmaps("50x50 annule");
            break;

        case CToolButton::Informations:
            icon = iconFromPixmaps("50x50 menu information");
            break;

        case CToolButton::CreateRecovery:
        case CToolButton::RestoreConfig:
            icon = iconFromPixmaps("50x50 menu sauvegarde");
            break;

        case CToolButton::Invalid:
            break;
    }

    return icon;
}
