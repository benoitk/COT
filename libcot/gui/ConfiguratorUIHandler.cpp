#include "ConfiguratorUIHandler.h"
#include "CGenericItemSelector.h"
#include "CVariableString.h"

namespace {
typedef QPair<QString, QVariant> PairStringString;
typedef QPair<QString, PairStringString> PairPairStringString;
typedef QList<PairPairStringString> PairPairStringStringList;

IVariablePtrList build(const PairPairStringStringList& pairs) {
    IVariablePtrList ivars;

    foreach (const PairPairStringString& pair, pairs) {
        IVariable *ivar = new CVariableString;
        ivar->setName(pair.first);
        ivar->setLabel(pair.second.first);
        ivar->setValue(pair.second.second);
        ivars << ivar;
    }

    return ivars;
}

void free(IVariablePtrList& ivars) {
    qDeleteAll(ivars);
    ivars.clear();
}
}

ConfiguratorUIHandler::ConfiguratorUIHandler(QObject *parent)
    : QObject(parent)
{
}

int ConfiguratorUIHandler::selectActionType(int defaultValue)
{
    // KDAB_TODO: No customer api so let fake
    IVariablePtrList ivars = build({
                                       {"calc_coef", qMakePair(tr("Calc Coef"), 1)},
                                       {"calc_rien", qMakePair(tr("Calc Rien"), 2)},
                                       {"bloc", qMakePair(tr("Bloc"), 1000)}
                                   });
    CGenericItemSelector dlg(ivars);
    dlg.setSelectedValue(defaultValue);
    int r = -1;

    if (dlg.exec()) {
        r = dlg.selectedItem()->toInt();
    }

    free(ivars);
    return r;
}

variableType ConfiguratorUIHandler::selectVariableType(int defaultValue)
{
    IVariablePtrList ivars = build({
                                      {"type_bool", qMakePair(tr("Boolean"), 0)},
                                      {"type_float", qMakePair(tr("Float"), 1)},
                                      {"type_int", qMakePair(tr("Integer"), 2)},
                                      {"type_string", qMakePair(tr("String"), 3)},
                                      {"type_stream", qMakePair(tr("Stream"), 4)},
                                      {"type_unknow", qMakePair(tr("Unknown"), 5)}
                                  });
    CGenericItemSelector dlg(ivars);
    dlg.setSelectedValue(defaultValue);
    variableType r = type_unknow;

    if (dlg.exec()) {
        r = variableType(dlg.selectedItem()->toInt());
    }

    free(ivars);
    return r;
}

VariableOrganType ConfiguratorUIHandler::selectOrganType(int defaultValue)
{

}

int ConfiguratorUIHandler::selectCycleType(int defaultValue)
{

}

QString ConfiguratorUIHandler::selectVariable(const QString &defaultValue)
{

}

QString ConfiguratorUIHandler::selectStream(const QString &defaultValue)
{

}

QString ConfiguratorUIHandler::selectMeasure(const QString &defaultValue)
{

}

QString ConfiguratorUIHandler::selectCycle(const QString &defaultValue)
{

}

QString ConfiguratorUIHandler::selectAction(const QString &defaultValue)
{

}

QString ConfiguratorUIHandler::selectStreamOrMeasure(const QString &defaultValue)
{

}

QString ConfiguratorUIHandler::selectExtension(const QString &defaultValue)
{

}

QString ConfiguratorUIHandler::selectOrgan(const QString &defaultValue)
{

}

QString ConfiguratorUIHandler::enterText(const QString &defaultValue)
{

}

int ConfiguratorUIHandler::enterInteger(int defaultValue)
{

}

double ConfiguratorUIHandler::enterDouble(double defaultValue)
{

}
