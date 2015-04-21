#include "CLedButton.h"
#include "CVerticalButtonBar.h"

CLedButton::CLedButton(QWidget *parent)
    : QLabel(parent)
    , m_checkState(Qt::Unchecked)
    , m_icon(CToolButton::buttonIcon(CToolButton::Led))
{
    updateIcon();
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}

Qt::CheckState CLedButton::checkState() const
{
    return m_checkState;
}

bool CLedButton::isChecked() const
{
    return m_checkState == Qt::Checked;
}

void CLedButton::setCheckState(Qt::CheckState state)
{
    if (m_checkState != state) {
        m_checkState = state;
        updateIcon();
    }
}

void CLedButton::setChecked(bool checked)
{
    setCheckState(checked ? Qt::Checked : Qt::Unchecked);
}

void CLedButton::updateIcon()
{
    static const QSize size(30, 30);

    switch (m_checkState) {
    case Qt::Checked:
    case Qt::PartiallyChecked:
        setPixmap(m_icon.pixmap(size, QIcon::Selected, QIcon::Off));
        break;
    case Qt::Unchecked:
        setPixmap(m_icon.pixmap(size, QIcon::Normal, QIcon::Off));
        break;
    }
}
