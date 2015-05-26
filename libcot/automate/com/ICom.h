#ifndef ICom_H
#define ICom_H

#include <QObject>
#include "qvariant.h"

enum comType{
        type_tcp = 0,
        type_jbus,
        type_jbus_over_tcpip,
        type_com_unknow

};

class IVariableInput;
class IVariableOutput;
class IVariable;
class ICom : public QObject
{
    Q_OBJECT

public:
    ICom(QObject *parent);
    ICom();
    ~ICom();

    virtual QVariant readData()=0;
    virtual QVariant readData(IVariableInput*)=0;

    virtual void writeData(IVariableOutput*)=0;
    virtual void addVariableOnDataTable(IVariableInput*)=0;
    virtual void addVariableOnDataTable(IVariableOutput*)=0;

    virtual void triggerUpdateAllData()=0;
    //virtual QList<IVariable*> getParameters()const=0;
    virtual QString getName()const =0;
    virtual comType getType()const=0;

private:

};

Q_DECLARE_METATYPE(comType)

#endif // ICom_H
