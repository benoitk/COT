#ifndef CSTEP_H
#define CSTEP_H

#include <QObject>
#include <QVariant>
#include "qrunnable.h"
#include "qmutex.h"

class IAction;
class ICycle;
class CStep : public QObject
{
    Q_OBJECT

public:
    CStep(ICycle *parent, const QVariantMap & = QVariantMap());
    CStep();
    ~CStep();

    //use for API
    QString getLabel()const;
    void setLabel(const QString &);
    QList<IAction*> getListActions()const;
    float getNumStep()const;
    void setNumStep(float);
    //CStep* getNextStep()const;
    //void setNextStep(CStep*);
    //FIN API
    void execStep();
    QVariantMap serialise();
    void addAction(IAction*);
    void removeAction(IAction*);
    void setListActions(const QList<IAction *> &actions);
    void abortStep();
    bool finishedWithcriticalError();
public slots:

    void slotActionFinished(IAction* );

signals:

    void signalStepFinished(CStep*);

private:

    QList<IAction*> m_listActions;
    QList<IAction*> m_listActionsWaited;
    bool m_bWaitForActions;
    bool m_criticalErrorDuringActions;

    float m_numStep; //peut gérer des pas flotant pour affiner le timming
    ICycle* m_parentCycle;
    QString m_label;

    QMutex m_mutex;
};

#endif // CSTEP_H
