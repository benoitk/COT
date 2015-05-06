#include "IConfiguratorUIHandler.h"
#include "CGenericItemSelector.h"
#include "CKeyboardDialog.h"
#include "CNumericalKeyboardDialog.h"
#include "CToolButton.h"
#include "CPCWindow.h"
#include "CAutomate.h"
#include "CModelExtensionCard.h"
#include "CVariableFactory.h"
#include "CVariableVoie.h"
#include "CVariableMeasure.h"
#include "IOrgan.h"
#include "IAction.h"

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
                     {"calc_coef", qMakePair(IConfiguratorUIHandler::tr("Calc Coef"), 1)},
                     {"calc_rien", qMakePair(IConfiguratorUIHandler::tr("Calc Rien"), 2)},
                     {"cmd_pump", qMakePair(IConfiguratorUIHandler::tr("Pump"), 3)},
                     {"cmd_relay", qMakePair(IConfiguratorUIHandler::tr("Relay"), 3)},
                     {"block", qMakePair(IConfiguratorUIHandler::tr("Block"), 1000)}
                 });
}

IVariablePtrList buildVariableTypes() {
    return buildTemporaryString({
                     {"type_bool", qMakePair(IConfiguratorUIHandler::tr("Boolean"), type_bool)},
                     {"type_float", qMakePair(IConfiguratorUIHandler::tr("Float"), type_float)},
                     {"type_int", qMakePair(IConfiguratorUIHandler::tr("Integer"), type_int)},
                     {"type_string", qMakePair(IConfiguratorUIHandler::tr("String"), type_string)},
                     {"type_stream", qMakePair(IConfiguratorUIHandler::tr("Stream"), type_stream)},
                     {"type_unknow", qMakePair(IConfiguratorUIHandler::tr("Unknown"), type_unknow)}
                 });
}

IVariablePtrList buildOrganTypes() {
    return buildTemporaryString({
                     {"VariableOrganTypeNone", qMakePair(IConfiguratorUIHandler::tr("None"), VariableOrganTypeNone)},
                     {"VariableOrganTypeInput", qMakePair(IConfiguratorUIHandler::tr("Input"), VariableOrganTypeInput)},
                     {"VariableOrganTypeOutput", qMakePair(IConfiguratorUIHandler::tr("Output"), VariableOrganTypeOutput)}
                 });
}

IVariablePtrList buildCycleTypes() {
    return buildTemporaryString({
                     {"CYCLE_MESURE", qMakePair(IConfiguratorUIHandler::tr("Measure"), CYCLE_MESURE)},
                     {"CYCLE_AUTONOME", qMakePair(IConfiguratorUIHandler::tr("Autonome"), CYCLE_AUTONOME)},
                     {"CYCLE_MAINTENANCE", qMakePair(IConfiguratorUIHandler::tr("Maintenance"), CYCLE_MAINTENANCE)},
                     {"CYCLE_PAUSE", qMakePair(IConfiguratorUIHandler::tr("Pause"), CYCLE_PAUSE)}
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

IConfiguratorUIHandler::IConfiguratorUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IVariableUIHandler(scrollable, parent)
{
}

int IConfiguratorUIHandler::selectActionType(int defaultValue)
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

variableType IConfiguratorUIHandler::selectVariableType(variableType defaultValue)
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

VariableOrganType IConfiguratorUIHandler::selectOrganType(VariableOrganType defaultValue)
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

eTypeCycle IConfiguratorUIHandler::selectCycleType(eTypeCycle defaultValue)
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

QString IConfiguratorUIHandler::selectVariable(const QString &defaultName)
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

QString IConfiguratorUIHandler::selectStream(const QString &defaultName)
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

QString IConfiguratorUIHandler::selectMeasure(const QString &defaultName)
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

QString IConfiguratorUIHandler::selectCycle(const QString &defaultName)
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

QString IConfiguratorUIHandler::selectAction(const QString &defaultName)
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

QString IConfiguratorUIHandler::selectStreamOrMeasure(const QString &defaultName)
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

QString IConfiguratorUIHandler::selectExtension(const QString &defaultName)
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

QString IConfiguratorUIHandler::selectOrgan(const QString &defaultName)
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

QWidget *IConfiguratorUIHandler::newDeleteButton(IVariable *ivar)
{
    CToolButton *editor = new CToolButton(CToolButton::Delete);
    editor->setFixedSize(21, 21);
    editor->setUserData(ivar->getName());
    editor->setText(ivar->toString());
    connect(editor, &CToolButton::clicked, this, &IConfiguratorUIHandler::slotDeleteClicked);
    return editor;
}

void IConfiguratorUIHandler::rowAboutToBeDeleted(const Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    Q_UNUSED(ivar);
}

void IConfiguratorUIHandler::slotDeleteClicked()
{
    CToolButton *editor = qobject_cast<CToolButton *>(sender());
    const QString name = editor->userData().toString();

    if (!m_rows.contains(name)) {
        Q_ASSERT(false);
        return;
    }

    IVariable *ivar = getVariable(name);
    Q_ASSERT(ivar);

    const Row &row = m_rows[name];
    rowAboutToBeDeleted(row, ivar);

    qDeleteAll(row.widgets);
    m_rows.remove(name);
}
