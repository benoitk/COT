#ifndef CVOIE_H
#define CVOIE_H
#include "IVariable.h"

#include <qobject.h>

class ICycle;
class CVariableMeasure;

class CVariableStream : public IVariable
{
    Q_OBJECT

public:
    CVariableStream(CAutomate* arg_automate, QObject *parent = Q_NULLPTR);
    CVariableStream(const QMap<QString, QVariant> &mapVar, CAutomate* arg_automate, QObject* parent);
    ~CVariableStream();

    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
    QVariant toVariant() Q_DECL_OVERRIDE;
    void setValue(const QVariant &) Q_DECL_OVERRIDE;
    void setToBindedValue(const QVariant &) Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;
    enumVariableType getType()const Q_DECL_OVERRIDE;
    void switchToUnit(CUnit*) Q_DECL_OVERRIDE;

    void setValue(int iNumVoie);

    QList<IVariable*> getListVariables();
//    QList<CVariableMeasure*> getListMeasures();
    QList<IVariable*> getListMeasures();
    QList<ICycle*> getListCycles();
    IVariable* getActiveState();
    bool removeVariable(IVariable *var);
    bool addVariable(IVariable *var);
    void addCycle(ICycle *cycle);
    void removeCycle(const QString &name);
    void addMeasure(IVariablePtr var);
    void removeMeasure(IVariablePtr var);

private:

    IVariable* m_activeState;
    QList<IVariable*> m_listVariables;
    QList<IVariable*> m_listMeasures;
    QList<ICycle*> m_listCycles;
};

#endif // CVOIE_H
