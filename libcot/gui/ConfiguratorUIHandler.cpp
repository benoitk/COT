#include "ConfiguratorUIHandler.h"
#include "CGenericItemSelector.h"
#include "CKeyboardDialog.h"
#include "CNumericalKeyboardDialog.h"
#include "CToolButton.h"
#include "CPCWindow.h"
#include "CAutomate.h"
#include "CModelExtensionCard.h"
#include "CVariableString.h"
#include "IOrgan.h"
#include "IAction.h"

namespace {
typedef QPair<QString, QVariant> PairStringString;
typedef QPair<QString, PairStringString> PairPairStringString;
typedef QList<PairPairStringString> PairPairStringStringList;

IVariablePtr build(const QString& name) {
    IVariable *ivar = new CVariableString;
    ivar->setName(name);
    ivar->setLabel(name);
    return ivar;
}

IVariablePtr build(const QString& name, const QString &label) {
    IVariable *ivar = new CVariableString;
    ivar->setName(name);
    ivar->setLabel(label);
    return ivar;
}

IVariablePtr build(const QString& name, const QString &label, const QVariant &value) {
    IVariable *ivar = new CVariableString;
    ivar->setName(name);
    ivar->setLabel(label);
    ivar->setValue(value);
    return ivar;
}

IVariablePtrList build(const QStringList& names) {
    IVariablePtrList ivars;

    foreach (const QString& name, names) {
        ivars << build(name);
    }

    return ivars;
}

IVariablePtrList build(const PairPairStringStringList& pairs) {
    IVariablePtrList ivars;

    foreach (const PairPairStringString& pair, pairs) {
        ivars << build(pair.first, pair.second.first, pair.second.second);
    }

    return ivars;
}

IVariablePtrList buildActionType() {
    // KDAB_TODO: No customer api so let fake
    return build({
                     {"calc_coef", qMakePair(ConfiguratorUIHandler::tr("Calc Coef"), 1)},
                     {"calc_rien", qMakePair(ConfiguratorUIHandler::tr("Calc Rien"), 2)},
                     {"bloc", qMakePair(ConfiguratorUIHandler::tr("Bloc"), 1000)}
                 });
}

IVariablePtrList buildVariableTypes() {
    return build({
                     {"type_bool", qMakePair(ConfiguratorUIHandler::tr("Boolean"), type_bool)},
                     {"type_float", qMakePair(ConfiguratorUIHandler::tr("Float"), type_float)},
                     {"type_int", qMakePair(ConfiguratorUIHandler::tr("Integer"), type_int)},
                     {"type_string", qMakePair(ConfiguratorUIHandler::tr("String"), type_string)},
                     {"type_stream", qMakePair(ConfiguratorUIHandler::tr("Stream"), type_stream)},
                     {"type_unknow", qMakePair(ConfiguratorUIHandler::tr("Unknown"), type_unknow)}
                 });
}

IVariablePtrList buildOrganTypes() {
    return build({
                     {"VariableOrganTypeNone", qMakePair(ConfiguratorUIHandler::tr("None"), VariableOrganTypeNone)},
                     {"VariableOrganTypeInput", qMakePair(ConfiguratorUIHandler::tr("Input"), VariableOrganTypeInput)},
                     {"VariableOrganTypeOutput", qMakePair(ConfiguratorUIHandler::tr("Output"), VariableOrganTypeOutput)}
                 });
}

IVariablePtrList buildCycleTypes() {
    return build({
                     {"CYCLE_MESURE", qMakePair(ConfiguratorUIHandler::tr("Measure"), CYCLE_MESURE)},
                     {"CYCLE_AUTONOME", qMakePair(ConfiguratorUIHandler::tr("Autonome"), CYCLE_AUTONOME)},
                     {"CYCLE_MAINTENANCE", qMakePair(ConfiguratorUIHandler::tr("Maintenance"), CYCLE_MAINTENANCE)},
                     {"CYCLE_PAUSE", qMakePair(ConfiguratorUIHandler::tr("Pause"), CYCLE_PAUSE)}
                 });
}

IVariablePtrList buildStreams() {
    // KDAB_TODO: No customer api so let fake
    CAutomate *automate = CAutomate::getInstance();
    return build(automate->getMapStreamsMeasures().keys());
}

IVariablePtrList buildMeasures() {
    // KDAB_TODO: No customer api so let fake
    CAutomate *automate = CAutomate::getInstance();
    const QMap<QString, QList<QString>> streams = automate->getMapStreamsMeasures();
    IVariablePtrList ivars;

    foreach (const QString &stream, streams.keys()) {
        foreach (const QString &measure, streams[stream]) {
            ivars << build(measure);
        }
    }

    return ivars;
}

IVariablePtrList buildCycles() {
    CAutomate *automate = CAutomate::getInstance();
    const QList<ICycle *> cycles = automate->getListCycles();
    IVariablePtrList ivars;

    foreach (ICycle *cycle, cycles) {
        ivars << build(cycle->getName(), cycle->getLbl());
    }

    return ivars;
}

IVariablePtrList buildActions() {
    CAutomate *automate = CAutomate::getInstance();
    const QList<IAction *> actions = automate->getListActions();
    IVariablePtrList ivars;

    foreach (IAction *action, actions) {
        ivars << build(action->getName(), action->getLabel());
    }

    return ivars;
}

IVariablePtrList buildStreamsMeasures() {
    // KDAB_TODO: No customer api so let fake
    CAutomate *automate = CAutomate::getInstance();
    const QMap<QString, QList<QString>> streams = automate->getMapStreamsMeasures();
    IVariablePtrList ivars;

    foreach (const QString &stream, streams.keys()) {
        ivars << build(stream);

        foreach (const QString &measure, streams[stream]) {
            ivars << build(measure, QString("%1 > %2").arg(stream).arg(measure));
        }
    }

    return ivars;
}

IVariablePtrList buildExtensions() {
    CAutomate *automate = CAutomate::getInstance();
    const QList<CModelExtensionCard *> cards = automate->getListExtensions();
    IVariablePtrList ivars;

    foreach (CModelExtensionCard *card, cards) {
        ivars << build(card->getName(), card->getLabel());
    }

    return ivars;
}

IVariablePtrList buildOrgans() {
    // KDAB_TODO: No customer api so let fake
    CAutomate *automate = CAutomate::getInstance();
    QList<CModelExtensionCard *> cards = automate->getListExtensions();
    IVariablePtrList ivars;

    foreach (CModelExtensionCard *card, cards) {
        foreach (IOrgan *organ, card->getListOrgans()) {
            ivars << build(organ->getName());
        }
    }

    return ivars;
}

void free(IVariablePtrList& ivars) {
    qDeleteAll(ivars);
    ivars.clear();
}
}

