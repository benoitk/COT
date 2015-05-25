#ifndef CSTEP_H
#define CSTEP_H

#include <QObject>

class IAction;
class CStep : public QObject
{
    Q_OBJECT

public:
    CStep(const QMap<QString, QVariant> &);
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
private:

    QList<IAction*> m_listActions;
    float m_numStep; //peut gérer des pas flotant pour affiner le timming
    CStep* m_nextStep;
    QString m_label;
};

#endif // CSTEP_H
