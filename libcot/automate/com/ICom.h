#ifndef ICom_H
#define ICom_H

#include <QObject>
#include "qvariant.h"

#include "cot_global.h"

enum enumComType{
        e_type_jbus_over_tcpip = 0,
        e_type_jbus,
        e_type_jbus_over_tcpip_rtu,
        e_type_com_unknow

};

LIBCOT_EXPORT enumComType stringToComType(const QString &type);
LIBCOT_EXPORT QString comTypeToString(enumComType arg_eType);

class IVariableInput;
class IVariableOutput;
class IVariable;
class LIBCOT_EXPORT ICom : public QObject
{
    Q_OBJECT

public:
    ICom(QObject *parent = 0);
    ~ICom();

    virtual QVariant readData()=0;
    virtual QVariant readData(IVariableInput*)=0;

    virtual void writeData(IVariableOutput*)=0;
    virtual void writeData(bool, const QString&)=0;
    virtual void addVariableInputOnDataTable(IVariableInput*)=0;
    virtual void addVariableOutputOnDataTable(IVariableOutput*)=0;
    virtual void addVariableOnDataTable(IVariable*)=0;


    virtual void triggerUpdateAllData()=0;
    //virtual QList<IVariable*> getParameters()const=0;
    virtual QString getName()const =0;
    virtual enumComType getType()const=0;
    virtual QVariantMap serialize();
    virtual void generateDocumentation()=0;

private:

};

Q_DECLARE_METATYPE(enumComType)

#endif // ICom_H
