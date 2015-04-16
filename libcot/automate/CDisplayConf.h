#ifndef CDisplayConf_H
#define CDisplayConf_H

#include <QObject>
#include "qmap.h"

class IVariable;
class CDisplayConf : public QObject
{
    Q_OBJECT

public:
    CDisplayConf(const QJsonArray&, QObject *parent);
    ~CDisplayConf();

    void addVariableToScreenDiagnostic(IVariable*);
    void addVariableToScreenElectricalTest(const QString&, IVariable*);
    void addTabToScreenElectricalTest(const QString&);
    void addVariableToScreenOptions(IVariable*);
    void addVariableToScreenHistory(IVariable*);
    void addVariableToScreenAlarms(IVariable*);

    void delVariableToScreenDiagnostic(IVariable*);
    void delVariableToScreenElectricalTest(const QString&, IVariable*);
    void delTabToScreenElectricalTest(const QString&);
    void delVariableToScreenOptions(IVariable*);
    void delVariableToScreenHistory(IVariable*);
    void delVariableToScreenAlarms(IVariable*);

    QList<IVariable*> getListForScrenDiagnostic();
    QMap<QString, QList<IVariable*> > getMapForScrenElectricalTests();
    QList<IVariable*> getListForScrenOptions();
    QList<IVariable*> getListForScrenHistory();
    QList<IVariable*> getListForScrenAlarms();
    

private:
    QList<IVariable*> m_listForScrenDiagnostic;
    QMap<QString, QList<IVariable*> > m_mapForScrenElectricalTests;
    QList<IVariable*> m_listForScrenOptions;
    QList<IVariable*> m_listForScrenHistory;
    QList<IVariable*> m_listForScrenAlarms;
};

#endif // CDisplayConf_H
