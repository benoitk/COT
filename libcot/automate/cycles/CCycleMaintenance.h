#ifndef CCYCLEMAINTENANCE_H
#define CCYCLEMAINTENANCE_H

#include "CCycleMesure.h"

class IVariable;
class CCycleMaintenance : public CCycleMesure
{
    Q_OBJECT

public:
    CCycleMaintenance(CScheduler *parent = Q_NULLPTR);
    CCycleMaintenance(enumTypeCycle type, CScheduler *parent = Q_NULLPTR);
     CCycleMaintenance(const QVariantMap&,CScheduler *parent);
    ~CCycleMaintenance();

    enumTypeCycle getType()const Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;

    QList<IVariable*>  getListVariablesInput();
    QList<IVariable*>  getListVariablesOutput();
    QList<IVariable*>  getListVariablesDefault();
    bool finishedWithErrors();
    void doValidationCopies();

public slots:
    void slotStepFinished(CStep*) Q_DECL_OVERRIDE;
//    void slotRunCycle() Q_DECL_OVERRIDE;

private:
    QList<IVariable*> m_listVariablesInput;
    QList<IVariable*> m_listVariablesOutput;
    QList<IVariable*> m_listVariablesDefault;
    QList<QPair<IVariable*, IVariable*>> m_listVariablesCopyOnValidation;



};
#endif // CCYCLEMAINTENANCE_H
