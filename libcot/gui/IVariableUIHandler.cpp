#include "IVariableUIHandler.h"
#include "IVariableObjectDescriber.h"
#include "CScrollableWidget.h"
#include "CScrollablePagerWidget.h"
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
#include "StyleRepository.h"
#include "CClickableLabel.h"

#include <QGridLayout>
#include <QScrollBar>
#include <QDebug>
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
        ivars << CVariableFactory::buildTemporary(pair.first, pair.second.first, pair.second.second, e_type_string);
    }

    return ivars;
}

IVariablePtrList buildActionType() {
    // SERES_TODO: Provide api (COT-54)
    // Note: this relates to CActionFactory::build()
    return buildTemporaryString(PairPairStringStringList()
                                    << PairPairStringString("type_block", qMakePair(IAction::typeToString(type_block), type_block))
                                    << PairPairStringString("type_cmd_pump", qMakePair(IAction::typeToString(type_cmd_pump), type_cmd_pump))
                                    << PairPairStringString("type_cmd_digital_output", qMakePair(IAction::typeToString(type_cmd_digital_output), type_cmd_digital_output))
                                    << PairPairStringString("type_rewrite_output", qMakePair(IAction::typeToString(type_rewrite_output), type_rewrite_output))
                                    << PairPairStringString("type_cmd_dc_engine", qMakePair(IAction::typeToString(type_cmd_dc_engine), type_cmd_dc_engine))
                                    << PairPairStringString("type_cmd_read_input", qMakePair(IAction::typeToString(type_cmd_read_input), type_cmd_read_input))
                                    << PairPairStringString("type_test", qMakePair(IAction::typeToString(type_test), type_test))
                                    << PairPairStringString("type_acquisition_cit_npoc", qMakePair(IAction::typeToString(type_acquisition_cit_npoc), type_acquisition_cit_npoc))
                                    << PairPairStringString("type_block", qMakePair(IAction::typeToString(type_block), type_block))
                                    << PairPairStringString("type_block", qMakePair(IAction::typeToString(type_block), type_block))
                                    << PairPairStringString("type_block", qMakePair(IAction::typeToString(type_block), type_block))
                                );
}

IVariablePtrList buildVariableTypes() {
    // SERES_TODO: Provide api (COT-55)
    return buildTemporaryString(PairPairStringStringList() <<
                                    PairPairStringString("type_bool", qMakePair(IVariableUIHandler::tr("Boolean"), e_type_bool)) <<
                                    PairPairStringString("type_float", qMakePair(IVariableUIHandler::tr("Float"), e_type_float)) <<
                                    PairPairStringString("type_int", qMakePair(IVariableUIHandler::tr("Integer"), e_type_int)) <<
                                    PairPairStringString("type_string", qMakePair(IVariableUIHandler::tr("String"), e_type_string)) <<
                                    PairPairStringString("type_stream", qMakePair(IVariableUIHandler::tr("Stream"), e_type_stream))
                                );
}

IVariablePtrList buildOrganTypes() {
    // SERES_TODO: Provide api (COT-56)
    return buildTemporaryString(PairPairStringStringList() <<
                                    PairPairStringString("VariableOrganTypeNone", qMakePair(IVariableUIHandler::tr("None"), e_type_organ_none)) <<
                                    PairPairStringString("VariableOrganTypeInput", qMakePair(IVariableUIHandler::tr("Input"), e_type_organ_input)) <<
                                    PairPairStringString("VariableOrganTypeOutput", qMakePair(IVariableUIHandler::tr("Output"), e_type_organ_output))
                                );
}


IVariablePtrList buildCycleTypes() {
    // SERES_TODO: Provide api (COT-57)
    return buildTemporaryString(PairPairStringStringList() <<
                                    PairPairStringString("CYCLE_MESURE", qMakePair(IVariableUIHandler::tr("Measure"), e_cycle_measure)) <<
                                    PairPairStringString("CYCLE_AUTONOME", qMakePair(IVariableUIHandler::tr("Autonome"), e_cycle_autonome)) <<
                                    PairPairStringString("CYCLE_MAINTENANCE", qMakePair(IVariableUIHandler::tr("Maintenance"), e_cycle_maintenance)) <<
                                    PairPairStringString("CYCLE_PAUSE", qMakePair(IVariableUIHandler::tr("Pause"), e_cycle_pause))
                                );
}

