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
#include "CVariableVoie.h"
#include "CVariableMeasure.h"
#include "IVariableInput.h"
#include "IVariableOutput.h"
#include "CModelExtensionCard.h"
#include "IAction.h"
#include "IOrgan.h"
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

namespace {
typedef QPair<QString, QVariant> PairStringString;
typedef QPair<QString, PairStringString> PairPairStringString;
typedef QList<PairPairStringString> PairPairStringStringList;

IVariablePtrList buildTemporaryString(const PairPairStringStringList& pairs) {
    IVariablePtrList ivars;

    foreach (const PairPairStringString& pair, pairs) {
        ivars << CVariableFactory::buildTemporary(pair.first, pair.second.first, pair.second.second, type_string);
    }

    return ivars;
}

IVariablePtrList buildActionType() {
    // KDAB_TODO: No customer api so let fake
    // Note: this relates to CActionFactory::build()
    return buildTemporaryString({
                     {"calc_coef", qMakePair(IVariableUIHandler::tr("Calc Coef"), 1)},
                     {"calc_rien", qMakePair(IVariableUIHandler::tr("Calc Rien"), 2)},
                     {"cmd_pump", qMakePair(IVariableUIHandler::tr("Pump"), 3)},
                     {"cmd_relay", qMakePair(IVariableUIHandler::tr("Relay"), 3)},
                     {"block", qMakePair(IVariableUIHandler::tr("Block"), 1000)}
                 });
}

IVariablePtrList buildVariableTypes() {
    return buildTemporaryString({
                     {"type_bool", qMakePair(IVariableUIHandler::tr("Boolean"), type_bool)},
                     {"type_float", qMakePair(IVariableUIHandler::tr("Float"), type_float)},
                     {"type_int", qMakePair(IVariableUIHandler::tr("Integer"), type_int)},
                     {"type_string", qMakePair(IVariableUIHandler::tr("String"), type_string)},
                     {"type_stream", qMakePair(IVariableUIHandler::tr("Stream"), type_stream)},
                     {"type_unknow", qMakePair(IVariableUIHandler::tr("Unknown"), type_unknow)}
                 });
}

IVariablePtrList buildOrganTypes() {
    return buildTemporaryString({
                     {"VariableOrganTypeNone", qMakePair(IVariableUIHandler::tr("None"), VariableOrganTypeNone)},
                     {"VariableOrganTypeInput", qMakePair(IVariableUIHandler::tr("Input"), VariableOrganTypeInput)},
                     {"VariableOrganTypeOutput", qMakePair(IVariableUIHandler::tr("Output"), VariableOrganTypeOutput)}
                 });
}

IVariablePtrList buildCycleTypes() {
    return buildTemporaryString({
                     {"CYCLE_MESURE", qMakePair(IVariableUIHandler::tr("Measure"), CYCLE_MESURE)},
                     {"CYCLE_AUTONOME", qMakePair(IVariableUIHandler::tr("Autonome"), CYCLE_AUTONOME)},
                     {"CYCLE_MAINTENANCE", qMakePair(IVariableUIHandler::tr("Maintenance"), CYCLE_MAINTENANCE)},
                     {"CYCLE_PAUSE", qMakePair(IVariableUIHandler::tr("Pause"), CYCLE_PAUSE)}
                 });
}

IVariablePtrList buildVariables() {
    CAutomate *automate = CAutomate::getInstance();
    return automate->getMapVariables().values();
}

IVariablePtrList buildStreams() {
    CAutomate *automate = CAutomate::getInstance();
    return automate->getMapStreams().values();
}

IVariablePtrList buildMeasures() {
    const IVariablePtrList streams = buildStreams();
    IVariablePtrList ivars;

    foreach (IVariable *stream, streams) {
        CVariableVoie *streamVar = static_cast<CVariableVoie *>(stream);

        foreach (IVariable *measure, streamVar->getListMeasures()) {
            CVariableMeasure *measureVar = static_cast<CVariableMeasure *>(measure);
            ivars << measureVar->getListVariables();
        }
    }

    return ivars;
}

IVariablePtrList buildCycles() {
    CAutomate *automate = CAutomate::getInstance();
    const QList<ICycle *> cycles = automate->getListCycles();
    IVariablePtrList ivars;

    foreach (ICycle *cycle, cycles) {
        ivars << CVariableFactory::buildTemporary(cycle->getName(), cycle->getLbl(), type_string);
    }

    return ivars;
}

IVariablePtrList buildActions() {
    CAutomate *automate = CAutomate::getInstance();
    const QList<IAction *> actions = automate->getListActions();
    IVariablePtrList ivars;

    foreach (IAction *action, actions) {
        ivars << CVariableFactory::buildTemporary(action->getName(), action->getLabel(), type_string);
    }

    return ivars;
}

IVariablePtrList buildStreamsMeasures() {
    CAutomate *automate = CAutomate::getInstance();
    const QMap<QString, IVariable *> streams = automate->getMapStreams();
    IVariablePtrList ivars;

    foreach (IVariable *stream, streams.values()) {
        CVariableVoie *streamVar = static_cast<CVariableVoie *>(stream);

        ivars << stream;

        foreach (IVariable *measure, streamVar->getListMeasures()) {
            CVariableMeasure *measureVar = static_cast<CVariableMeasure *>(measure);

            ivars << measureVar->getMeasureVariable();
        }
    }

    return ivars;
}

IVariablePtrList buildExtensions() {
    CAutomate *automate = CAutomate::getInstance();
    QMap<QString, CModelExtensionCard*> cards = automate->getMapExtensions();
    IVariablePtrList ivars;
    QMapIterator<QString, CModelExtensionCard*> i(cards);
    while (i.hasNext()) {
        i.next();
        ivars << CVariableFactory::buildTemporary(i.value()->getName(), i.value()->getLabel(), type_string);
    }
    return ivars;
}

IVariablePtrList buildOrgans() {
    // KDAB_TODO: No customer api so let fake
    CAutomate *automate = CAutomate::getInstance();
    QMap<QString, CModelExtensionCard*> cards = automate->getMapExtensions();
    IVariablePtrList ivars;
    QMapIterator<QString, CModelExtensionCard*> i(cards);
    while (i.hasNext()) {
        i.next();
        foreach (IOrgan *organ, i.value()->getListOrgans()) {
            ivars << CVariableFactory::buildTemporary(organ->getName(), type_string);
        }
    }

    return ivars;
}
}

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

