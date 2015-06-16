#include "CScrollablePlainTextEdit.h"

#include <QAction>
#include <QScrollBar>

CScrollablePlainTextEdit::CScrollablePlainTextEdit(QWidget *parent)
    : QPlainTextEdit(parent)
{
    m_moveDown = new QAction(tr("Move down"), this);
    connect(m_moveDown, &QAction::triggered, this, &CScrollablePlainTextEdit::slotMoveDown);
    m_moveUp = new QAction(tr("Move up"), this);
    connect(m_moveUp, &QAction::triggered, this, &CScrollablePlainTextEdit::slotMoveUp);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    updateActions();

    connect(this, &QPlainTextEdit::blockCountChanged,
            this, &CScrollablePlainTextEdit::updateActions);
    connect(verticalScrollBar(), &QScrollBar::valueChanged,
            this, &CScrollablePlainTextEdit::updateActions);
}

CScrollablePlainTextEdit::~CScrollablePlainTextEdit()
{

}

QAction *CScrollablePlainTextEdit::moveDown() const
{
    return m_moveDown;
}

QAction *CScrollablePlainTextEdit::moveUp() const
{
    return m_moveUp;
}

void CScrollablePlainTextEdit::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    updateActions();
}

void CScrollablePlainTextEdit::slotMoveUp()
{
    verticalScrollBar()->triggerAction(QAbstractSlider::SliderPageStepSub);
    updateActions();
}

void CScrollablePlainTextEdit::slotMoveDown()
{
    verticalScrollBar()->triggerAction(QAbstractSlider::SliderPageStepAdd);
    updateActions();
}

void CScrollablePlainTextEdit::updateActions()
{
    m_moveDown->setEnabled(verticalScrollBar()->value() != verticalScrollBar()->maximum());
    m_moveUp->setEnabled(verticalScrollBar()->value() > 0);
}

