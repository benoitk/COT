#ifndef CSCROLLABLEPLAINTEXTEDIT_H
#define CSCROLLABLEPLAINTEXTEDIT_H

#include "cot_global.h"
#include <QPlainTextEdit>
class QAction;

class LIBCOT_EXPORT CScrollablePlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit CScrollablePlainTextEdit(QWidget *parent = Q_NULLPTR);
    ~CScrollablePlainTextEdit();

    QAction *moveDown() const;
    QAction *moveUp() const;

protected:
    virtual void resizeEvent(QResizeEvent *event);

private slots:
    void slotMoveUp();
    void slotMoveDown();

private:
    QAction *m_moveUp;
    QAction *m_moveDown;

    void updateActions();
};

#endif
