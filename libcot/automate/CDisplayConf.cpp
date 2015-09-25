#include "CDisplayConf.h"
#include "IVariable.h"
#include "IAction.h"
#include "CAutomate.h"
#include "qvariant.h"
#include "qjsonarray.h"
#include "cotautomate_debug.h"
#include "cotautomate_debug.h"

// JSON names for elec_tests, they are used to retrieve the correct IVariable array in a map.
// the strings are coming from save.json
// see getMapForScreenElectricalTests()
const QString CDisplayConf::STR_ELEC_420 = QString("tab_selecteur");
const QString CDisplayConf::STR_ELEC_RELAYS = QString("tab_Actionneurs"); //TODO A remettre d'aplomb (actionneur inversé avec ev je sais pas ou)
const QString CDisplayConf::STR_ELEC_INPUTS = QString("tab_entrees");
const QString CDisplayConf::STR_ELEC_PUMP = QString("tab_pump");
const QString CDisplayConf::STR_ELEC_ACTUATOR = QString("tab_EV");

CDisplayConf::CDisplayConf(const QJsonArray& jsonArray, QObject *parent)
    : QObject(parent)
{
    foreach(QJsonValue jsonConteneur, jsonArray){
        QVariantMap mapScreen = jsonConteneur.toVariant().toMap();
        if(mapScreen.contains(QStringLiteral("name")) && mapScreen["name"].toString() == QStringLiteral("diagnostic")){
            QVariantList variantList = mapScreen.value(QStringLiteral("variables")).toList();
            foreach(QVariant variant, variantList){
                IVariable* var = CAutomate::getInstance()->getVariable(variant.toString());
                if(var->getType() != e_type_unknow){
                    addVariableToScreenDiagnostic(var);
                }
                else qCDebug(COTAUTOMATE_LOG) << "CDisplay Conf diagnostic type_unknow" << mapScreen;

            }
        }else if(mapScreen.contains(QStringLiteral("name")) && mapScreen["name"].toString() == QStringLiteral("options")){
            QVariantList variantList = mapScreen.value(QStringLiteral("variables")).toList();
            foreach(QVariant variant, variantList){
                IVariable* var = CAutomate::getInstance()->getVariable(variant.toString());
                if(var->getType() != e_type_unknow){
                    addVariableToScreenOptions(var);
                }
                else qCDebug(COTAUTOMATE_LOG) << "CDisplay Conf options type_unknow" << mapScreen;
            }
        }else if(mapScreen.contains(QStringLiteral("name")) && mapScreen["name"].toString() == QStringLiteral("history")){
            QVariantList variantList = mapScreen.value(QStringLiteral("variables")).toList();
            foreach(QVariant variant, variantList){
                IVariable* var = CAutomate::getInstance()->getVariable(variant.toString());
                if(var->getType() != e_type_unknow){
                    addVariableToScreenHistory(var);
                }
                else qCDebug(COTAUTOMATE_LOG) << "CDisplay Conf history type_unknow" << mapScreen;
            }
        }else if(mapScreen.contains(QStringLiteral("name")) && mapScreen["name"].toString() == QStringLiteral("alarms")){
            QVariantList variantList = mapScreen.value(QStringLiteral("variables")).toList();
            foreach(QVariant variant, variantList){
                IVariable* var = CAutomate::getInstance()->getVariable(variant.toString());
                if(var->getType() != e_type_unknow){
                    addVariableToScreenAlarms(var);
                }
                else qCDebug(COTAUTOMATE_LOG) << "CDisplay Conf alarms type_unknow" << mapScreen;
            }
        }else if(mapScreen.contains(QStringLiteral("name")) && mapScreen["name"].toString() == QStringLiteral("elec_tests")){
            QVariantList variantMapTabs = mapScreen.value(QStringLiteral("map_tabs")).toList();
            foreach(QVariant variant, variantMapTabs){
                QVariantMap map = variant.toMap();
                QVariantList variantList = map.value(QStringLiteral("variables")).toList();
                addTabToScreenElectricalTest(map.value(QStringLiteral("name")).toString());
                foreach(QVariant variant, variantList){
                    IVariable* var = CAutomate::getInstance()->getVariable(variant.toString());
                    //if(var->getType() != type_unknow){
                        addVariableToScreenElectricalTest(map.value(QStringLiteral("name")).toString(), var);
                    //}
                    //else qCDebug(COTAUTOMATE_LOG) << "CDisplay Conf elec_tests type_unknow" << mapScreen;
                }
            }
        }else if(mapScreen.contains(QStringLiteral("name")) && mapScreen["name"].toString() == QStringLiteral("initial_tests")){
            QVariantList variantListActions = mapScreen.value(QStringLiteral("actions")).toList();
            foreach(QVariant variant, variantListActions){
                IAction* action = CAutomate::getInstance()->getAction(variant.toString());
                addInitialTestsAction(action);
                //if(var->getType() != type_unknow){
      //          add
                //}
                //else qCDebug(COTAUTOMATE_LOG) << "CDisplay Conf elec_tests type_unknow" << mapScreen;
            }
            QVariantList variantListVariables = mapScreen.value(QStringLiteral("variables")).toList();
            foreach(QVariant variant, variantListVariables){
                QVariantMap map = variant.toMap();
                IVariable* varTest = CAutomate::getInstance()->getVariable(map.value(QStringLiteral("test")).toString());
                IVariable* varIndicator = CAutomate::getInstance()->getVariable(map.value(QStringLiteral("indicator")).toString());
                //if(var->getType() != type_unknow){
                addInitialTestsVariableTest(varTest);
                addInitialTestsVariableIndicator(varIndicator);
                //}
                //else qCDebug(COTAUTOMATE_LOG) << "CDisplay Conf elec_tests type_unknow" << mapScreen;
            }
        }else{
            qCDebug(COTAUTOMATE_LOG) << "display écran inconnu " << mapScreen;
        }
    }

//    qCDebug(COTAUTOMATE_LOG) << "diagnostic" << m_listForScrenDiagnostic;
//    qCDebug(COTAUTOMATE_LOG) << "elec_tests" << m_mapForScrenElectricalTests;
//    qCDebug(COTAUTOMATE_LOG) << "options" << m_listForScrenOptions;
//    qCDebug(COTAUTOMATE_LOG) << "history" << m_listForScrenHistory;
//    qCDebug(COTAUTOMATE_LOG) << "alarms" << m_listForScrenAlarms;
}

