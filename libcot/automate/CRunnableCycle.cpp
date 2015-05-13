#include "CRunnableCycle.h"

CRunnableCycle::CRunnableCycle(ICycle *cycle)
    : QRunnable()
{
    this->setAutoDelete(true);
}

CRunnableCycle::~CRunnableCycle()
{

}

void CRunnableCycle::run(){
    m_cycle->slotRunCycle();
}