#include "IVariableUIHandler.h"
#include "IVariableObjectDescriber.h"
#include "CScrollableWidget.h"
#include "CSwitchButton.h"
#include "CLedButton.h"
#include "CPushButton.h"
#include "CToolButton.h"
#include "CKeyboardDialog.h"
#include "CNumericalKeyboardDialog.h"
#include "CGenericItemSelector.h"
#include "CPCWindow.h"
#include "CAutomate.h"
#include "IVariable.h"
#include "IVariableInput.h"
#include "IVariableOutput.h"
#include "CUnit.h"

#include <QGridLayout>
#include <QLabel>
#include <QDebug>

/*
// Read / Write
VariableOrganTypeNone
// Write Only
VariableOrganTypeOutput
//Read Only
VariableOrganTypeInput
*/

IVariableUIHandler::IVariableUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : QObject(parent)
    , m_describer(Q_NULLPTR)
    , m_scrollable(scrollable)
    , m_container(Q_NULLPTR)
    , m_containerLayout(Q_NULLPTR)
{
    connect(CAutomate::getInstance(), &CAutomate::signalVariableChanged,
            this, &IVariableUIHandler::slotVariableChanged);
}

IVariableUIHandler::~IVariableUIHandler()
{
    delete m_describer;
}

void IVariableUIHandler::layout(const QList<IVariable *> &variables, bool addDeleteButton)
{
    // Clean old widgets
    delete m_containerLayout;
    delete m_container;
    m_rows.clear();

    // Create new rows
    m_container = new QWidget(m_scrollable);
    m_containerLayout = new QGridLayout(m_container);
    m_containerLayout->setMargin(0);

    const int numberOfColumn = addDeleteButton ? (columnCount() + 1) : columnCount();
    int y = 0;
    foreach (IVariable *ivar, variables) {
        Row &row = m_rows[ivar->getName()];

        for (int x = 0; x < numberOfColumn; ++x) {
            QWidget *widget = createWidget(x, ivar);
            // it intentional to put possible null entry in list, so we can still rely on column to get correct widget.
            row.widgets << widget;

            if (widget) {
                m_containerLayout->addWidget(widget, y, x);
            }
        }

        rowChanged(row, ivar);
        rowInserted(row, ivar);
        y++;
    }

    QSpacerItem *vspacer = new QSpacerItem(8, 8, QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_containerLayout->addItem(vspacer, y, 0, 1, numberOfColumn);

    QSpacerItem *hspacer = new QSpacerItem(8, 8, QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_containerLayout->addItem(hspacer, 0, numberOfColumn, y, 1);

    m_scrollable->setScrollableWidget(m_container);
}

void IVariableUIHandler::layout(const QStringList &variables, bool addDeleteButton)
{
    CAutomate *automate = CAutomate::getInstance();
    layout(automate->getVariables(variables), addDeleteButton);
}

void IVariableUIHandler::setScrollableWidget(CScrollableWidget *scrollable)
{
    if (m_scrollable) {
        Q_ASSERT(false);
    }

    m_scrollable = scrollable;
}

int IVariableUIHandler::layoutRow(QWidget *widget) const
{
    int i = m_containerLayout->indexOf(widget);
    int r;
    int c;
    int rs;
    int cs;
    m_containerLayout->getItemPosition(i, &r, &c, &rs, &cs);
    return r;
}

IVariable *IVariableUIHandler::getVariable(const QString &name)
{
    IVariable *ivar = Q_NULLPTR;

    if (m_describer) {
        ivar = m_describer->getVariable(name);
    }

    if (!ivar) {
        ivar = CAutomate::getInstance()->getVariable(name);
    }

    return ivar;
}

int IVariableUIHandler::columnCount() const
{
    return 3;
}

QWidget *IVariableUIHandler::createWidget(int column, IVariable *ivar)
{
    switch (column) {
        case 0:
            return newLabel(ivar);

        case 1:
            return newEditor(ivar);

        case 2:
            return newUnit(ivar);

        case 3:
            return newDeleteButton(ivar);

    }

    Q_ASSERT(false);
    return Q_NULLPTR;
}

QWidget *IVariableUIHandler::newDeleteButton(IVariable *ivar)
{
    Q_UNUSED(ivar);
    return Q_NULLPTR;
}

QLabel *IVariableUIHandler::newLabel(IVariable *ivar)
{
    Q_UNUSED(ivar);
    QLabel *label = new QLabel(m_container);
    label->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    return label;
}

QWidget *IVariableUIHandler::newEditor(IVariable *ivar)
{
    // Keep in synch with rowChanged
    switch (ivar->getType()) {
        case type_bool: {
            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone:
                case VariableOrganTypeOutput: {
                    CSwitchButton *editor = new CSwitchButton(m_container);
                    editor->setUserData(ivar->getName());
                    editor->setChecked(ivar->toBool());

                    foreach (CToolButton *button, editor->findChildren<CToolButton *>()) {
                        button->setFixedSize(30, 30);
                    }

                    connect(editor, &CSwitchButton::clicked, this, &IVariableUIHandler::slotSwitchClicked);
                    return editor;
                }

                case VariableOrganTypeInput: {
                    break;
                }
            }

            CLedButton *editor = new CLedButton(m_container);
            editor->setUserData(ivar->getName());
            editor->setChecked(ivar->toBool());
            return editor;
        }

        case type_float: {
            CPushButton *editor = new CPushButton(m_container);
            editor->setUserData(ivar->getName());
            editor->setText(ivar->toString());

            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone:
                case VariableOrganTypeOutput: {
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestDoubleValue);
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }
            }

            return editor;
        }

        case type_int: {
            CPushButton *editor = new CPushButton(m_container);
            editor->setUserData(ivar->getName());
            editor->setText(ivar->toString());

            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone:
                case VariableOrganTypeOutput: {
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestIntegerValue);
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }
            }

            return editor;
        }

        case type_string: {
            CPushButton *editor = new CPushButton(m_container);
            editor->setUserData(ivar->getName());
            editor->setText(ivar->toString());

            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone:
                case VariableOrganTypeOutput: {
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestStringValue);
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }
            }

            return editor;
        }

        case type_stream: {
            CPushButton *editor = new CPushButton(m_container);
            editor->setUserData(ivar->getName());
            editor->setText(ivar->toString());

            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone:
                case VariableOrganTypeOutput: {
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestStream);
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }
            }

            return editor;
        }

        case type_unknow: {
            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone:
                case VariableOrganTypeOutput: {
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }
            }

            CPushButton *editor = new CPushButton(m_container);
            editor->setUserData(ivar->getName());
            editor->setText(ivar->toString());
            return editor;
        }
    }

    return Q_NULLPTR;
}

