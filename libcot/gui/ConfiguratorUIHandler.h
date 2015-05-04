#ifndef CONFIGURATORUIHANDLER_H
#define CONFIGURATORUIHANDLER_H

#include <QObject>

#include "IVariable.h"
#include "ICycle.h"

class ConfiguratorUIHandler : public QObject
{
    Q_OBJECT

public:
    explicit ConfiguratorUIHandler(QObject *parent = Q_NULLPTR);

//protected:
    // return an action type: calc_coef, cal_rien, bloc
    int selectActionType(int defaultValue = -1);
    // Select a variable type (float, int, string)
    variableType selectVariableType(variableType defaultValue = type_unknow);
    // Select a variable organ type (input, output, none)
    VariableOrganType selectOrganType(VariableOrganType defaultValue = VariableOrganTypeNone);
    // Select a cycle type (maintenance, autonome, pause...)
    eTypeCycle selectCycleType(eTypeCycle defaultValue = CYCLE_INVALID);
    // Select a variable
    QString selectVariable(const QString &defaultName = QString());
    // Select a stream name
    QString selectStream(const QString &defaultName = QString());
    // Select a measure
    QString selectMeasure(const QString &defaultName = QString());
    // Select a cycle
    QString selectCycle(const QString &defaultName = QString());
    // Select an action
    QString selectAction(const QString &defaultName = QString());
    // Select a stream and/or measure
    QString selectStreamOrMeasure(const QString &defaultName = QString());
    // Select extension
    QString selectExtension(const QString &defaultName = QString());
    // Select organ
    QString selectOrgan(const QString &defaultName = QString());

    // Ask user to enter a text value
    QString enterText(const QString &defaultValue = QString());
    // Ask user to enter an int value
    int enterInteger(int defaultValue = 0);
    // Ask user to enter a double value
    double enterDouble(double defaultValue = 0);
};

#endif // CONFIGURATORUIHANDLER_H