bool IVariableUIHandler::enterText(QString &value)
{
    CKeyboardDialog dlg;
    dlg.setTitle(tr("Enter a new value"));
    dlg.setStringValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.stringValue();
        return true;
    }

    return false;
}

bool IVariableUIHandler::enterInteger(int &value)
{
    CNumericalKeyboardDialog dlg(CNumericalKeyboardWidget::Integer);
    dlg.setTitle(tr("Enter a new value"));
    dlg.setIntegerValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.integerValue();
        return true;
    }

    return false;
}

bool IVariableUIHandler::enterDouble(double &value)
{
    CNumericalKeyboardDialog dlg(CNumericalKeyboardWidget::Double);
    dlg.setTitle(tr("Enter a new value"));
    dlg.setDoubleValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.doubleValue();
        return true;
    }

    return false;
}

int  IVariableUIHandler::selectActionType(int defaultValue)
{
    IVariablePtrList ivars = buildActionType();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select an action type"));
    dlg.setSelectedValue(defaultValue);
    int result = -1;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.selectedItem()->toInt();
    }

    CVariableFactory::deleteVariables(ivars);
    return result;
}

variableType  IVariableUIHandler::selectVariableType(variableType defaultValue)
{
    IVariablePtrList ivars = buildVariableTypes();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a variable type"));
    dlg.setSelectedValue(defaultValue);
    variableType result = defaultValue;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = variableType(dlg.selectedItem()->toInt());
    }

    CVariableFactory::deleteVariables(ivars);
    return result;
}

