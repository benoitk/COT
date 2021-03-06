#ifndef CEDITINBINDSUIHANDLER_H
#define CEDITINBINDSUIHANDLER_H

#include <IConfiguratorUIHandler.h>

class CEditInBindsUIHandler : public IConfiguratorUIHandler
{
    Q_OBJECT

public:
    explicit CEditInBindsUIHandler(CAutomate* arg_automate,CScrollableWidget *scrollable, QObject *parent);
    ~CEditInBindsUIHandler();

    void layout(IVariable *ivar);

protected:
    int columnCount() const Q_DECL_OVERRIDE;
    QWidget *createWidget(int column, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowInserted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowChanged(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;

    CAutomate* m_automate;
};

#endif // CEDITINBINDSUIHANDLER_H
