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
#include "CVariableStream.h"
#include "CVariableMeasure.h"
#include "CVariableMutable.h"
#include "IVariableInput.h"
#include "IVariableOutput.h"
#include "CModelExtensionCard.h"
#include "IAction.h"
#include "IOrgan.h"
#include "CUnit.h"

#include <QGridLayout>
#include <QLabel>
#include "cotgui_debug.h"

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

class ScopedIVariablePtrList
{
public:
    ScopedIVariablePtrList(IVariablePtrList *list) : m_list(list) {}
    ~ScopedIVariablePtrList() { CVariableFactory::deleteVariables(*m_list); }

private:
    IVariablePtrList *m_list;
};

IVariablePtrList buildTemporaryString(const PairPairStringStringList& pairs) {
    IVariablePtrList ivars;

    foreach (const PairPairStringString& pair, pairs) {
        ivars << CVariableFactory::buildTemporary(pair.first, pair.second.first, pair.second.second, type_string);
    }

    return ivars;
}

IVariablePtrList buildActionType() {
    // SERES_TODO: Provide api
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
        CVariableStream *streamVar = static_cast<CVariableStream *>(stream);

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
        CVariableStream *streamVar = static_cast<CVariableStream *>(stream);

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
    QList<CModelExtensionCard*> cards = automate->getMapExtensions().values();
    IVariablePtrList ivars;

    foreach (CModelExtensionCard *card, cards) {
        ivars << CVariableFactory::buildTemporary(card->getName(), card->getLabel(), type_string);
    }

    return ivars;
}

IVariablePtrList buildOrgans() {
    // SERES_TODO: Provide api
    CAutomate *automate = CAutomate::getInstance();
    QList<CModelExtensionCard*> cards = automate->getMapExtensions().values();
    IVariablePtrList ivars;

    foreach (CModelExtensionCard *card, cards) {
        foreach (IOrgan *organ, card->getListOrgans()) {
            ivars << CVariableFactory::buildTemporary(organ->getName(), type_string);
        }
    }

    return ivars;
}

IVariablePtrList buildUnits() {
    CAutomate *automate = CAutomate::getInstance();
    QList<CUnit *> units = automate->getListUnits();
    IVariablePtrList ivars;

    foreach (CUnit *unit, units) {
        ivars << CVariableFactory::buildTemporary(unit->getName(), unit->getLbl(), type_string);
    }

    return ivars;
}
}

IVariableUIHandler::IVariableUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : QObject(parent)
    , m_container(Q_NULLPTR)
    , m_containerLayout(Q_NULLPTR)
    , m_scrollable(scrollable)
    , m_describer(Q_NULLPTR)
{
    connect(CAutomate::getInstance(), &CAutomate::signalVariableChanged,
            this, &IVariableUIHandler::slotVariableChanged);
}

