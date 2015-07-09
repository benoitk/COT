#ifndef CACTIONBLOCK_H
#define CACTIONBLOCK_H
#include "IAction.h"

class IVariable;
/**
 * @brief The CActionBlock class is an action that contains a list of other actions.
 * This allows to reuse lists of actions in multiple contexts.
 */
class CCycleAutonome;
class CActionBlock : public IAction
{
    Q_OBJECT

public:

    CActionBlock(const QVariantMap&, QObject *parent);

    ~CActionBlock();


    bool runAction() Q_DECL_OVERRIDE;
    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
    bool variableUsed(IVariable *)const Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapIVariableParameters() Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapCstParameters() Q_DECL_OVERRIDE;
    void setParameter(QString arg_key, IVariable* arg_parameter)Q_DECL_OVERRIDE;
    CCycleAutonome* getCycle();
private:

    CCycleAutonome* m_cycle;

};

#endif // CACTIONBLOCK_H