ConfiguratorUIHandler::ConfiguratorUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IVariableUIHandler(scrollable, parent)
{
}

int ConfiguratorUIHandler::selectActionType(int defaultValue)
{
    IVariablePtrList ivars = buildActionType();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select an action type"));
    dlg.setSelectedValue(defaultValue);
    int result = -1;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.selectedItem()->toInt();
    }

    free(ivars);
    return result;
}

variableType ConfiguratorUIHandler::selectVariableType(variableType defaultValue)
{
    IVariablePtrList ivars = buildVariableTypes();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a variable type"));
    dlg.setSelectedValue(defaultValue);
    variableType result = defaultValue;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = variableType(dlg.selectedItem()->toInt());
    }

    free(ivars);
    return result;
}

VariableOrganType ConfiguratorUIHandler::selectOrganType(VariableOrganType defaultValue)
{
    IVariablePtrList ivars = buildOrganTypes();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select an organ type type"));
    dlg.setSelectedValue(defaultValue);
    VariableOrganType result = defaultValue;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = VariableOrganType(dlg.selectedItem()->toInt());
    }

    free(ivars);
    return result;
}

eTypeCycle ConfiguratorUIHandler::selectCycleType(eTypeCycle defaultValue)
{
    IVariablePtrList ivars = buildCycleTypes();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a cycle type"));
    dlg.setSelectedValue(defaultValue);
    eTypeCycle result = defaultValue;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = eTypeCycle(dlg.selectedItem()->toInt());
    }

    free(ivars);
    return result;
}

QString ConfiguratorUIHandler::selectVariable(const QString &defaultName)
{
    CAutomate *automate = CAutomate::getInstance();
    IVariablePtrList ivars = automate->getMapVariables().values();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a variable"));
    dlg.setSelectedValue(defaultName);
    QString result = defaultName;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.selectedItem()->getName();
    }

    return result;
}

