#ifndef CONFIGURATORSEQUENCERUIHANDLER_H
#define CONFIGURATORSEQUENCERUIHANDLER_H

#include <IConfiguratorUIHandler.h>
#include "cot_global.h"

class CPushButton;

class LIBCOT_EXPORT ConfiguratorSequencerUIHandler : public IConfiguratorUIHandler
{
    Q_OBJECT

public:
    typedef QPair<ICycle *, int> CyclePair;
    typedef QList<CyclePair> CyclePairList;

    explicit ConfiguratorSequencerUIHandler(CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    ~ConfiguratorSequencerUIHandler();

    void layout();

    CyclePairList cyclePairList() const;
    void setCyclePairList(const CyclePairList &pairs);

    static QList<ICycle*> fromCyclePairList(const CyclePairList &pairs);
    static CyclePairList fromCycleList(const QList<ICycle*> &cycles);

protected:
    IVariable *getVariable(const QString &name) const Q_DECL_OVERRIDE;
    int columnCount() const Q_DECL_OVERRIDE;
    QWidget *createWidget(int column, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowInserted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowChanged(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowAboutToBeDeleted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowDeleted(const QString &name) Q_DECL_OVERRIDE;

private slots:
    void slotEditCycleClicked();
    void slotEditValueClicked();

private:
    QHash<QString, IVariable *> m_internalVariables;

    CPushButton *newCycleButton(IVariable *ivar);
    CPushButton *newValueButton(IVariable *ivar);
};

#endif // CONFIGURATORSEQUENCERUIHANDLER_H
