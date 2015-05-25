#ifndef CACTIONUNKNOW_H
#define CACTIONUNKNOW_H

#include "IAction.h"

class CActionUnknow : public IAction
{
    Q_OBJECT

public:
    CActionUnknow(QObject *parent);
    CActionUnknow(const QVariantMap &mapAction);
    CActionUnknow();
    ~CActionUnknow();

    bool runAction() Q_DECL_OVERRIDE;
    QString getName()const Q_DECL_OVERRIDE;
    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    QString getLabel()const Q_DECL_OVERRIDE;
    void setLabel(const QString&) Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;

private:
    QString m_name;
    QString* m_label;
};

#endif // CACTIONUNKNOW_H
