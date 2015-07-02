#ifndef CVARIABLEMEASURE_H
#define CVARIABLEMEASURE_H

#include "IVariable.h"
#include <QObject>
#include <QColor>

class ICycle;
class CVariableMeasure : public IVariable
{
    Q_OBJECT

public:
    CVariableMeasure(QObject *parent = Q_NULLPTR);
    CVariableMeasure(const QMap<QString, QVariant> &mapVar);



    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
    QVariant toVariant() Q_DECL_OVERRIDE;
    void setValue(const QVariant &) Q_DECL_OVERRIDE;
    void setToBindedValue(const QVariant &) Q_DECL_OVERRIDE;
    QVariantMap serialise() Q_DECL_OVERRIDE;
    variableType getType()const Q_DECL_OVERRIDE;
    void switchToUnit(CUnit*) Q_DECL_OVERRIDE;


    void setValue(int iNumVoie);

    QList<IVariable*> getListVariables();
    IVariable* getMeasureVariable();
    IVariable * getMeasureMax();
    IVariable * getMeasureMin();

    void removeVariable(IVariable *ivar);
    void addVariable(IVariable *ivar);

    void setColor(const QColor& col);
    QColor color() const;

private:

    IVariable * m_measure;
    IVariable * m_measureMax;
    IVariable * m_measureMin;

    QList<IVariable*> m_listVariables;
    QColor m_color;
};

#endif // CVARIABLEMEASURE_H
