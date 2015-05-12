#ifndef CCYCLETABUIHANDLER_H
#define CCYCLETABUIHANDLER_H

#include "IConfiguratorUIHandler.h"

class CPushButton;

class  CConfiguratorCycleTabUIHandler : public IConfiguratorUIHandler
{
    Q_OBJECT

public:
    explicit  CConfiguratorCycleTabUIHandler(CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    ~CConfiguratorCycleTabUIHandler();

    void layout();

protected:
    QHash<QString, IVariable *> m_internalVariables;

    IVariable *getVariable(const QString &name) Q_DECL_OVERRIDE;
    int columnCount() const Q_DECL_OVERRIDE;
    QWidget *createWidget(int column, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowInserted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowChanged(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowAboutToBeDeleted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;

protected slots:
    void slotEditClicked();

private:
    CPushButton *newButton(IVariable *ivar);
};

#endif // CCYCLETABUIHANDLER_H