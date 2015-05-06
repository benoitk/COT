#ifndef IVARIABLEUIHANDLER_H
#define IVARIABLEUIHANDLER_H

#include <QObject>
#include <QHash>

class CScrollableWidget;
class IVariable;
class IVariableObjectDescriber;
class QLabel;
class QGridLayout;

class IVariableUIHandler : public QObject
{
    Q_OBJECT

public:
    explicit IVariableUIHandler(CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    virtual ~IVariableUIHandler();

    void layout(const QList<IVariable *> &variables, bool addDeleteButton = false);
    void layout(const QStringList &variables, bool addDeleteButton = false);

    void setScrollableWidget(CScrollableWidget *scrollable);

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

    virtual QWidget *newDeleteButton(IVariable *ivar);
    QLabel *newLabel(IVariable *ivar);
    QWidget *newEditor(IVariable *ivar);
    QLabel *newUnit(IVariable *ivar);

private slots:
    void slotVariableChanged(const QString &name);
    void slotSwitchClicked();
    void slotRequestIntegerValue();
    void slotRequestDoubleValue();
    void slotRequestStringValue();
    void slotRequestStream();
};

#endif // IVARIABLEUIHANDLER_H
