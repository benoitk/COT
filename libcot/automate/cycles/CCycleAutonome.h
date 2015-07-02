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
    QVariantMap serialise() Q_DECL_OVERRIDE;
/*    void setType(eTypeCycle);
    eTypeCycle getType()const;
    bool isRunning();
    bool isPaused();
    QString getName()const;
    void setName(const QString &);
    void addAction(IAction*);
    QString getLabel()const;
    void setLbl(const QString&);
public slots:
    void slotRunCycle();
    void slotPauseCycle();
    void slotStopCycle();
    void slotUnPauseCycle();
    void slotStopEndCycle();
    void slotGoToEndCycle();
    void slotGoToStepCycle(int);
    void slotGetReadyForPlayNextCycle();
    void slotGetReadyForPlayCycle();

    void slotExecNextStep();
    */
private:
    int m_idCycle;
    eTypeCycle m_typeCycle;
    QString m_name;
    QString m_label;


};
#endif // CCYCLEAUTONOME_H
