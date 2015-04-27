#ifndef IVARIABLEUIHANDLER_H
#define IVARIABLEUIHANDLER_H

#include <QObject>
#include <QHash>

class CScrollableWidget;
class IVariable;
class QLabel;
class QGridLayout;

class IVariableUIHandler : public QObject
{
    Q_OBJECT

public:
    explicit IVariableUIHandler(CScrollableWidget *scrollable, QObject *parent = Q_NULLPTR);

    void layout(const QList<IVariable *> &variables);
    void layout(const QStringList &variables);

protected:
    struct Row {
        Row() : label(Q_NULLPTR), editor(Q_NULLPTR), unit(Q_NULLPTR) { }

        QLabel *label;
        QWidget *editor;
        QLabel *unit;
    };

    CScrollableWidget *m_scrollable;
    QWidget *m_container;
    QGridLayout *m_containerLayout;
    QHash<QString, Row> m_rows;

    virtual QLabel *newLabel(IVariable *ivar);
    virtual QWidget *newEditor(IVariable *ivar);
    virtual QLabel *newUnit(IVariable *ivar);

    virtual int labelColumn() const;
    virtual int editorColumn() const;
    virtual int unitColumn() const;

    virtual void rowInserted(const Row &row);
    virtual void rowChanged(const Row &row, IVariable *ivar);

private slots:
    void slotVariableChanged(const QString &name);
    void slotSwitchClicked();
    void slotRequestIntegerValue();
    void slotRequestDoubleValue();
    void slotRequestStringValue();
    void slotRequestStream();
};

#endif // IVARIABLEUIHANDLER_H
