#ifndef IHARDWARE_H
#define IHARDWARE_H

class ICom;
class IHardware
{

public:
	virtual void registerCom(ICom*);//Enregistre toute les coms qui attende une info de cet hardware (eth, uart, autre)

private:
	
};

#endif // IHARDWARE_H