CDisplayConf::~CDisplayConf()
{

}
void CDisplayConf::addVariableToScreenDiagnostic(IVariable* var){
    m_listForScrenDiagnostic.append(var);
}
void CDisplayConf::addVariableToScreenElectricalTest(const QString& tab, IVariable* var){
    if(m_mapForScrenElectricalTests.contains(tab)){
        m_mapForScrenElectricalTests[tab].append(var);
    }
}
void CDisplayConf::addTabToScreenElectricalTest(const QString& tab){
    QList<IVariable*> list;
    m_mapForScrenElectricalTests.insert(tab, list);
}
void CDisplayConf::addVariableToScreenOptions(IVariable* var){
    m_listForScrenOptions.append(var);
}
void CDisplayConf::addVariableToScreenHistory(IVariable* var){
    m_listForScrenHistory.append(var);
}
void CDisplayConf::addVariableToScreenAlarms(IVariable* var){
    m_listForScrenAlarms.append(var);
}

void CDisplayConf::delVariableToScreenDiagnostic(IVariable* var){
    int i=0;
    foreach(IVariable* varList, m_listForScrenDiagnostic){
        if(varList == var){ //comparaison des pointeurs
            if(i < m_listForScrenDiagnostic.count())
                m_listForScrenDiagnostic.removeAt(i);
        }
        i++;
    }

}
void CDisplayConf::delVariableToScreenElectricalTest(const QString& tab, IVariable* var){
    if(m_mapForScrenElectricalTests.contains(tab)){
        int i=0;
        QList<IVariable*> list = m_mapForScrenElectricalTests[tab];
        foreach(IVariable* varList, list){
            if(varList == var){ //comparaison des pointeurs
                if(i < list.count())
                    list.removeAt(i);
            }
            i++;
        }
    }
}
void CDisplayConf::delTabToScreenElectricalTest(const QString& tab){
    m_mapForScrenElectricalTests.remove(tab);
}
void CDisplayConf::delVariableToScreenOptions(IVariable* var){
    int i=0;
    foreach(IVariable* varList, m_listForScrenOptions){
        if(varList == var){ //comparaison des pointeurs
            if(i < m_listForScrenOptions.count())
                m_listForScrenOptions.removeAt(i);
        }
        i++;
    }
}
void CDisplayConf::delVariableToScreenHistory(IVariable* var){
    int i=0;
    foreach(IVariable* varList, m_listForScrenHistory){
        if(varList == var){ //comparaison des pointeurs
            if(i < m_listForScrenHistory.count())
                m_listForScrenHistory.removeAt(i);
        }
        i++;
    }
}
void CDisplayConf::delVariableToScreenAlarms(IVariable* var){
    int i=0;
    foreach(IVariable* varList, m_listForScrenAlarms){
        if(varList == var){ //comparaison des pointeurs
            if(i < m_listForScrenAlarms.count())
                m_listForScrenAlarms.removeAt(i);
        }
        i++;
    }
}
QList<IVariable*> CDisplayConf::getListForScreenDiagnostic() const{
    return m_listForScrenDiagnostic;
}
QMap<QString, QList<IVariable*> > CDisplayConf::getMapForScreenElectricalTests() const{
    return m_mapForScrenElectricalTests;
}
QList<IVariable*> CDisplayConf::getListForScreenOptions() const{
    return m_listForScrenOptions;
}
QList<IVariable*> CDisplayConf::getListForScreenHistory() const{
    return m_listForScrenHistory;
}
QList<IVariable*> CDisplayConf::getListForScreenAlarms() const{
    return m_listForScrenAlarms;
}
void CDisplayConf::addInitialTestsAction(IAction* arg){
    if(arg) m_listInitialTestActions.append(arg);
}

