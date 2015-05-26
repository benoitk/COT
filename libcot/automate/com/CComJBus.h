#ifndef CComJBus_H
#define CComJBus_H

#include "ICom.h"

#include "qlist.h"
#include "qbitarray.h"
#include "qvariant.h"

#include "cot_global.h"

typedef struct _modbus modbus_t;

class LIBCOT_EXPORT CComJBus : public ICom
{
    Q_OBJECT

public:
    CComJBus(const QVariantMap &options, QObject *parent = 0);
    ~CComJBus();

    QVariant readData() Q_DECL_OVERRIDE;
    QVariant readData(IVariableInput*) Q_DECL_OVERRIDE;
    void writeData(IVariableOutput*) Q_DECL_OVERRIDE;
    void addVariableOnDataTable(IVariableInput*) Q_DECL_OVERRIDE;
    void addVariableOnDataTable(IVariableOutput*) Q_DECL_OVERRIDE;

    void triggerUpdateAllData() Q_DECL_OVERRIDE;


    QBitArray readNBitsFunction1( int addrVar, int nbBitsToRead);
    void writeNBitsFunction15(int addrVar, const QBitArray &data);
    QList<char> readNWordsFunction3( int addrVar, int nbBytesToRead);
    void writeNWordsFunction16(int addrVar, const QList<char> &data);

    QString getName()const Q_DECL_OVERRIDE;
    comType getType()const Q_DECL_OVERRIDE;

private:
    modbus_t* m_ctx;
    int m_numSlave;
    QMap<int, IVariableInput*> m_mapInputTable;
    QMap<int, IVariableOutput*> m_mapOutputTable;

    QString m_name;
    comType m_type;
};

#endif // CComJBus_H
