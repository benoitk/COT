#ifndef CComJBus_H
#define CComJBus_H

#include "ICom.h"

#include "qlist.h"
#include "qbitarray.h"
#include "qvariant.h"

#include "cot_global.h"

#include <modbus.h>

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

    QString getName()const Q_DECL_OVERRIDE;
    comType getType()const Q_DECL_OVERRIDE;

private:
    typedef QVector<uint8_t> BitArray;
    BitArray readNBitsFunction1(int addrVar, int nbBitsToRead);
    void writeNBitsFunction15(int addrVar, const BitArray &data);

    typedef QVector<uint16_t> WordArray;
    WordArray readNWordsFunction3(int addrVar, int nbWordsToRead);
    void writeNWordsFunction16(int addrVar, const WordArray &data);

    BitArray readNInputBitsFunction2(int addrVar, int nbBitsToRead);
    WordArray readNInputWordsFunction4(int addrVar, int nbWordsToRead);

    void writeBitFunction5(int addrVar, bool bit);
    void writeWordFunction6(int addrVar, int word);

    bool readBool(int addrVar);
    void writeBool(int addrVar, bool value);

    int readInt(int addrVar);
    void writeInt(int addrVar, int value);

    float readFloat(int addrVar);
    void writeFloat(int addrVar, float value);

    void initializeModbus();

    struct FreeModbus;
    QScopedPointer<modbus_t, FreeModbus> m_ctx;

    int m_slave;
    QMap<int, IVariableInput*> m_mapInputTable;
    QMap<int, IVariableOutput*> m_mapOutputTable;

    QString m_name;
    comType m_type;

    friend class JBusTest;
};

#endif // CComJBus_H
