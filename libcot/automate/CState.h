#ifndef CSTATE_H
#define CSTATE_H

#include <QObject>
#include <QList>


class IVariable;
class CState:public  QObject
{
    Q_OBJECT
public:
    CState(QObject *parent);

    QString getName();
    void setName(QString);
    QString getlabel();
    void setLabel(QString);
    bool getState();
    void setState(bool);
    void addOutputVariable(IVariable*);
    QVariantMap serialize();

signals:
    void signalStateChanged();

private:
    QString m_name;
    QString m_label;
    bool m_state;
    QList<IVariable*> m_listVariablesToSet;
};
#endif // CSTATE_H