IVariablePtrList buildVariables() {
    CAutomate *automate = CAutomate::getInstance();
    return automate->getMapVariables().values();
}

//IVariablePtrList buildStreams() {
QList<CVariableStream*> buildStreams() {
CAutomate *automate = CAutomate::getInstance();
    return automate->getListStreams();
}

IVariablePtrList buildMeasures() {
    const QList<CVariableStream*> streams = buildStreams();
    IVariablePtrList ivars;

    foreach (CVariableStream *streamVar, streams) {
        ivars << streamVar->getListMeasures();
    }

    return ivars;
}

IVariablePtrList buildCycles() {
    CAutomate *automate = CAutomate::getInstance();
    const QList<ICycle *> cycles = automate->getListCycles();
    IVariablePtrList ivars;

    foreach (ICycle *cycle, cycles) {
        ivars << CVariableFactory::buildTemporary(cycle->getName(), cycle->getLabel(), e_type_string);
    }

    return ivars;
}

IVariablePtrList buildActions() {
    CAutomate *automate = CAutomate::getInstance();
    const QList<IAction *> actions = automate->getListActions();
    IVariablePtrList ivars;

    foreach (IAction *action, actions) {
        ivars << CVariableFactory::buildTemporary(action->getName(), action->getLabel(), e_type_string);
    }

    return ivars;
}

IVariablePtrList buildStreamsMeasures() {
    CAutomate *automate = CAutomate::getInstance();
    const QList<CVariableStream *> streams = automate->getListStreams();
    IVariablePtrList ivars;

    ivars << CVariableFactory::buildTemporary(QString(), IVariableUIHandler::tr("Analyzer"), e_type_string);

    foreach (CVariableStream *streamVar, streams) {
        ivars << CVariableFactory::buildTemporary(streamVar->getName(), streamVar->getLabel(), e_type_string);

        foreach (IVariable *measure, streamVar->getListMeasures()) {
            CVariableMeasure *measureVar = static_cast<CVariableMeasure *>(measure);
            IVariable *ivar = CVariableFactory::buildTemporary(measureVar->getName(), measureVar->getLabel(), e_type_string);
            ivar->setLabel(QString("%1 / %2").arg(streamVar->getLabel()).arg(measureVar->getLabel()));
            ivars << ivar;
        }
    }

    return ivars;
}

IVariablePtrList buildExtensions() {
    CAutomate *automate = CAutomate::getInstance();
    QList<CModelExtensionCard*> cards = automate->getMapExtensions().values();
    IVariablePtrList ivars;

    foreach (CModelExtensionCard *card, cards) {
        ivars << CVariableFactory::buildTemporary(card->getName(), card->getLabel(), e_type_string);
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
            ivars << CVariableFactory::buildTemporary(organ->getName(), e_type_string);
        }
    }

    return ivars;
}

