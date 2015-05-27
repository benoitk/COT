#ifndef CONFIGURATORSTREAMSUIHANDLER_H
#define CONFIGURATORSTREAMSUIHANDLER_H

#include "cot_global.h"
#include "IConfiguratorUIHandler.h"

class CPushButton;
class CVariableMeasure;
class CVariableStream;

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

    /**
     * @brief asks the user for a name, then add a new measure in the passed stream
     */
    void addNewMeasureToStream(CVariableStream *stream);

private slots:
    void slotItemClicked();
    void slotAddItem();

public slots:
    void slotAddStreams();

};

#endif // CONFIGURATORSTREAMSUIHANDLER_H
