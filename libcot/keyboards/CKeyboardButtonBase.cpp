#include "CKeyboardButtonBase.h"
#include "CToolButton.h"

#include <QPainter>
#include <StyleRepository.h>

CKeyboardButtonBase::CKeyboardButtonBase(CKeyboardButtonBase::Type type, QWidget *parent)
    : QPushButton(parent)
    , m_type(type)
    , m_icon(CToolButton::buttonIcon(CToolButton::Empty))
{
    setMinimumSize( QSize( 70, 70 ) );

    if (m_type == Alpha) {
        setFont(QFont("Arial", font().pointSize() +2, QFont::Bold));
    }
    else if (m_type == Numeric) {
        QPalette pal = palette();
        pal.setColor(QPalette::ButtonText, QColor(Qt::white));

        setPalette(pal);
        setFont(QFont("Arial", font().pointSize() +6, QFont::Bold));
        setFixedSize(StyleRepository::keyboardButtonSize());
    }
}

CKeyboardButtonBase::~CKeyboardButtonBase()
{

}
CKeyboardButtonBase::Type CKeyboardButtonBase::type() const
{
    return m_type;
}

void CKeyboardButtonBase::paintEvent(QPaintEvent *event)
{
    if (m_type == Numeric) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        if (isEnabled()) {
            if (isChecked() || isDown()) {
                m_icon.paint(&painter, rect(), Qt::AlignCenter, QIcon::Selected, QIcon::Off);
            }
            else {
                m_icon.paint(&painter, rect(), Qt::AlignCenter, QIcon::Normal, QIcon::Off);
            }
        }
        else {
            m_icon.paint(&painter, rect(), Qt::AlignCenter, QIcon::Disabled, QIcon::Off);
        }

        painter.drawText(rect(), Qt::AlignCenter | Qt::TextWrapAnywhere, text());
    }
    else {
        QPushButton::paintEvent(event);
    }
}


