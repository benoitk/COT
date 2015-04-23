#include "IVariableUIHandler.h"
#include "CScrollableWidget.h"
#include "CLedButton.h"
#include "CPushButton.h"
#include "CAutomate.h"
#include "IVariable.h"
#include "IVariableInput.h"
#include "IVariableOutput.h"
#include "CUnit.h"

#include <QGridLayout>
#include <QLabel>

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
    QList<IVariable *> ivars;

    foreach (const QString &variable, variables) {
        IVariable *ivar = automate->getVariable(variable);
        Q_ASSERT(ivar);
        ivars << ivar;
    }

    layout(ivars);
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
                case VariableOrganTypeNone: {
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }

                case VariableOrganTypeOutput: {
                    break;
                }
            }

            CLedButton *editor = new CLedButton(m_container);
            editor->setChecked(ivar->toBool());
            return editor;
        }

        case type_float: {
            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone: {
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }

                case VariableOrganTypeOutput: {
                    break;
                }
            }

            CPushButton *editor = new CPushButton(m_container);
            editor->setText(ivar->toString());
            return editor;
        }

        case type_int: {
            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone: {
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }

                case VariableOrganTypeOutput: {
                    break;
                }
            }

            CPushButton *editor = new CPushButton(m_container);
            editor->setText(ivar->toString());
            return editor;
        }

        case type_string: {
            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone: {
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }

                case VariableOrganTypeOutput: {
                    break;
                }
            }

            CPushButton *editor = new CPushButton(m_container);
            editor->setText(ivar->toString());
            return editor;
        }

        case type_stream: {
            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone: {
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }

                case VariableOrganTypeOutput: {
                    break;
                }
            }

            CPushButton *editor = new CPushButton(m_container);
            editor->setText(ivar->toString());
            return editor;
        }

        case type_unknow: {
            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone: {
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }

                case VariableOrganTypeOutput: {
                    break;
                }
            }

            CPushButton *editor = new CPushButton(m_container);
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
    Q_UNUSED(row);
}

void IVariableUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    CUnit *unit = ivar->getUnit();
    row.label->setText(ivar->getLabel());
    row.unit->setText(unit ? unit->getLbl() : QString());

    switch (ivar->getType()) {
        case type_bool: {
            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone: {
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }

                case VariableOrganTypeOutput: {
                    break;
                }
            }

            qobject_cast<CLedButton *>(row.editor)->setChecked(ivar->toBool());
            break;
        }

        case type_float: {
            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone: {
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }

                case VariableOrganTypeOutput: {
                    break;
                }
            }

            qobject_cast<CPushButton *>(row.editor)->setText(ivar->toString());
            break;
        }

        case type_int: {
            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone: {
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }

                case VariableOrganTypeOutput: {
                    break;
                }
            }

            qobject_cast<CPushButton *>(row.editor)->setText(ivar->toString());
            break;
        }

        case type_string: {
            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone: {
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }

                case VariableOrganTypeOutput: {
                    break;
                }
            }

            qobject_cast<CPushButton *>(row.editor)->setText(ivar->toString());
            break;
        }

        case type_stream: {
            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone: {
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }

                case VariableOrganTypeOutput: {
                    break;
                }
            }

            qobject_cast<CPushButton *>(row.editor)->setText(ivar->toString());
            break;
        }

        case type_unknow: {
            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone: {
                    break;
                }

                case VariableOrganTypeInput: {
                    break;
                }

                case VariableOrganTypeOutput: {
                    break;
                }
            }

            qobject_cast<CPushButton *>(row.editor)->setText(ivar->toString());
            break;
        }
    }
}

void IVariableUIHandler::slotVariableChanged(const QString &name)
{
    if (!m_rows.contains(name)) {
        Q_ASSERT(false);
        return;
    }

    const Row &row = m_rows[name];
    IVariable *ivar = CAutomate::getInstance()->getVariable(name);
    Q_ASSERT(ivar);

    rowChanged(row, ivar);
}
