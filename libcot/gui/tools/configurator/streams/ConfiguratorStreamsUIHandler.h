#ifndef CONFIGURATORSTREAMSUIHANDLER_H
#define CONFIGURATORSTREAMSUIHANDLER_H

#include "cot_global.h"
#include "IConfiguratorUIHandler.h"

class CPushButton;
class CVariableMeasure;

class LIBCOT_EXPORT ConfiguratorStreamsUIHandler : public IConfiguratorUIHandler
{
    Q_OBJECT

public:
    explicit ConfiguratorStreamsUIHandler(CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    ~ConfiguratorStreamsUIHandler();

    void layout();
    IVariable *getVariable(const QString &name) const Q_DECL_OVERRIDE;

protected:
    int columnCount() const Q_DECL_OVERRIDE;
    QWidget *createWidget(int column, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowInserted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowChanged(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowAboutToBeDeleted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;

private:
    CPushButton *newItemButton(IVariable *ivar);
    CToolButton *addMeasureButton(IVariable *ivar);

    CVariableStream *getStreamForMeasure(CVariableMeasure *measure);

private slots:
    void itemClicked();
    void addItem();

};

#endif // CONFIGURATORSTREAMSUIHANDLER_H
