#ifndef INetwork_H
#define INetwork_H

typedef enum networkType{
	eth =0,
	uart

};

class ICom;
class INetwork
{

public:
	virtual void registerCom(ICom*);//Enregistre toute les coms qui attende une info de cet hardware (eth, uart, autre)
	virtual void getType();

private:
	
};

#endif // INetwork_H