IVariablePtrList buildUnits() {
    CAutomate *automate = CAutomate::getInstance();
    QList<CUnit *> units = automate->getListUnits();
    IVariablePtrList ivars;

    foreach (CUnit *unit, units) {
        ivars << CVariableFactory::buildTemporary(unit->getName(), unit->getLabel(), e_type_string);
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
    Q_ASSERT(scrollable);

    connect(CAutomate::getInstance(), &CAutomate::signalVariableChanged,
            this, &IVariableUIHandler::slotVariableChanged);
}

IVariableUIHandler::~IVariableUIHandler()
{
}

void IVariableUIHandler::layout(const QList<IVariable *> &variables, bool addDeleteButton)
{
    // remember vscroll position to restore it after.
    const int vscroll = m_scrollable->verticalScrollBar()->value();

    // Clean old widgets
    delete m_containerLayout;
    delete m_container;
    m_rows.clear();

    // Create new rows
    m_container = new CScrollablePagerWidget(m_scrollable);
    m_containerLayout = new QGridLayout(m_container);
    m_containerLayout->setMargin(0);

    int minRowHeight = 0;
    const int numberOfColumn = addDeleteButton ? (columnCount() + 1) : columnCount();
    int y = 0;
    foreach (IVariable *ivar, variables) {
        // Attention si m_name est vide : comme était initialisé dans ConfiguratorVariablesUIHandler::layout()
        // -> plante lors d'un appel à ConfiguratorVariablesUIHandler::rowChanged
        if(ivar->getName() != ""){ //Fait par SERES : à modifier ?
            Row &row = m_rows[ivar->getName()];

            for (int x = 0; x < numberOfColumn; ++x) {
                QWidget *widget = createWidget(x, ivar);
                // it intentional to put possible null entry in list, so we can still rely on column to get correct widget.
                row.widgets << widget;

                if (widget) {
                    m_containerLayout->addWidget(widget, y, x);
                    minRowHeight = qMax(minRowHeight, widget->minimumSizeHint().height());
                }
            }
            rowChanged(row, ivar);
            rowInserted(row, ivar);
            y++;
        }
    }

    // For pagination to work ok we need all rows to have the same height
    //qDebug() << m_scrollable->parentWidget() << "minRowHeight=" << minRowHeight;
    for (int row = 0 ; row < m_containerLayout->rowCount() ; ++row) {
        m_containerLayout->setRowMinimumHeight(row, minRowHeight);
    }

    if (verticalStretch()) {
        m_containerLayout->setRowStretch(y, 1);
    }

    if (horizontalStretch()) {
        m_containerLayout->setColumnStretch(numberOfColumn, 1);
    }

    m_scrollable->setScrollablePagerWidget(m_container);

    m_container->ensurePolished();
    m_container->repaint();
    m_scrollable->ensurePolished();
    m_scrollable->viewport()->ensurePolished();
    m_scrollable->verticalScrollBar()->setValue(vscroll);

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

CScrollablePagerWidget *IVariableUIHandler::container() const
{
    return m_container;
}

QGridLayout *IVariableUIHandler::containerLayout() const
{
    return m_containerLayout;
}

bool IVariableUIHandler::enterText(QString &value, const QString &title)
{
    CKeyboardDialog dlg;
    dlg.setTitle(!title.isEmpty() ? title : tr("Enter a new value"));
    dlg.setStringValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.stringValue();
        return true;
    }

    return false;
}

bool IVariableUIHandler::enterInteger(int &value, const QString &title)
{
    return CNumericalKeyboardDialog::getInteger(value, title);
}

bool IVariableUIHandler::enterFloat(float &value, const QString &title)
{
    CNumericalKeyboardDialog dlg(CNumericalKeyboardWidget::Double);
    dlg.setTitle(!title.isEmpty() ? title : tr("Enter a new value"));
    dlg.setFloatValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.floatValue();
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectActionType(actionType &value, const QString &title)
{
    IVariablePtrList ivars = buildActionType();
    ScopedIVariablePtrList scoped(&ivars);
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(!title.isEmpty() ? title : tr("Select an action type"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = static_cast<actionType>(dlg.selectedItem()->toInt());
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectVariableType(enumVariableType &value, const QString &title)
{
    IVariablePtrList ivars = buildVariableTypes();
    ScopedIVariablePtrList scoped(&ivars);
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(!title.isEmpty() ? title : tr("Select a variable type"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = enumVariableType(dlg.selectedItem()->toInt());
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectOrganType(enumVariableOrganType &value, const QString &title)
{
    IVariablePtrList ivars = buildOrganTypes();
    ScopedIVariablePtrList scoped(&ivars);
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(!title.isEmpty() ? title : tr("Select an organ type type"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = enumVariableOrganType(dlg.selectedItem()->toInt());
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectCycleType(enumTypeCycle &value, const QString &title)
{
    IVariablePtrList ivars = buildCycleTypes();
    ScopedIVariablePtrList scoped(&ivars);
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(!title.isEmpty() ? title : tr("Select a cycle type"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = enumTypeCycle(dlg.selectedItem()->toInt());
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectVariable(QString &value, const QString &title)
{
    IVariablePtrList ivars = buildVariables(); // don't free, hold by automate
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(!title.isEmpty() ? title : tr("Select a variable"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.selectedItem()->getName();
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectStream(QString &value, const QString &title)
{
    //TO DO : vérifier le fonctionnement

    IVariablePtrList ivars;// = buildStreams(); // don't free, hold by automate
    foreach(CVariableStream* stream, buildStreams()){
        ivars << stream;
    }
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(!title.isEmpty() ? title : tr("Select a stream"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.selectedItem()->getName();
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectMeasure(QString &value, const QString &title)
{
    IVariablePtrList ivars = buildMeasures(); // don't free, hold by automate
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(!title.isEmpty() ? title : tr("Select a measure"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.selectedItem()->getName();
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectCycle(QString &value, const QString &title)
{
    IVariablePtrList ivars = buildCycles();
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(!title.isEmpty() ? title : tr("Select a cycle"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.selectedItem()->getName();
        return true;
    }

    CVariableFactory::deleteVariables(ivars);
    return false;
}

bool IVariableUIHandler::selectAction(QString &value, const QString &title)
{
    IVariablePtrList ivars = buildActions();
    ScopedIVariablePtrList scoped(&ivars);
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(!title.isEmpty() ? title : tr("Select an action"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.selectedItem()->getName();
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectStreamOrMeasure(QString &value, const QString &title)
{
    IVariablePtrList ivars = buildStreamsMeasures();
    ScopedIVariablePtrList scoped(&ivars);
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(!title.isEmpty() ? title : tr("Select a stream or measure"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.selectedItem()->getName();
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectExtension(QString &value, const QString &title)
{
    IVariablePtrList ivars = buildExtensions();
    ScopedIVariablePtrList scoped(&ivars);
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(!title.isEmpty() ? title : tr("Select an extension"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.selectedItem()->getName();
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectOrgan(QString &value, const QString &title)
{
    IVariablePtrList ivars = buildOrgans();
    ScopedIVariablePtrList scoped(&ivars);
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(!title.isEmpty() ? title : tr("Select an organ"));
    dlg.setSelectedValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.selectedItem()->getName();
        return true;
    }

    return false;
}

bool IVariableUIHandler::selectUnit(QString &value, const QString &title)
{
    IVariablePtrList ivars = buildUnits();
    ScopedIVariablePtrList scoped(&ivars);
    CGenericItemSelector dlg(ivars);
    dlg.setTitle(!title.isEmpty() ? title : tr("Select an unit"));
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
    Row row = m_rows.take(name);

    for (auto it = row.widgets.begin(), end = row.widgets.end(); it != end; ++it) {
        QWidget* widget = (*it);

        if (!widget) {
            continue;
        }

        widget->setParent(0);
        widget->hide();
        widget->deleteLater();
    }
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

int IVariableUIHandler::layoutRow(const IVariableUIHandler::Row &row) const
{
    foreach (QWidget *widget, row.widgets) {
        const int r = layoutRow(widget);

        if (r >= 0) {
            return r;
        }
    }

    return -1;
}

IVariable *IVariableUIHandler::getVariable(const QString &name) const
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

bool IVariableUIHandler::horizontalStretch() const
{
    return true;
}

bool IVariableUIHandler::verticalStretch() const
{
    return true;
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

void IVariableUIHandler::setVariableAccess(IVariable *ivar, enumVariableAccess access)
{
    if (ivar) {
        ivar->setAccess(access);
    }
}

CClickableLabel *IVariableUIHandler::newLabel(IVariable *ivar)
{
    Q_UNUSED(ivar);
    CClickableLabel *label = new CClickableLabel(m_container);
    label->setUserData(ivar->getName());
    return label;
}

QWidget *IVariableUIHandler::newEditor(IVariable *ivar)
{
    // Keep in synch with rowChanged
    switch (ivar->getType()) {
        case e_type_alarm:{
        CLedButton *editor = new CLedButton(m_container);
        editor->setUserData(ivar->getName());
        return editor;
    }
        case e_type_bool: {
            switch (ivar->getOrganType()) {
                case e_type_organ_none:
                case e_type_organ_output: {
                    CSwitchButton *editor = new CSwitchButton(m_container);
                    editor->setUserData(ivar->getName());

                    foreach (CToolButton *button, editor->findChildren<CToolButton *>()) {
                        button->setFixedSize(StyleRepository::configuratorButtonSize());
                    }

                    connect(editor, &CSwitchButton::clicked, this, &IVariableUIHandler::slotSwitchClicked);
                    return editor;
                }

                case e_type_organ_input: {
                    break;
                }
            }

            CLedButton *editor = new CLedButton(m_container);
            editor->setUserData(ivar->getName());
            return editor;
        }

        case e_type_float: {
            CPushButton *editor = new CPushButton(m_container);
            editor->setUserData(ivar->getName());

            switch (ivar->getOrganType()) {
                case e_type_organ_none:
                case e_type_organ_output: {
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestDouble);
                    break;
                }

                case e_type_organ_input: {
                    break;
                }
            }

            return editor;
        }

        case e_type_int: {
            CPushButton *editor = new CPushButton(m_container);
            editor->setUserData(ivar->getName());

            switch (ivar->getOrganType()) {
                case e_type_organ_none:
                case e_type_organ_output: {
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestInteger);
                    break;
                }

                case e_type_organ_input: {
                    break;
                }
            }

            return editor;
        }

        case e_type_string: {
            CPushButton *editor = new CPushButton(m_container);
            editor->setUserData(ivar->getName());

            switch (ivar->getOrganType()) {
                case e_type_organ_none:
                case e_type_organ_output: {
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestString);
                    break;
                }

                case e_type_organ_input: {
                    break;
                }
            }

            return editor;
        }

        case e_type_stream: {
            CPushButton *editor = new CPushButton(m_container);
            editor->setUserData(ivar->getName());

            switch (ivar->getOrganType()) {
                case e_type_organ_none:
                case e_type_organ_output: {
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestStream);
                    break;
                }

                case e_type_organ_input: {
                    break;
                }
            }

            return editor;
        }

        case e_type_measure: {
            CPushButton *editor = new CPushButton(m_container);
            editor->setUserData(ivar->getName());

            switch (ivar->getOrganType()) {
                case e_type_organ_none:
                case e_type_organ_output: {
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestMeasure);
                    break;
                }

                case e_type_organ_input: {
                    break;
                }
            }

            return editor;
        }

        case e_type_unknow: {
            switch (ivar->getOrganType()) {
                case e_type_organ_none:
                case e_type_organ_output: {
                    break;
                }

                case e_type_organ_input: {
                    break;
                }
            }

            CPushButton *editor = new CPushButton(m_container);
            editor->setUserData(ivar->getName());
            return editor;
        }

        case e_type_list_variables:
            break;

        case type_mutable: {
            CVariableMutable *vmutable = static_cast<CVariableMutable *>(ivar);

            switch (vmutable->mutableType()) {
                case CVariableMutable::Undefined: {
                    CPushButton *editor = new CPushButton(m_container);
                    editor->setUserData(ivar->getName());
                    return editor;
                }

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

                case CVariableMutable::VarOrganType: {
                    CPushButton *editor = new CPushButton(m_container);
                    editor->setUserData(ivar->getName());
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestOrganType);
                    return editor;
                }

                case CVariableMutable::Variable: {
                    CPushButton *editor = new CPushButton(m_container);
                    editor->setUserData(ivar->getName());
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestVariable);
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

                case CVariableMutable::Action: {
                    CPushButton *editor = new CPushButton(m_container);
                    editor->setUserData(ivar->getName());
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestAction);
                    return editor;
                }

                case CVariableMutable::ActionType: {
                    CPushButton *editor = new CPushButton(m_container);
                    editor->setUserData(ivar->getName());
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestActionType);
                    return editor;
                }

                case CVariableMutable::StreamOrMeasure: {
                    CPushButton *editor = new CPushButton(m_container);
                    editor->setUserData(ivar->getName());
                    connect(editor, &CPushButton::clicked, this, &IVariableUIHandler::slotRequestStreamOrMeasure);
                    return editor;
                }
            }

            break;
        }
    }

    return Q_NULLPTR;
}

CClickableLabel *IVariableUIHandler::newUnit(IVariable *ivar)
{
    Q_UNUSED(ivar);
    CClickableLabel *label = new CClickableLabel(m_container);
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
    CClickableLabel *label = row.widgetAt<CClickableLabel *>(0);
    QWidget *editor = row.widgetAt<QWidget *>(1);
    CClickableLabel *labelUnit = row.widgetAt<CClickableLabel *>(2);
    CUnit *unit = ivar->getUnit();
    label->setText(getVariableLabel(ivar));
    labelUnit->setText(unit ? unit->getLabel() : QString());

    applyEditorConstraints(editor, ivar);

    // Keep in synch with newEditor
    switch (ivar->getType()) {
    case e_type_alarm:
        qobject_cast<CLedButton *>(editor)->setChecked(!ivar->toBool());
        return;

    case e_type_bool: {
        switch (ivar->getOrganType()) {
        case e_type_organ_none:
        case e_type_organ_output: {
            qobject_cast<CSwitchButton *>(editor)->setChecked(ivar->toBool());
            return;
        }

        case e_type_organ_input: {
            break;
        }
        }

        qobject_cast<CLedButton *>(editor)->setChecked(ivar->toBool());
        return;
    }

    case e_type_float: {
        switch (ivar->getOrganType()) {
        case e_type_organ_none:
        case e_type_organ_output: {
            break;
        }

        case e_type_organ_input: {
            break;
        }
        }

        qobject_cast<CPushButton *>(editor)->setText(ivar->toString());
        return;
    }

    case e_type_int: {
        switch (ivar->getOrganType()) {
        case e_type_organ_none:
        case e_type_organ_output: {
            break;
        }

        case e_type_organ_input: {
            break;
        }
        }

        qobject_cast<CPushButton *>(editor)->setText(ivar->toString());
        return;
    }

    case e_type_string: {
        switch (ivar->getOrganType()) {
        case e_type_organ_none:
        case e_type_organ_output: {
            break;
        }

        case e_type_organ_input: {
            break;
        }
        }

        qobject_cast<CPushButton *>(editor)->setText(ivar->toString());
        return;
    }

    case e_type_stream: {
        switch (ivar->getOrganType()) {
        case e_type_organ_none:
        case e_type_organ_output: {
            break;
        }

        case e_type_organ_input: {
            break;
        }
        }

        qobject_cast<CPushButton *>(editor)->setText(ivar->toString());
        return;
    }

    case e_type_measure: {
        switch (ivar->getOrganType()) {
        case e_type_organ_none:
        case e_type_organ_output: {
            break;
        }

        case e_type_organ_input: {
            break;
        }
        }

        qobject_cast<CPushButton *>(editor)->setText(ivar->toString());
        return;
    }

    case e_type_unknow: {
        switch (ivar->getOrganType()) {
        case e_type_organ_none:
        case e_type_organ_output: {
            break;
        }

        case e_type_organ_input: {
            break;
        }
        }

        qobject_cast<CPushButton *>(editor)->setText(ivar->toString());
        return;
    }

    case e_type_list_variables:
        break;

    case type_mutable: {
        CAutomate *automate = CAutomate::getInstance();
        CVariableMutable *vmutable = static_cast<CVariableMutable *>(ivar);
        CPushButton *button = qobject_cast<CPushButton *>(editor);

        switch (vmutable->mutableType()) {
        case CVariableMutable::Undefined:
            break;

        case CVariableMutable::CycleType: {
            button->setText(ICycle::typeToString(enumTypeCycle(ivar->toInt())));
            break;
        }

        case CVariableMutable::Cycle: {
            ICycle *cycle = automate->getCycle(ivar->toString());
            button->setText(cycle ? cycle->getLabel() : QString());
            break;
        }

        case CVariableMutable::VariableType: {
            button->setText(IVariable::typeToString(enumVariableType(ivar->toInt())));
            break;
        }

        case CVariableMutable::VarOrganType: {
            button->setText(IVariable::organTypeToString(enumVariableOrganType(ivar->toInt())));
            break;
        }

        case CVariableMutable::Unit: {
            CUnit *unit = automate->getUnit(ivar->toString());
            button->setText(unit ? unit->getLabel() : QString());
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

        case CVariableMutable::Variable: {
            IVariable *variable = automate->getVariable(ivar->toString());
            button->setText(variable ? variable->getLabel() : QString());
            break;
        }

        case CVariableMutable::Action: {
            IAction *action = automate->getAction(ivar->toString());
            button->setText(action ? action->getLabel() : QString());
            break;
        }

        case CVariableMutable::ActionType: {
            actionType type = static_cast<actionType>(ivar->toInt());
            button->setText(IAction::typeToString(type));
            break;
        }

        case CVariableMutable::StreamOrMeasure: {
            const QString name = ivar->toString();
            CVariableStream *stream = automate->getStream(name);
            CVariableMeasure *measure = automate->getMeasure(name);
            const QString text = stream ? stream->getLabel() : (measure ? measure->getLabel() : QString());
            button->setText(text);
            break;
        }
        }

        break;
    }
    }
}

QString IVariableUIHandler::getVariableLabel(IVariable *ivar) const
{
    return ivar ? ivar->getLabel() : QString();
}

void IVariableUIHandler::applyEditorConstraints(QWidget *editor, IVariable *ivar)
{
    if (editor) {
        editor->setEnabled(ivar->getAccess() != e_access_read);
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

    if (enterText(value, getVariableLabel(ivar))) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestInteger()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    int value = ivar->toInt();

    if (enterInteger(value, getVariableLabel(ivar))) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestDouble()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    float value = ivar->toFloat();

    if (enterFloat(value, getVariableLabel(ivar))) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestActionType()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    actionType value = static_cast<actionType>(ivar->toInt());

    if (selectActionType(value, getVariableLabel(ivar))) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestVariableType()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    enumVariableType value = enumVariableType(ivar->toInt());

    if (selectVariableType(value, getVariableLabel(ivar))) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestOrganType()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    enumVariableOrganType value = enumVariableOrganType(ivar->toInt());

    if (selectOrganType(value, getVariableLabel(ivar))) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestCycleType()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    enumTypeCycle value = enumTypeCycle(ivar->toInt());

    if (selectCycleType(value, getVariableLabel(ivar))) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestVariable()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    QString value = ivar->toString();

    if (selectVariable(value, getVariableLabel(ivar))) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestStream()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    QString value = ivar->toString();

    if (selectStream(value, getVariableLabel(ivar))) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestMeasure()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    QString value = ivar->toString();

    if (selectMeasure(value, getVariableLabel(ivar))) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestCycle()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    QString value = ivar->toString();

    if (selectCycle(value, getVariableLabel(ivar))) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestAction()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    QString value = ivar->toString();

    if (selectAction(value, getVariableLabel(ivar))) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestStreamOrMeasure()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    QString value = ivar->toString();

    if (selectStreamOrMeasure(value, getVariableLabel(ivar))) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestExtension()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    QString value = ivar->toString();

    if (selectExtension(value, getVariableLabel(ivar))) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestOrgan()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    QString value = ivar->toString();

    if (selectOrgan(value, getVariableLabel(ivar))) {
        ivar->setValue(value);
    }
}

void IVariableUIHandler::slotRequestUnit()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IVariable *ivar = getVariable(editor->userData().toString());
    QString value = ivar->toString();

    if (selectUnit(value, getVariableLabel(ivar))) {
        ivar->setValue(value);
    }
}
