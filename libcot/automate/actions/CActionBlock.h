#ifndef CACTIONBLOCK_H
#define CACTIONBLOCK_H
#include "IAction.h"

class IVariable;
/**
 * @brief The CActionBlock class is an action that contains a list of other actions.
 * This allows to reuse lists of actions in multiple contexts.
 */
class CActionBlock : public IAction
{
    Q_OBJECT

public:

    CActionBlock(const QVariantMap&);
    ~CActionBlock();

    void setActions(const QList<IAction *>& actions);
    QList<IAction *> actions() const;

    bool runAction() Q_DECL_OVERRIDE;
    QString getName()const Q_DECL_OVERRIDE;
    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    QString getLabel()const Q_DECL_OVERRIDE;
    void setLabel(const QString&) Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
private:

    QString m_label;
    QList<IAction*> m_actions;
    QString m_name;
    
};

#endif // CACTIONBLOCK_H
