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
 * This class handles the UI presentation for a widget in the COT UI.
 * It is responsable for creating labels, editors and mapped selectors in a generic way.
 * Give it your variables list, it will do all for you.
 *
 * The widgets get created inside the scrollable widget passed to setScrollableWidget.
 */
class LIBCOT_EXPORT IVariableUIHandler : public QObject
{
    Q_OBJECT

public:
    explicit IVariableUIHandler(CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    virtual ~IVariableUIHandler();

    void layout(const QList<IVariable *> &variables, bool addDeleteButton = false);

    void setScrollableWidget(CScrollableWidget *scrollable);
    CScrollableWidget *getScrollableWidget() const;

    void setDescriber(IVariableObjectDescriber *describer);
    IVariableObjectDescriber *describer() const;
    template <typename T> T castedDescriber() const {
        return qobject_cast<T>(m_describer);
    }

    QWidget *container() const;
    QGridLayout *containerLayout() const;

    // Ask user to enter a text value
    bool enterText(QString &value, const QString &title = tr("Enter a new value"));
    // Ask user to enter an int value
    bool enterInteger(int &value, const QString &title = tr("Enter a new value"));
    // Ask user to enter a double value
    bool enterDouble(double &value, const QString &title = tr("Enter a new value"));

    // return an action type: calc_coef, calc_rien, block, etc.
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

    virtual IVariable *getVariable(const QString &name) const;
    QStringList variableNames() const;

protected:
    struct Row {
        Row() { }

        template <typename T>
        T widgetAt(int index) const {
            return qobject_cast<T>(widgets.at(index));
        }

        QList<QWidget *> widgets;
    };

    Row *getRow(const QString &name) const;
    void removeRow(const QString &name);
    int layoutRow(QWidget *widget) const;
    int layoutRow(const Row &row) const;

    virtual int columnCount() const;
    virtual bool horizontalStretch() const;
    virtual bool verticalStretch() const;

    // Called by layout() for every row, every column
    virtual QWidget *createWidget(int column, IVariable *ivar);

    // Called when layout() inserts a row
    virtual void rowInserted(const Row &row, IVariable *ivar);

    // Called when layout() inserts a row, or gets notified that a variable changed
    // This is therefore the best method where to implement showing the value of the variable
    virtual void rowChanged(const Row &row, IVariable *ivar);

    virtual CToolButton *newDeleteButton(IVariable *ivar);
    QLabel *newLabel(IVariable *ivar);
    QWidget *newEditor(IVariable *ivar);
    QLabel *newUnit(IVariable *ivar);
    void applyEditorConstraints(QWidget *editor, IVariable *ivar);

protected slots:
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

private:
    QWidget *m_container;
    QGridLayout *m_containerLayout;
    CScrollableWidget *m_scrollable;
    IVariableObjectDescriber *m_describer;
    mutable QHash<QString, Row> m_rows;
};

#endif // IVARIABLEUIHANDLER_H
