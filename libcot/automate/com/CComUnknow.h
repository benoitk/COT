﻿#ifndef CCOMUNKNOW_H
#define CCOMUNKNOW_H
#include "ICom.h"

#include <QObject>

class CComUnknow : public ICom
{
    Q_OBJECT

public:
    CComUnknow(QObject *parent = 0);
    ~CComUnknow();

    QVariant readData() Q_DECL_OVERRIDE;
    QVariant readData(IVariableInput*) Q_DECL_OVERRIDE;
    void writeData(IVariableOutput*) Q_DECL_OVERRIDE;
    void addVariableInputOnDataTable(IVariableInput*) Q_DECL_OVERRIDE;
    void addVariableOutputOnDataTable(IVariableOutput*) Q_DECL_OVERRIDE;
    void addVariableOnDataTable(IVariable*) Q_DECL_OVERRIDE;
    void writeData(bool, const QString&) Q_DECL_OVERRIDE;
    void triggerUpdateAllData() Q_DECL_OVERRIDE;
    void generateDocumentation()Q_DECL_OVERRIDE;

    QString getName()const Q_DECL_OVERRIDE;
    enumComType getType()const Q_DECL_OVERRIDE;

private:

};

#endif // CCOMUNKNOW_H
