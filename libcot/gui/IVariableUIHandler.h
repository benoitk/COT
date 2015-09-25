#ifndef IVARIABLEUIHANDLER_H
#define IVARIABLEUIHANDLER_H

#include <QObject>
#include <QHash>
#include "cot_global.h"

#include "IVariable.h"
#include "ICycle.h"
#include "IAction.h"

class CScrollableWidget;
class CScrollablePagerWidget;
class IVariableObjectDescriber;
class CClickableLabel;
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
    explicit IVariableUIHandler(CScrollableWidget *scrollable, QObject *parent = Q_NULLPTR);
    virtual ~IVariableUIHandler();

    void layout(const QList<IVariable *> &variables, bool addDeleteButton = false);

    CScrollableWidget *getScrollableWidget() const;

    void setDescriber(IVariableObjectDescriber *describer);
    IVariableObjectDescriber *describer() const;
    template <typename T> T castedDescriber() const {
        return qobject_cast<T>(m_describer);
    }

    CScrollablePagerWidget *container() const;
    QGridLayout *containerLayout() const;
    virtual bool horizontalStretch() const;
    virtual bool verticalStretch() const;

    // Ask user to enter a text value
    static bool enterText(QString &value, const QString &title = QString());
    // Ask user to enter an int value
    static bool enterInteger(int &value, const QString &title = QString());
    // Ask user to enter a double value
    static bool enterFloat(float &value, const QString &title = QString());

    // return an action type: calc_coef, calc_rien, block, etc.
    static bool selectActionType(actionType &value, const QString &title = QString());
    // Select a variable type (float, int, string)
    static bool selectVariableType(enumVariableType &value, const QString &title = QString());
    // Select a variable organ type (input, output, none)
    static bool selectOrganType(enumVariableOrganType &value, const QString &title = QString());
    // Select a cycle type (maintenance, autonome, pause...)
    static bool selectCycleType(enumTypeCycle &value, const QString &title = QString());
    //Select a variable
    static bool selectVariable(QString &value, const QString &title = QString());
    // Select a stream name
    static bool selectStream(QString &value, const QString &title = QString());
    // Select a measure
    static bool selectMeasure(QString &value, const QString &title = QString());
    // Select a cycle
    static bool selectCycle(QString &value, const QString &title = QString());
    // Select an action
    static bool selectAction(QString &value, const QString &title = QString());
    // Select a stream and/or measure
    static bool selectStreamOrMeasure(QString &value, const QString &title = QString());
    // Select extension
    static bool selectExtension(QString &value, const QString &title = QString());
    // Select organ
    static bool selectOrgan(QString &value, const QString &title = QString());
    // Select an unit
    static bool selectUnit(QString &value, const QString &title = QString());

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

    // Called by layout() for every row, every column
    virtual QWidget *createWidget(int column, IVariable *ivar);

    // Called when layout() inserts a row
    virtual void rowInserted(const Row &row, IVariable *ivar);

    // Called when layout() inserts a row, or gets notified that a variable changed
    // This is therefore the best method where to implement showing the value of the variable
    virtual void rowChanged(const Row &row, IVariable *ivar);

    virtual QString getVariableLabel(IVariable *ivar) const;

    virtual void applyEditorConstraints(QWidget *editor, IVariable *ivar);
    virtual CToolButton *newDeleteButton(IVariable *ivar);
    void setVariableAccess(IVariable *ivar, enumVariableAccess access);
    CClickableLabel *newLabel(IVariable *ivar);
    QWidget *newEditor(IVariable *ivar);
    CClickableLabel *newUnit(IVariable *ivar);

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
    CScrollablePagerWidget *m_container;
    QGridLayout *m_containerLayout;
    CScrollableWidget *m_scrollable;
    IVariableObjectDescriber *m_describer;
    mutable QHash<QString, Row> m_rows;
};

#endif // IVARIABLEUIHANDLER_H