QLabel *IVariableUIHandler::newUnit(IVariable *ivar)
{
    Q_UNUSED(ivar);
    QLabel *label = new QLabel(m_container);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    return label;
}

void IVariableUIHandler::rowInserted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(ivar);
    m_containerLayout->setAlignment(row.widgets[1], Qt::AlignCenter);
}

void IVariableUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    QLabel *label = row.widgetAt<QLabel *>(0);
    QWidget *editor = row.widgetAt<QWidget *>(1);
    QLabel *labelUnit = row.widgetAt<QLabel *>(2);
    CUnit *unit = ivar->getUnit();
    label->setText(ivar->getLabel());
    labelUnit->setText(unit ? unit->getLbl() : QString());

    // Keep in synch with newEditor
    switch (ivar->getType()) {
        case type_bool: {
            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone:
                case VariableOrganTypeOutput: {
                    qobject_cast<CSwitchButton *>(editor)->setChecked(ivar->toBool());
                    return;
                }

                case VariableOrganTypeInput: {
                    break;
                }
            }

            qobject_cast<CLedButton *>(editor)->setChecked(ivar->toBool());
            return;
        }

        case type_float: {
            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone:
                case VariableOrganTypeOutput: {
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }
            }

            qobject_cast<CPushButton *>(editor)->setText(ivar->toString());
            return;
        }

        case type_int: {
            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone:
                case VariableOrganTypeOutput: {
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }
            }

            qobject_cast<CPushButton *>(editor)->setText(ivar->toString());
            return;
        }

        case type_string: {
            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone:
                case VariableOrganTypeOutput: {
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }
            }

            qobject_cast<CPushButton *>(editor)->setText(ivar->toString());
            return;
        }

        case type_stream: {
            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone:
                case VariableOrganTypeOutput: {
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }
            }

            qobject_cast<CPushButton *>(editor)->setText(ivar->toString());
            return;
        }

        case type_unknow: {
            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone:
                case VariableOrganTypeOutput: {
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }
            }

            qobject_cast<CPushButton *>(editor)->setText(ivar->toString());
            return;
        }
    }
}

void IVariableUIHandler::slotVariableChanged(const QString &name)
{
    if (!m_rows.contains(name)) {
        return;
    }

    const Row &row = m_rows[name];
    IVariable *ivar = getVariable(name);
    Q_ASSERT(ivar);

    rowChanged(row, ivar);
}

void IVariableUIHandler::slotSwitchClicked()
{
    CSwitchButton *editor = qobject_cast<CSwitchButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    ivar->setValue(editor->isChecked());
}

void IVariableUIHandler::slotRequestIntegerValue()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    CNumericalKeyboardDialog dlg(CNumericalKeyboardWidget::Integer);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        ivar->setValue(dlg.integerValue());
    }
}

void IVariableUIHandler::slotRequestDoubleValue()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    CNumericalKeyboardDialog dlg(CNumericalKeyboardWidget::Double);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        ivar->setValue(dlg.doubleValue());
    }
}

void IVariableUIHandler::slotRequestStringValue()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    CKeyboardDialog dlg;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        ivar->setValue(dlg.stringValue());
    }
}

void IVariableUIHandler::slotRequestStream()
{
    CAutomate *automate = CAutomate::getInstance();
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    IVariablePtrList streams = automate->getMapStreams().values();
    CGenericItemSelector dlg(streams);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        ivar->setValue(dlg.selectedItem()->getName());
    }
}
