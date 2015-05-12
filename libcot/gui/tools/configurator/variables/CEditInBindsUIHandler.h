#ifndef CEDITINBINDSUIHANDLER_H
#define CEDITINBINDSUIHANDLER_H

#include <IConfiguratorUIHandler.h>



class CEditInBindsUIHandler : public IConfiguratorUIHandler
{
    Q_OBJECT
public:
    explicit CEditInBindsUIHandler(CScrollableWidget *scrollable, QObject *parent);
    ~CEditInBindsUIHandler();
};

#endif // CEDITINBINDSUIHANDLER_H
