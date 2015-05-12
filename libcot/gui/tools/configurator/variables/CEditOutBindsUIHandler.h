#ifndef CEDITOUTBINDSUIHANDLER_H
#define CEDITOUTBINDSUIHANDLER_H

#include <IConfiguratorUIHandler.h>



class CEditOutBindsUIHandler : public IConfiguratorUIHandler
{
    Q_OBJECT
public:
    explicit CEditOutBindsUIHandler(CScrollableWidget *scrollable, QObject *parent);
    ~CEditOutBindsUIHandler();
};

#endif // CEDITOUTBINDSUIHANDLER_H
