#ifndef CEDITINBINDSUIHANDLER_H
#define CEDITINBINDSUIHANDLER_H

#include <IConfiguratorUIHandler.h>



class CEditInBindsUIHandler : public IConfiguratorUIHandler
{
    Q_OBJECT
public:
    explicit CEditInBindsUIHandler(CScrollableWidget *scrollable, QObject *parent);
    ~CEditInBindsUIHandler();
    QWidget *createWidget(int column, IVariable *ivar) Q_DECL_OVERRIDE;
};

#endif // CEDITINBINDSUIHANDLER_H