VariableOrganType  IVariableUIHandler::selectOrganType(VariableOrganType defaultValue)
{
    IVariablePtrList ivars = buildOrganTypes();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select an organ type type"));
    dlg.setSelectedValue(defaultValue);
    VariableOrganType result = defaultValue;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = VariableOrganType(dlg.selectedItem()->toInt());
    }

    CVariableFactory::deleteVariables(ivars);
    return result;
}

eTypeCycle  IVariableUIHandler::selectCycleType(eTypeCycle defaultValue)
{
    IVariablePtrList ivars = buildCycleTypes();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a cycle type"));
    dlg.setSelectedValue(defaultValue);
    eTypeCycle result = defaultValue;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = eTypeCycle(dlg.selectedItem()->toInt());
    }

    CVariableFactory::deleteVariables(ivars);
    return result;
}

QString  IVariableUIHandler::selectVariable(const QString &defaultName)
{
    IVariablePtrList ivars = buildVariables();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a variable"));
    dlg.setSelectedValue(defaultName);
    QString result = defaultName;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.selectedItem()->getName();
    }

    //Don't add free(ivars) as variables comes directly from automate
    return result;
}

QString  IVariableUIHandler::selectStream(const QString &defaultName)
{
    IVariablePtrList ivars = buildStreams();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a stream"));
    dlg.setSelectedValue(defaultName);
    QString result = defaultName;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.selectedItem()->getName();
    }

    //Don't add free(ivars) as variables comes directly from automate
    return result;
}

QString  IVariableUIHandler::selectMeasure(const QString &defaultName)
{
    IVariablePtrList ivars = buildMeasures();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a measure"));
    dlg.setSelectedValue(defaultName);
    QString result = defaultName;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.selectedItem()->getName();
    }

    //Don't add free(ivars) as variables comes directly from automate
    return result;
}

QString  IVariableUIHandler::selectCycle(const QString &defaultName)
{
    IVariablePtrList ivars = buildCycles();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a cycle"));
    dlg.setSelectedValue(defaultName);
    QString result = defaultName;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.selectedItem()->getName();
    }

    CVariableFactory::deleteVariables(ivars);
    return result;
}

QString  IVariableUIHandler::selectAction(const QString &defaultName)
{
    IVariablePtrList ivars = buildActions();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select an action"));
    dlg.setSelectedValue(defaultName);
    QString result = defaultName;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.selectedItem()->getName();
    }

    CVariableFactory::deleteVariables(ivars);
    return result;
}

QString  IVariableUIHandler::selectStreamOrMeasure(const QString &defaultName)
{
    IVariablePtrList ivars = buildStreamsMeasures();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a measure or measure"));
    dlg.setSelectedValue(defaultName);
    QString result = defaultName;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.selectedItem()->getName();
    }

    //Don't add free(ivars) as variables comes directly from automate
    return result;
}

QString  IVariableUIHandler::selectExtension(const QString &defaultName)
{
    IVariablePtrList ivars = buildExtensions();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select an extension"));
    dlg.setSelectedValue(defaultName);
    QString result = defaultName;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.selectedItem()->getName();
    }

    CVariableFactory::deleteVariables(ivars);
    return result;
}

QString  IVariableUIHandler::selectOrgan(const QString &defaultName)
{
    IVariablePtrList ivars = buildOrgans();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select an organ"));
    dlg.setSelectedValue(defaultName);
    QString result = defaultName;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.selectedItem()->getName();
    }

    CVariableFactory::deleteVariables(ivars);
    return result;
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
    int value = ivar->toInt();

    if (enterInteger(value)) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestDoubleValue()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    double value = ivar->toFloat();

    if (enterDouble(value)) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestStringValue()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    QString value = ivar->toString();

    if (enterText(value)) {
        ivar->setValue(value);
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
