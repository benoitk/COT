#ifndef IVARIABLEUIHANDLER_H
#define IVARIABLEUIHANDLER_H

#include <QObject>
#include <QHash>
#include "cot_global.h"

#include "IVariable.h"
#include "ICycle.h"

class CScrollableWidget;
class IVariableObjectDescriber;
class QLabel;
class QGridLayout;
class CToolButton;

/*
 * This class handle the UI presentation for a widget in the COT UI.
 * It is responsable to create labels, editors and mapped selectors in a generic way.
 * Give it your variables list, it will do all for you.
 * */
class LIBCOT_EXPORT IVariableUIHandler : public QObject
{
    Q_OBJECT

public:
    explicit IVariableUIHandler(CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    virtual ~IVariableUIHandler();

    void layout(const QList<IVariable *> &variables, bool addDeleteButton = false);
    void layout(const QStringList &variables, bool addDeleteButton = false);

    void setScrollableWidget(CScrollableWidget *scrollable);

    // Ask user to enter a text value
    bool enterText(QString &value);
    // Ask user to enter an int value
    bool enterInteger(int &value);
    // Ask user to enter a double value
    bool enterDouble(double &value);

    // return an action type: calc_coef, calc_rien, bloc, etc.
    bool selectActionType(int &value);
    // Select a variable type (float, int, string)
    bool selectVariableType(variableType &value);
    // Select a variable organ type (input, output, none)
    bool selectOrganType(VariableOrganType &value);
    // Select a cycle type (maintenance, autonome, pause...)
    bool selectCycleType(eTypeCycle &value);
    // Select a variable
    bool selectVariable(QString &value);
    // Select a stream name
    bool selectStream(QString &value);
    // Select a measure
    bool selectMeasure(QString &value);
    // Select a cycle
    bool selectCycle(QString &value);
    // Select an action
    bool selectAction(QString &value);
    // Select a stream and/or measure
    bool selectStreamOrMeasure(QString &value);
    // Select extension
    bool selectExtension(QString &value);
    // Select organ
    bool selectOrgan(QString &value);
    // Select an unit
    bool selectUnit(QString &value);

protected:
    struct Row {
        Row() { }

        template <typename T>
        T widgetAt(int index) const {
            return qobject_cast<T>(widgets.at(index));
        }

        QList<QWidget *> widgets;
    };

    IVariableObjectDescriber *m_describer;
    CScrollableWidget *m_scrollable;
    QWidget *m_container;
    QGridLayout *m_containerLayout;
    QHash<QString, Row> m_rows;

    int layoutRow(QWidget *widget) const;

    virtual IVariable *getVariable(const QString &name);
    virtual int columnCount() const;
    virtual QWidget *createWidget(int column, IVariable *ivar);
    virtual void rowInserted(const Row &row, IVariable *ivar);
    virtual void rowChanged(const Row &row, IVariable *ivar);

    virtual CToolButton *newDeleteButton(IVariable *ivar);
    QLabel *newLabel(IVariable *ivar);
    QWidget *newEditor(IVariable *ivar);
    QLabel *newUnit(IVariable *ivar);

private slots:
    void slotVariableChanged(const QString &name);
    void slotSwitchClicked();
    void slotRequestString();
    void slotRequestInteger();
    void slotRequestDouble();
    void slotRequestActionType();
    void slotRequestVariableType();
    void slotRequestOrganType();
    void slotRequestCycleType();
    void slotRequestVariable();
    void slotRequestStream();
    void slotRequestMeasure();
    void slotRequestCycle();
    void slotRequestAction();
    void slotRequestStreamOrMeasure();
    void slotRequestExtension();
    void slotRequestOrgan();
    void slotRequestUnit();
};

#endif // IVARIABLEUIHANDLER_H
