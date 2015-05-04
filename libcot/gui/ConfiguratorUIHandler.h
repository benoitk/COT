#ifndef CONFIGURATORUIHANDLER_H
#define CONFIGURATORUIHANDLER_H

#include <QObject>

#include "IVariable.h"

class ConfiguratorUIHandler : public QObject
{
    Q_OBJECT

public:
    explicit ConfiguratorUIHandler(QObject *parent = Q_NULLPTR);

//protected:
    // return an action type: calc_coef, cal_rien, bloc
    int selectActionType(int defaultValue = -1);
    // Select a variable type (float, int, string)
    variableType selectVariableType(int defaultValue = -1);
    // Select a variable organ type (input, output, none)
    VariableOrganType selectOrganType(int defaultValue = -1);
    // Select a cycle type (maintenance, autonome, pause...)
    int selectCycleType(int defaultValue = -1);
    // Select a variable
    QString selectVariable(const QString &defaultValue = QString());
    // Select a stream name
    QString selectStream(const QString &defaultValue = QString());
    // Select a measure
    QString selectMeasure(const QString &defaultValue = QString());
    // Select a cycle
    QString selectCycle(const QString &defaultValue = QString());
    // Select an action
    QString selectAction(const QString &defaultValue = QString());
    // Select a stream and/or measure
    QString selectStreamOrMeasure(const QString &defaultValue = QString());
    // Select extension
    QString selectExtension(const QString &defaultValue = QString());
    // Select organ
    QString selectOrgan(const QString &defaultValue = QString());

    // Ask user to enter a text value
    QString enterText(const QString &defaultValue = QString());
    // Ask user to enter an int value
    int enterInteger(int defaultValue = -1);
    // Ask user to enter a double value
    double enterDouble(double defaultValue = -1.0);
};

#endif // CONFIGURATORUIHANDLER_H
