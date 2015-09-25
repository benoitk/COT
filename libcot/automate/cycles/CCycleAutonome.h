#ifndef CCYCLEAUTONOME_H
#define CCYCLEAUTONOME_H

//#include "ICycle.h"
#include "CCycleMesure.h"

//class CCycleAutonome : public ICycle
class CCycleAutonome : public CCycleMesure
{
    Q_OBJECT

public:
    CCycleAutonome(QObject *parent = Q_NULLPTR);
    CCycleAutonome(const QVariantMap&, QObject *parent);
    CCycleAutonome(const QVariantMap&, const QMap<QString, IAction*> &, QObject *parent);
    ~CCycleAutonome();


    QString getRelatedStreamName()const Q_DECL_OVERRIDE;
    CVariableStream* getRelatedStream()const Q_DECL_OVERRIDE;
    void setRelatedStreamName(const QString &name) Q_DECL_OVERRIDE;
    QList<CStep*> getListSteps()const Q_DECL_OVERRIDE;
    CStep* getStepStop()const Q_DECL_OVERRIDE;
    void setListSteps(const QList<CStep *> &steps, CStep *stopStep = Q_NULLPTR) Q_DECL_OVERRIDE;
    int getCurrentStepIndex() const Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;

    void updateCycleInfosStep(float arg_numStep, QString arg_info) Q_DECL_OVERRIDE;
    void updateCycleInfosAction(QString arg_info) Q_DECL_OVERRIDE;
    void updateCycleInfosCountStep() Q_DECL_OVERRIDE;

private:
    int m_idCycle;
    enumTypeCycle m_typeCycle;
    QString m_name;
    QString m_label;


};
#endif // CCYCLEAUTONOME_H
