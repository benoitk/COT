#include "CToolButton.h"

#include <QAction>
#include <QTimer>
#include <QPainter>
#include <QFile>
#include <QMetaEnum>
#include <StyleRepository.h>
#include "cotgui_debug.h"

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

        if (defaultAction()) {
            defaultAction()->setIcon(buttonIcon(type));
        }
        else {
            setIcon(buttonIcon(type));
        }

        updateDefaultText();
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

    if (m_type == CToolButton::Empty || icon().isNull()) {
        painter.drawText(rect(), Qt::AlignCenter | Qt::TextWrapAnywhere, text());
    }

    // KDAB_TODO: Just for debug until all icons types are handled
    if (icon().isNull()) {
        painter.setPen(Qt::black);
        painter.drawRect(rect());
    }
}

void CToolButton::initialize(CToolButton::Type type, QAction *action)
{
    Q_ASSERT(type != CToolButton::AlarmsActive); // That's not a real button but a state.
    m_type = type;

    setFixedSize(StyleRepository::verticalBarButtonSize());

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

    switch (type) {
    case CToolButton::Back:
    case CToolButton::Quit:
    case CToolButton::Cancel: {
        if (action) {
            action->setShortcut(QKeySequence(Qt::Key_Escape));
        }
        else {
            setShortcut(QKeySequence(Qt::Key_Escape));
        }

        break;
    }

    default:
        break;
    }

    updateDefaultText();
}

void CToolButton::updateVisibility()
{
    setVisible(defaultAction()->isVisible());
}

void CToolButton::updateDefaultText()
{
    if (text().isEmpty()) {
        if (defaultAction()) {
            defaultAction()->setText(CToolButton::typeToString(m_type));
        }
        else {
            setText(CToolButton::typeToString(m_type));
        }
    }
}

// SERES_TODO: Create uniforms icon size.
// Upscale smaller icons until fixed.
QPixmap CToolButton::createPixmap(const QString &filePath)
{
    QPixmap pixmap(filePath);

    if (!pixmap.isNull() && pixmap.width() < 50) {
        pixmap = pixmap.scaledToWidth(50, Qt::SmoothTransformation);
    }

    return pixmap;
}

QIcon CToolButton::iconFromPixmaps(const QString &baseName)
{
    QIcon icon;
    const QString mainPixmapPath = pixmapFilePath(baseName + ".png");
    if (!QFile::exists(mainPixmapPath)) {
        qCWarning(COTGUI_LOG) << "Icon not found:" << mainPixmapPath;
        return icon;
    }
    icon.addPixmap(createPixmap(mainPixmapPath), QIcon::Normal, QIcon::Off);

    // Try adding the selected and disabled versions as well.
    // If they don't exist, we'll get a null QPixmap, and addPixmap won't do anything to the QIcon.
    icon.addPixmap(createPixmap(pixmapFilePath(baseName + " active.png")), QIcon::Selected, QIcon::Off);
    icon.addPixmap(createPixmap(pixmapFilePath(baseName + " grisee.png")), QIcon::Disabled, QIcon::Off);
    return icon;
}

QString CToolButton::pixmapFilePath(const QString &name)
{
    const bool isHd = StyleRepository::screenSize() == StyleRepository::TenInch;
    return QString(":/hd-icons/pictohd/%1").arg(name);
    //return isHd ? QString(":/hd-icons/pictohd/%1").arg(name)
    //            : QString(":/icons/picto/%1").arg(name);
}

QIcon CToolButton::buttonIcon(CToolButton::Type type)
{
    QIcon icon;

    // enum Mode { Normal, Disabled, Selected };
    switch (type) {
    case CToolButton::StopEndCycle:
        icon = iconFromPixmaps("arret fin cycle");
        break;

    case CToolButton::NextStream:
        icon = iconFromPixmaps("next mesure");
        break;
    case CToolButton::Update:
        icon = iconFromPixmaps("chargement");
        break;
    case CToolButton::Copy:
    case CToolButton::Move:
    case CToolButton::AddStopStep:
    case CToolButton::Edit:
    case CToolButton::Retry:
    case CToolButton::Screenshot:
        // SERES_TODO: Add correct icons. // COT-66
        break;

    case CToolButton::Empty:
        icon = iconFromPixmaps("empty");
        break;

    case CToolButton::Add:
        icon = iconFromPixmaps("Plus");
        break;

    case CToolButton::Remove:
        icon = iconFromPixmaps("moins");
        break;

    case CToolButton::PlayStop:
        icon = iconFromPixmaps("play stop");
        break;

    case CToolButton::Play:
        icon = iconFromPixmaps("lancer maintenance");
        break;

    case CToolButton::Stop:
        icon = iconFromPixmaps("stop mesure");
        break;

    case CToolButton::Alarms:
        icon = iconFromPixmaps("alarme mesure");
        break;

    case CToolButton::AlarmsActive:
        icon = iconFromPixmaps("alarme mesure gif");
        break;

    case CToolButton::ScrollUp:
        icon = iconFromPixmaps("fleche haut");
        break;

    case CToolButton::ScrollDown:
        icon = iconFromPixmaps("fleche bas");
        break;

    case CToolButton::Back:
    case CToolButton::Quit:
        icon = iconFromPixmaps("quitter");
        break;

    case CToolButton::On:
        icon = iconFromPixmaps("on");
        break;

    case CToolButton::Off:
        icon = iconFromPixmaps("off");
        break;

    case CToolButton::Led:
        icon = iconFromPixmaps("Ana-tor");
        break;

    case CToolButton::Maintenance:
        icon = iconFromPixmaps("menu maintenance");
        break;

    case CToolButton::ElectricalTests:
        icon = iconFromPixmaps("menu carte mesure");
        break;

    case CToolButton::Options:
        icon = iconFromPixmaps("menu sequenceur");
        break;

    case CToolButton::History:
        icon = iconFromPixmaps("historique");
        break;

    case CToolButton::LogFiles:
        icon = iconFromPixmaps("transfert copie");
        break;

    case CToolButton::MeasureDetails:
    case CToolButton::Configure: // SERES_TODO: Add correct icons. // COT-66
        icon = iconFromPixmaps("detail mesure");
        break;

    case CToolButton::Ok:
        icon = iconFromPixmaps("appliquer");
        break;

    case CToolButton::Cancel:
    case CToolButton::Delete:
        icon = iconFromPixmaps("annule");
        break;

    case CToolButton::Informations:
        icon = iconFromPixmaps("menu information");
        break;

    case CToolButton::CreateRecovery:
    case CToolButton::RestoreConfig:
        icon = iconFromPixmaps("menu sauvegarde");
        break;

    case CToolButton::Invalid:
        break;
    }

    return icon;
}

QString CToolButton::typeToString(CToolButton::Type type)
{
    const QMetaObject &mo = staticMetaObject;
    const int index = mo.indexOfEnumerator("Type");
    const QMetaEnum metaEnum = mo.enumerator(index);
    return QString::fromLocal8Bit(metaEnum.valueToKey(type));
}