void CDisplayConf::addInitialTestsVariableTest(IVariable* arg){
    if(arg) m_listInitialTestVariablesTest.append(arg);
}

void CDisplayConf::addInitialTestsVariableIndicator(IVariable* arg){
    if(arg) m_listInitialTestVariablesIndicator.append(arg);
}

QList<IAction *> CDisplayConf::getListInitialsTestActions(){
    return m_listInitialTestActions;
}

QList<IVariable *> CDisplayConf::getListInitialsTestVariablesTest(){
    return m_listInitialTestVariablesTest;
}

QList<IVariable *> CDisplayConf::getListInitialsTestVariablesIndicator(){
    return m_listInitialTestVariablesIndicator;
}

QVariantList CDisplayConf::serialize(){
    QVariantList listSerialize;
    //diagnostic
    {
        QVariantMap mapDiag;
        mapDiag.insert(QStringLiteral("name"), QStringLiteral("diagnostic"));
        QVariantList listVar;
        foreach(IVariable* var, m_listForScrenDiagnostic){
            listVar.append(var->getName());
        }
        mapDiag.insert(QStringLiteral("variables"), listVar);
        listSerialize.append(mapDiag);
    }

    //tests elec
    {
        QVariantMap mapTestsElec;
        mapTestsElec.insert(QStringLiteral("name"), QStringLiteral("elec_tests"));
        QVariantList listTabs;
        QMap<QString, QList<IVariable*> >::iterator it;
        for(it=m_mapForScrenElectricalTests.begin(); it != m_mapForScrenElectricalTests.end(); ++it){
            QVariantList listVar;
            foreach(IVariable* var, it.value()){
                listVar.append(var->getName());
            }
            QVariantMap mapTab;
            mapTab.insert(QStringLiteral("name"), it.key());
            mapTab.insert(QStringLiteral("variables"), listVar);
            listTabs.append(mapTab);
        }
        mapTestsElec.insert(QStringLiteral("map_tabs"), listTabs);
        listSerialize.append(mapTestsElec);
    }
    //options
    {
        QVariantMap mapOption;
        mapOption.insert(QStringLiteral("name"), QStringLiteral("options"));
        QVariantList listVar;
        foreach(IVariable* var, m_listForScrenOptions){
            listVar.append(var->getName());
        }
        mapOption.insert(QStringLiteral("variables"), listVar);
        listSerialize.append(mapOption);
    }
    //History
    {
        QVariantMap mapHistory;
        mapHistory.insert(QStringLiteral("name"), QStringLiteral("history"));
        QVariantList listVar;
        foreach(IVariable* var, m_listForScrenHistory){
            listVar.append(var->getName());
        }
        mapHistory.insert(QStringLiteral("variables"), listVar);
        listSerialize.append(mapHistory);
    }
    //alarms
    {
        QVariantMap mapAlarms;
        mapAlarms.insert(QStringLiteral("name"), QStringLiteral("alarms"));
        QVariantList listVar;
        foreach(IVariable* var, m_listForScrenAlarms){
            listVar.append(var->getName());
        }
        mapAlarms.insert(QStringLiteral("variables"), listVar);
        listSerialize.append(mapAlarms);
    }

    //initial_tests
    {
        QVariantMap mapTestInitial;
        mapTestInitial.insert(QStringLiteral("name"), QStringLiteral("initial_tests"));
        QVariantList listMap;
        for(int i=0; i<m_listInitialTestVariablesIndicator.count() && i<m_listInitialTestVariablesTest.count(); ++i){
            QVariantMap map;
            map.insert(QStringLiteral("test"), m_listInitialTestVariablesTest.at(i)->getName());
            map.insert(QStringLiteral("indicator"), m_listInitialTestVariablesIndicator.at(i)->getName());
            listMap.append(map);
        }
        mapTestInitial.insert(QStringLiteral("variables"), listMap);
        listSerialize.append(mapTestInitial);
    }

    return listSerialize;
}
