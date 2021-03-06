#ifndef CACTIONCMDPOMPE_H
#define CACTIONCMDPOMPE_H

#include "IAction.h"

class IVariable;
class CVariableOutputBool;
class CVariableInputBool;
class CVariableOutputInt;
class CVariableAlarm;
class CActionCmdPompe : public IAction
{
    Q_OBJECT

public:

    CActionCmdPompe(const QVariantMap &, CAutomate *parent);

    ~CActionCmdPompe();

    bool runAction(ICycle* arg_stepParent) Q_DECL_OVERRIDE;
    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
    bool variableUsed(IVariable *)const Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapIVariableParameters() Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapCstParameters() Q_DECL_OVERRIDE;
    void setParameter(const QString& arg_key, IVariable* arg_parameter)Q_DECL_OVERRIDE;

    enumVariableType getWaitedType(const QString& arg_key) Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;
private:


    //Rien ne nous assure les types correct dans le json (et rien ne contre indique à mettre n'importe quoi, normalement)

    CVariableOutputBool* m_alim; //valeur par défaut de la pompe
    //valeur spécifique à l'action :
    CVariableOutputInt* m_speed;
    CVariableOutputInt* m_nbSteps;
    CVariableOutputBool* m_clockwise;
    IVariable* m_stepByStep;
    CVariableOutputInt* m_nbTurns;
    CVariableOutputBool* m_OriginReturn;
    CVariableInputBool* m_default;
    CVariableAlarm* m_alarm;
};

#endif // CACTIONCMDPOMPE_H
