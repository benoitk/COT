#ifndef CTHREADDIAG_H
#define CTHREADDIAG_H

#include <QObject>
#include "qrunnable.h"
//#include "qtimer.h"

class IVariableInput;
class CThreadDiag : public QObject, QRunnable
{
    Q_OBJECT
public:
    CThreadDiag(QObject* parent);

    void run();

public slots:
    void slotStop();
    void slotStart();
    void slotReadVariables();

private:
    QList<IVariableInput*> m_listDiagInputVars;
    bool m_stoped;
    //QTimer m_timer;
};

#endif // CTHREADDIAG_H
