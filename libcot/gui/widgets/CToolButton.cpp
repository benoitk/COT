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

QPixmap CToolButton::buttonPixmap(const QString &name)
{
    // TODO_KDAB: To be computed
    const bool isHd = true;
    return QPixmap(isHd
                   ? QString(":/hd-icons/pictohd/%1").arg(name)
                   : QString(":/icons/picto/%1").arg(name));
}

QIcon CToolButton::buttonIcon(CToolButton::Type type)
{
    QIcon icon;

    // enum Mode { Normal, Disabled, Selected };
    switch (type) {
        case CToolButton::StopEndCycle:
        case CToolButton::NextStream:
        case CToolButton::Update:
        case CToolButton::Configure:
        case CToolButton::AddVariable:
        case CToolButton::Delete:
            // TODO_KDAB:: Handle each icon set in picto / pictohd resources.
            break;

        case CToolButton::Play:
            icon.addPixmap(buttonPixmap("30x30 lancer maintenance.png"), QIcon::Normal, QIcon::Off);
            icon.addPixmap(buttonPixmap("30x30 lancer maintenance active.png"), QIcon::Selected, QIcon::Off);
            icon.addPixmap(buttonPixmap("30x30 lancer maintenance grisee.png"), QIcon::Disabled, QIcon::Off);
            break;

        case CToolButton::Stop:
            icon.addPixmap(buttonPixmap("40x40 stop mesure.png"), QIcon::Normal, QIcon::Off);
            icon.addPixmap(buttonPixmap("40x40 stop mesure active.png"), QIcon::Selected, QIcon::Off);
            break;

        case CToolButton::Alarms:
            icon.addPixmap(buttonPixmap("40x40 alarme mesure.png"), QIcon::Normal, QIcon::Off);
            icon.addPixmap(buttonPixmap("40x40 alarme mesure active.png"), QIcon::Selected, QIcon::Off);
            break;

        case CToolButton::AlarmsActive:
            icon.addPixmap(buttonPixmap("40x40 alarme mesure gif.png"), QIcon::Normal, QIcon::Off);
            icon.addPixmap(buttonPixmap("40x40 alarme mesure active.png"), QIcon::Selected, QIcon::Off);
            break;

        case CToolButton::ScrollUp:
            icon.addPixmap(buttonPixmap("75x75 fleche haut.png"), QIcon::Normal, QIcon::Off);
            icon.addPixmap(buttonPixmap("75x75 fleche haut active.png"), QIcon::Selected, QIcon::Off);
            icon.addPixmap(buttonPixmap("75x75 fleche haut grisee.png"), QIcon::Disabled, QIcon::Off);
            break;

        case CToolButton::ScrollDown:
            icon.addPixmap(buttonPixmap("75x75 fleche bas.png"), QIcon::Normal, QIcon::Off);
            icon.addPixmap(buttonPixmap("75x75 fleche bas active.png"), QIcon::Selected, QIcon::Off);
            icon.addPixmap(buttonPixmap("75x75 fleche bas grisee.png"), QIcon::Disabled, QIcon::Off);
            break;

        case CToolButton::Back:
            icon.addPixmap(buttonPixmap("40x40 quitter.png"), QIcon::Normal, QIcon::Off);
            icon.addPixmap(buttonPixmap("40x40 quitter active.png"), QIcon::Selected, QIcon::Off);
            icon.addPixmap(buttonPixmap("40x40 quitter grisee.png"), QIcon::Disabled, QIcon::Off);
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

        case CToolButton::Maintenance:
            icon.addPixmap(buttonPixmap("50x50 menu maintenance.png"), QIcon::Normal, QIcon::Off);
            icon.addPixmap(buttonPixmap("50x50 menu maintenance active.png"), QIcon::Selected, QIcon::Off);
            break;

        case CToolButton::ElectricalTests:
            icon.addPixmap(buttonPixmap("50x50 menu carte mesure.png"), QIcon::Normal, QIcon::Off);
            icon.addPixmap(buttonPixmap("50x50 menu carte mesure active.png"), QIcon::Selected, QIcon::Off);
            break;

        case CToolButton::Options:
            icon.addPixmap(buttonPixmap("50x50 menu sequenceur.png"), QIcon::Normal, QIcon::Off);
            icon.addPixmap(buttonPixmap("50x50 menu sequenceur active.png"), QIcon::Selected, QIcon::Off);
            break;

        case CToolButton::History:
            icon = QIcon(buttonPixmap("50x50 historique.png"));
            break;

        case CToolButton::LogFiles:
            icon.addPixmap(buttonPixmap("50x50 transfert copie.png"), QIcon::Normal, QIcon::Off);
            icon.addPixmap(buttonPixmap("50x50 transfert copie actif.png"), QIcon::Selected, QIcon::Off);
            break;

        case CToolButton::Quit:
            icon.addPixmap(buttonPixmap("40x40 quitter.png"), QIcon::Normal, QIcon::Off);
            icon.addPixmap(buttonPixmap("40x40 quitter active.png"), QIcon::Selected, QIcon::Off);
            icon.addPixmap(buttonPixmap("40x40 quitter grisee.png"), QIcon::Disabled, QIcon::Off);
            break;

        case CToolButton::MeasureDetails:
            icon.addPixmap(buttonPixmap("35x35 detail mesure.png"), QIcon::Normal, QIcon::Off);
            icon.addPixmap(buttonPixmap("35x35 detail mesure active.png"), QIcon::Selected, QIcon::Off);
            break;

        case CToolButton::Ok:
            icon.addPixmap(buttonPixmap("40x40 appliquer.png"), QIcon::Normal, QIcon::Off);
            icon.addPixmap(buttonPixmap("40x40 appliquer active.png"), QIcon::Selected, QIcon::Off);
            icon.addPixmap(buttonPixmap("40x40 appliquer grisee.png"), QIcon::Disabled, QIcon::Off);
            break;

        case CToolButton::Cancel:
            icon.addPixmap(buttonPixmap("50x50 annule.png"), QIcon::Normal, QIcon::Off);
            break;

        case CToolButton::Informations:
            icon.addPixmap(buttonPixmap("50x50 menu information.png"), QIcon::Normal, QIcon::Off);
            icon.addPixmap(buttonPixmap("50x50 menu information active.png"), QIcon::Selected, QIcon::Off);
            break;

        case CToolButton::CreateRecovery:
        case CToolButton::RestoreConfig:
            icon.addPixmap(buttonPixmap("50x50 menu sauvegarde.png"), QIcon::Normal, QIcon::Off);
            icon.addPixmap(buttonPixmap("50x50 menu sauvegarde active.png"), QIcon::Selected, QIcon::Off);
            break;

        case CToolButton::Invalid:
            break;
    }

    return icon;
}