IVariableUIHandler::~IVariableUIHandler()
{
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

CScrollableWidget *IVariableUIHandler::getScrollableWidget() const
{
    return m_scrollable;
}

void IVariableUIHandler::setDescriber(IVariableObjectDescriber *describer)
{
    if (m_describer) {
        disconnect(m_describer, &IVariableObjectDescriber::signalVariableChanged, this, &IVariableUIHandler::slotVariableChanged);
        m_describer->deleteLater();
    }

    m_describer = describer;

    if (m_describer) {
        connect(m_describer, &IVariableObjectDescriber::signalVariableChanged, this, &IVariableUIHandler::slotVariableChanged);
    }
}

IVariableObjectDescriber *IVariableUIHandler::describer() const
{
    return m_describer;
}

QWidget *IVariableUIHandler::container() const
{
    return m_container;
}

QGridLayout *IVariableUIHandler::containerLayout() const
{
    return m_containerLayout;
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

bool IVariableUIHandler::selectActionType(int &value)
{
    IVariablePtrList ivars = buildActionType();
    ScopedIVariablePtrList scoped(&ivars);
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select an action type"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.selectedItem()->toInt();
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectVariableType(variableType &value)
{
    IVariablePtrList ivars = buildVariableTypes();
    ScopedIVariablePtrList scoped(&ivars);
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a variable type"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = variableType(dlg.selectedItem()->toInt());
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectOrganType(VariableOrganType &value)
{
    IVariablePtrList ivars = buildOrganTypes();
    ScopedIVariablePtrList scoped(&ivars);
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select an organ type type"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = VariableOrganType(dlg.selectedItem()->toInt());
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectCycleType(eTypeCycle &value)
{
    IVariablePtrList ivars = buildCycleTypes();
    ScopedIVariablePtrList scoped(&ivars);
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a cycle type"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = eTypeCycle(dlg.selectedItem()->toInt());
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectVariable(QString &value)
{
    IVariablePtrList ivars = buildVariables(); // don't free, hold by automate
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a variable"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.selectedItem()->getName();
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectStream(QString &value)
{
    IVariablePtrList ivars = buildStreams(); // don't free, hold by automate
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a stream"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.selectedItem()->getName();
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectMeasure(QString &value)
{
    IVariablePtrList ivars = buildMeasures(); // don't free, hold by automate
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a measure"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.selectedItem()->getName();
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectCycle(QString &value)
{
    IVariablePtrList ivars = buildCycles();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a cycle"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.selectedItem()->getName();
        return true;
    }

    CVariableFactory::deleteVariables(ivars);
    return false;
}

bool IVariableUIHandler::selectAction(QString &value)
{
    IVariablePtrList ivars = buildActions();
    ScopedIVariablePtrList scoped(&ivars);
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select an action"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.selectedItem()->getName();
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectStreamOrMeasure(QString &value)
{
    IVariablePtrList ivars = buildStreamsMeasures(); // don't free, hold by automate
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a measure or measure"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.selectedItem()->getName();
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectExtension(QString &value)
{
    IVariablePtrList ivars = buildExtensions();
    ScopedIVariablePtrList scoped(&ivars);
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select an extension"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.selectedItem()->getName();
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectOrgan(QString &value)
{
    IVariablePtrList ivars = buildOrgans();
    ScopedIVariablePtrList scoped(&ivars);
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select an organ"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.selectedItem()->getName();
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectUnit(QString &value)
{
    IVariablePtrList ivars = buildUnits();
    ScopedIVariablePtrList scoped(&ivars);
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select an unit"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.selectedItem()->getName();
        return true;
    }

    return false;
}

IVariableUIHandler::Row *IVariableUIHandler::getRow(const QString &name) const
{
    QHash<QString, Row>::iterator it = m_rows.find(name);
    return it != m_rows.end() ? &it.value() : Q_NULLPTR;
}

void IVariableUIHandler::removeRow(const QString &name)
{
    qDeleteAll(m_rows.value(name).widgets);
    m_rows.remove(name);
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

QStringList IVariableUIHandler::variableNames() const
{
    return m_rows.keys();
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

CToolButton *IVariableUIHandler::newDeleteButton(IVariable *ivar)
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
            return editor;
        }

        case type_float: {
            CPushButton *editor = new CPushButton(m_container);
            editor->setUserData(ivar->getName());

            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone:
                case VariableOrganTypeOutput: {
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestDouble);
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

            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone:
                case VariableOrganTypeOutput: {
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestInteger);
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

            switch (ivar->getOrganType()) {
                case VariableOrganTypeNone:
                case VariableOrganTypeOutput: {
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestString);
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
            return editor;
        }

        case type_mutable: {
            CVariableMutable *vmutable = static_cast<CVariableMutable *>(ivar);

            switch (vmutable->mutableType()) {
                case CVariableMutable::Undefined:
                    break;

                case CVariableMutable::CycleType: {
                    CPushButton *editor = new CPushButton(m_container);
                    editor->setUserData(ivar->getName());
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestCycleType);
                    return editor;
                }

                case CVariableMutable::Cycle: {
                    CPushButton *editor = new CPushButton(m_container);
                    editor->setUserData(ivar->getName());
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestCycle);
                    return editor;
                }

                case CVariableMutable::VariableType: {
                    CPushButton *editor = new CPushButton(m_container);
                    editor->setUserData(ivar->getName());
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestVariableType);
                    return editor;
                }

                case CVariableMutable::Unit: {
                    CPushButton *editor = new CPushButton(m_container);
                    editor->setUserData(ivar->getName());
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestUnit);
                    return editor;
                }

                case CVariableMutable::Extension: {
                    CPushButton *editor = new CPushButton(m_container);
                    editor->setUserData(ivar->getName());
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestExtension);
                    return editor;
                }

                case CVariableMutable::Organ: {
                    CPushButton *editor = new CPushButton(m_container);
                    editor->setUserData(ivar->getName());
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestOrgan);
                    return editor;
                }

                case CVariableMutable::Stream: {
                    CPushButton *editor = new CPushButton(m_container);
                    editor->setUserData(ivar->getName());
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestStream);
                    return editor;
                }

                case CVariableMutable::Format: {
                    CPushButton *editor = new CPushButton(m_container);
                    editor->setUserData(ivar->getName());
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestString);
                    return editor;
                }

                case CVariableMutable::Measure: {
                    CPushButton *editor = new CPushButton(m_container);
                    editor->setUserData(ivar->getName());
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestMeasure);
                    return editor;
                }
            }

            break;
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
    QWidget *widget = row.widgets.value(1);

    if (widget && (widget->inherits("CLedButton") || widget->inherits("CSwitchButton") )) {
        m_containerLayout->setAlignment(widget, Qt::AlignCenter);
    }
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

        case type_mutable: {
            CAutomate *automate = CAutomate::getInstance();
            CVariableMutable *vmutable = static_cast<CVariableMutable *>(ivar);
            CPushButton *button = qobject_cast<CPushButton *>(editor);

            switch (vmutable->mutableType()) {
                case CVariableMutable::Undefined:
                    break;

                case CVariableMutable::CycleType: {
                    button->setText(ICycle::typeToString(eTypeCycle(ivar->toInt())));
                    break;
                }

                case CVariableMutable::Cycle: {
                    ICycle *cycle = automate->getCycle(ivar->toString());
                    button->setText(cycle ? cycle->getLbl() : QString());
                    break;
                }

                case CVariableMutable::VariableType: {
                    button->setText(IVariable::typeToString(variableType(ivar->toInt())));
                    break;
                }

                case CVariableMutable::Unit: {
                    CUnit *unit = automate->getUnit(ivar->toString());
                    button->setText(unit ? unit->getLbl() : QString());
                    break;
                }

                case CVariableMutable::Extension: {
                    CModelExtensionCard *card = automate->getExtensionCard(ivar->toString());
                    button->setText(card ? card->getLabel() : QString());
                    break;
                }

                case CVariableMutable::Organ: {
                    IOrgan *organ = automate->getOrgan(ivar->toString());
                    button->setText(organ ? organ->getName() : QString()); // SERES_TODO: add label for organs ?
                    break;
                }

                case CVariableMutable::Stream: {
                    CVariableStream *stream = automate->getStream(ivar->toString());
                    button->setText(stream ? stream->getLabel() : QString());
                    break;
                }

                case CVariableMutable::Format: {
                    button->setText(ivar->toString());
                    break;
                }

                case CVariableMutable::Measure: {
                    CVariableMeasure *measure = automate->getMeasure(ivar->toString());
                    button->setText(measure ? measure->getLabel() : QString());
                    break;
                }
            }

            break;
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

void IVariableUIHandler::slotRequestString()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    QString value = ivar->toString();

    if (enterText(value)) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestInteger()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    int value = ivar->toInt();

    if (enterInteger(value)) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestDouble()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    double value = ivar->toFloat();

    if (enterDouble(value)) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestActionType()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    int value = ivar->toInt();

    if (selectActionType(value)) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestVariableType()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    variableType value = variableType(ivar->toInt());

    if (selectVariableType(value)) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestOrganType()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    VariableOrganType value = VariableOrganType(ivar->toInt());

    if (selectOrganType(value)) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestCycleType()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    eTypeCycle value = eTypeCycle(ivar->toInt());

    if (selectCycleType(value)) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestVariable()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    QString value = ivar->toString();

    if (selectVariable(value)) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestStream()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    QString value = ivar->toString();

    if (selectStream(value)) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestMeasure()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    QString value = ivar->toString();

    if (selectMeasure(value)) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestCycle()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    QString value = ivar->toString();

    if (selectCycle(value)) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestAction()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    QString value = ivar->toString();

    if (selectAction(value)) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestStreamOrMeasure()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    QString value = ivar->toString();

    if (selectStreamOrMeasure(value)) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestExtension()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    QString value = ivar->toString();

    if (selectExtension(value)) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestOrgan()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    QString value = ivar->toString();

    if (selectOrgan(value)) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestUnit()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    QString value = ivar->toString();

    if (selectUnit(value)) {
        ivar->setValue(value);
    }
}