QString ConfiguratorUIHandler::selectStream(const QString &defaultName)
{
    IVariablePtrList ivars = buildStreams();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a stream"));
    dlg.setSelectedValue(defaultName);
    QString result = defaultName;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.selectedItem()->getName();
    }

    free(ivars);
    return result;
}

QString ConfiguratorUIHandler::selectMeasure(const QString &defaultName)
{
    IVariablePtrList ivars = buildMeasures();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a measure"));
    dlg.setSelectedValue(defaultName);
    QString result = defaultName;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.selectedItem()->getName();
    }

    free(ivars);
    return result;
}

QString ConfiguratorUIHandler::selectCycle(const QString &defaultName)
{
    IVariablePtrList ivars = buildCycles();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a cycle"));
    dlg.setSelectedValue(defaultName);
    QString result = defaultName;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.selectedItem()->getName();
    }

    free(ivars);
    return result;
}

QString ConfiguratorUIHandler::selectAction(const QString &defaultName)
{
    IVariablePtrList ivars = buildActions();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select an action"));
    dlg.setSelectedValue(defaultName);
    QString result = defaultName;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.selectedItem()->getName();
    }

    free(ivars);
    return result;
}

QString ConfiguratorUIHandler::selectStreamOrMeasure(const QString &defaultName)
{
    IVariablePtrList ivars = buildStreamsMeasures();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select a measure or measure"));
    dlg.setSelectedValue(defaultName);
    QString result = defaultName;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.selectedItem()->getName();
    }

    free(ivars);
    return result;
}

QString ConfiguratorUIHandler::selectExtension(const QString &defaultName)
{
    IVariablePtrList ivars = buildExtensions();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select an extension"));
    dlg.setSelectedValue(defaultName);
    QString result = defaultName;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.selectedItem()->getName();
    }

    free(ivars);
    return result;
}

QString ConfiguratorUIHandler::selectOrgan(const QString &defaultName)
{
    IVariablePtrList ivars = buildOrgans();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(tr("Select an organ"));
    dlg.setSelectedValue(defaultName);
    QString result = defaultName;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.selectedItem()->getName();
    }

    free(ivars);
    return result;
}

QString ConfiguratorUIHandler::enterText(const QString &defaultValue)
{
    CKeyboardDialog dlg;
    dlg.setTitle(tr("Enter a new value"));
    dlg.setStringValue(defaultValue);
    QString result = defaultValue;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.stringValue();
    }

    return result;
}

int ConfiguratorUIHandler::enterInteger(int defaultValue)
{
    CNumericalKeyboardDialog dlg(CNumericalKeyboardWidget::Integer);
    dlg.setTitle(tr("Enter a new value"));
    dlg.setIntegerValue(defaultValue);
    int result = defaultValue;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.integerValue();
    }

    return result;
}

double ConfiguratorUIHandler::enterDouble(double defaultValue)
{
    CNumericalKeyboardDialog dlg(CNumericalKeyboardWidget::Double);
    dlg.setTitle(tr("Enter a new value"));
    dlg.setDoubleValue(defaultValue);
    double result = defaultValue;

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        result = dlg.doubleValue();
    }

    return result;
}

QWidget *ConfiguratorUIHandler::newDeletor(IVariable *ivar)
{
    CToolButton *editor = new CToolButton(CToolButton::Delete);
    editor->setUserData(ivar->getName());
    editor->setText(ivar->toString());
    connect(editor, &CToolButton::clicked, this, &ConfiguratorUIHandler::slotDeletorClicked);
    return editor;
}

void ConfiguratorUIHandler::rowAboutToBeDeleted(const Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    Q_UNUSED(ivar);
}

void ConfiguratorUIHandler::slotDeletorClicked()
{
    CToolButton *editor = qobject_cast<CToolButton *>(sender());
    const QString name = editor->userData().toString();

    if (!m_rows.contains(name)) {
        Q_ASSERT(false);
        return;
    }

    IVariable *ivar = CAutomate::getInstance()->getVariable(name);
    Q_ASSERT(ivar);

    const Row &row = m_rows[name];
    rowAboutToBeDeleted(row, ivar);

    qDeleteAll(row.widgets);
    m_rows.remove(name);
}
