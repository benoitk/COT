#ifndef CSTEP_H
#define CSTEP_H

#include <QObject>
#include <QVariant>

class IAction;
class CStep : public QObject
{
    Q_OBJECT

public:
    CStep(const QVariantMap & = QVariantMap());
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
private:

    QList<IAction*> m_listActions;
    float m_numStep; //peut gérer des pas flotant pour affiner le timming
    QString m_label;
};

#endif // CSTEP_H
