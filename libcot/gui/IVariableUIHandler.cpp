#include "IVariableUIHandler.h"
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
    , m_scrollable(scrollable)
    , m_container(Q_NULLPTR)
    , m_containerLayout(Q_NULLPTR)
{
    connect(CAutomate::getInstance(), &CAutomate::signalVariableChanged,
            this, &IVariableUIHandler::slotVariableChanged);
}

void IVariableUIHandler::layout(const QList<IVariable *> &variables)
{
    // Clean old widgets
    delete m_containerLayout;
    delete m_container;
    m_rows.clear();

    // Create new rows
    m_container = new QWidget(m_scrollable);
    m_containerLayout = new QGridLayout(m_container);
    m_containerLayout->setMargin(0);

    int y = 0;
    foreach (IVariable *ivar, variables) {
        Row &row = m_rows[ivar->getName()];
        row.label = newLabel(ivar);
        row.editor = newEditor(ivar);
        row.unit = newUnit(ivar);

        m_containerLayout->addWidget(row.label, y, labelColumn());
        m_containerLayout->addWidget(row.editor, y, editorColumn());
        m_containerLayout->addWidget(row.unit, y, unitColumn());
        rowChanged(row, ivar);
        rowInserted(row);
        y++;
    }

    QSpacerItem *spacer = new QSpacerItem(8, 8, QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_containerLayout->addItem(spacer, y, 0, 1, 3);

    m_scrollable->setScrollableWidget(m_container);
}

void IVariableUIHandler::layout(const QStringList &variables)
{
    CAutomate *automate = CAutomate::getInstance();
    layout(automate->getVariables(variables));
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

int IVariableUIHandler::labelColumn() const
{
    return 0;
}

int IVariableUIHandler::editorColumn() const
{
    return 1;
}

int IVariableUIHandler::unitColumn() const
{
    return 2;
}

void IVariableUIHandler::rowInserted(const IVariableUIHandler::Row &row)
{
    m_containerLayout->setAlignment(row.editor, Qt::AlignCenter);
}

void IVariableUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    CUnit *unit = ivar->getUnit();
    row.label->setText(ivar->getLabel());
    row.unit->setText(unit ? unit->getLbl() : QString());

    // Keep in synch with newEditor
    switch (ivar->getType()) {
        case type_bool: {
            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone:
                case VariableOrganTypeOutput: {
                    qobject_cast<CSwitchButton *>(row.editor)->setChecked(ivar->toBool());
                    return;
                }

                case VariableOrganTypeInput: {
                    break;
                }
            }

            qobject_cast<CLedButton *>(row.editor)->setChecked(ivar->toBool());
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

            qobject_cast<CPushButton *>(row.editor)->setText(ivar->toString());
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

            qobject_cast<CPushButton *>(row.editor)->setText(ivar->toString());
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

            qobject_cast<CPushButton *>(row.editor)->setText(ivar->toString());
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

            qobject_cast<CPushButton *>(row.editor)->setText(ivar->toString());
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

            qobject_cast<CPushButton *>(row.editor)->setText(ivar->toString());
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
    IVariable *ivar = CAutomate::getInstance()->getVariable(name);
    Q_ASSERT(ivar);

    rowChanged(row, ivar);
}

void IVariableUIHandler::slotSwitchClicked()
{
    CSwitchButton *editor = qobject_cast<CSwitchButton *>(sender());
    IVariable *ivar = CAutomate::getInstance()->getVariable(editor->userData().toString());
    ivar->setValue(editor->isChecked());
}

void IVariableUIHandler::slotRequestIntegerValue()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = CAutomate::getInstance()->getVariable(editor->userData().toString());
    CNumericalKeyboardDialog dlg(CNumericalKeyboardWidget::Integer);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        ivar->setValue(dlg.integerValue());
    }
}

void IVariableUIHandler::slotRequestDoubleValue()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = CAutomate::getInstance()->getVariable(editor->userData().toString());
    CNumericalKeyboardDialog dlg(CNumericalKeyboardWidget::Double);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        ivar->setValue(dlg.doubleValue());
    }
}

void IVariableUIHandler::slotRequestStringValue()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = CAutomate::getInstance()->getVariable(editor->userData().toString());
    CKeyboardDialog dlg;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        ivar->setValue(dlg.stringValue());
    }
}

void IVariableUIHandler::slotRequestStream()
{
    CAutomate *automate = CAutomate::getInstance();
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = automate->getVariable(editor->userData().toString());
    IVariablePtrList streams = automate->getVariables(automate->getStreams());
    CGenericItemSelector dlg(streams);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        ivar->setValue(dlg.selectedItem()->getName());
    }

    qDeleteAll(streams);
}
