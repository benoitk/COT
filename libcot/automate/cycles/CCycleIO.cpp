#include "CCycleIO.h"

CCycleIO::CCycleIO(QObject *parent)
    : ICycle(parent)
{

}

CCycleIO::~CCycleIO()
{

}
eTypeCycle CCycleIO::getType()const{
    return CYCLE_MESURE;
}

int CCycleIO::getCurrentStepIndex() const
{
    return -1;
}
void CCycleIO::slotRunCycle(){
    
}
void CCycleIO::slotPauseCycle(){
    
}
void CCycleIO::slotStopCycle(){
}

void CCycleIO::addAction(int, IAction* action){
    
}
