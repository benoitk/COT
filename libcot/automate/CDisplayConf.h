#ifndef CDisplayConf_H
#define CDisplayConf_H

#include <QObject>
#include "qmap.h"

class IVariable;
class IAction;
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

    QList<IVariable*> getListForScreenDiagnostic() const;
    QMap<QString, QList<IVariable*> > getMapForScreenElectricalTests() const;
    QList<IVariable*> getListForScreenOptions() const;
    QList<IVariable*> getListForScreenHistory() const;
    QList<IVariable*> getListForScreenAlarms() const;

    void addInitialTestsAction(IAction*);
    void addInitialTestsVariableTest(IVariable*);
    void addInitialTestsVariableIndicator(IVariable*);
    QList<IAction *> getListInitialsTestActions();
    QList<IVariable *> getListInitialsTestVariablesTest();
    QList<IVariable *> getListInitialsTestVariablesIndicator();

    static const QString STR_ELEC_420;
    static const QString STR_ELEC_RELAYS;
    static const QString STR_ELEC_INPUTS;
    static const QString STR_ELEC_PUMP;
    static const QString STR_ELEC_ACTUATOR;

private:
    QList<IVariable*> m_listForScrenDiagnostic;
    QMap<QString, QList<IVariable*> > m_mapForScrenElectricalTests;
    QList<IVariable*> m_listForScrenOptions;
    QList<IVariable*> m_listForScrenHistory;
    QList<IVariable*> m_listForScrenAlarms;

    QList<IAction*> m_listInitialTestActions;
    QList<IVariable*> m_listInitialTestVariablesTest;
    QList<IVariable*> m_listInitialTestVariablesIndicator;
};

#endif // CDisplayConf_H
