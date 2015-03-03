#ifndef CComJBus_H
#define CComJBus_H

#include "ICom.h"

#include "qlist.h"
#include "qbitarray.h"

class IHardware;
class CComJBus : public ICom
{
	Q_OBJECT

public:
	CComJBus(QObject *parent);
	~CComJBus();


	QVariant readData();
	QVariant readData(IVariableInput*);
	void writeData(IVariableOutput*);
	void addVariableOnDataTable(IVariableInput*);
	void addVariableOnDataTable(IVariableOutput*);

	void triggerUpdateAllData();


	QBitArray readNBitsFunction1( int addrVar, int nbBitsToRead);
	void writeNBitsFunction15(int addrVar, QBitArray data);
	QList<char> readNWordsFunction3( int addrVar, int nbBytesToRead);
	void writeNWordsFunction16(int addrVar, QList<char> data);

private:
	
	IHardware* m_uart;
	int m_numSlave;
	QMap<int, IVariableInput*> m_mapInputTable;
	QMap<int, IVariableOutput*> m_mapOutputTable;
};

#endif // CComJBus_H
