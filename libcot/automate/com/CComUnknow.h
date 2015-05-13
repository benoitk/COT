#ifndef CCOMUNKNOW_H
#define CCOMUNKNOW_H
#include "ICom.h"

#include <QObject>

class INetwork;
class CComUnknow : public ICom
{
    Q_OBJECT

public:
    CComUnknow(QObject *parent);
    CComUnknow();
    ~CComUnknow();

    QVariant readData() Q_DECL_OVERRIDE;
    QVariant readData(IVariableInput*) Q_DECL_OVERRIDE;
    void writeData(IVariableOutput*) Q_DECL_OVERRIDE;
    void addVariableOnDataTable(IVariableInput*) Q_DECL_OVERRIDE;
    void addVariableOnDataTable(IVariableOutput*) Q_DECL_OVERRIDE;

    void triggerUpdateAllData() Q_DECL_OVERRIDE;

    QString getName()const Q_DECL_OVERRIDE;
    comType getType()const Q_DECL_OVERRIDE;

private:
    
};

#endif // CCOMUNKNOW_H