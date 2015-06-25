#include "CDisplayConf.h"
#include "IVariable.h"
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
                if(var->getType() != type_unknow){
                    addVariableToScreenDiagnostic(var);
                }
                else qCDebug(COTAUTOMATE_LOG) << "CDisplay Conf diagnostic type_unknow" << mapScreen;

            }
        }else if(mapScreen.contains(QStringLiteral("name")) && mapScreen["name"].toString() == QStringLiteral("options")){
            QVariantList variantList = mapScreen.value(QStringLiteral("variables")).toList();
            foreach(QVariant variant, variantList){
                IVariable* var = CAutomate::getInstance()->getVariable(variant.toString());
                if(var->getType() != type_unknow){
                    addVariableToScreenOptions(var);
                }
                else qCDebug(COTAUTOMATE_LOG) << "CDisplay Conf options type_unknow" << mapScreen;
            }
        }else if(mapScreen.contains(QStringLiteral("name")) && mapScreen["name"].toString() == QStringLiteral("history")){
            QVariantList variantList = mapScreen.value(QStringLiteral("variables")).toList();
            foreach(QVariant variant, variantList){
                IVariable* var = CAutomate::getInstance()->getVariable(variant.toString());
                if(var->getType() != type_unknow){
                    addVariableToScreenHistory(var);
                }
                else qCDebug(COTAUTOMATE_LOG) << "CDisplay Conf history type_unknow" << mapScreen;
            }
        }else if(mapScreen.contains(QStringLiteral("name")) && mapScreen["name"].toString() == QStringLiteral("alarms")){
            QVariantList variantList = mapScreen.value(QStringLiteral("variables")).toList();
            foreach(QVariant variant, variantList){
                IVariable* var = CAutomate::getInstance()->getVariable(variant.toString());
                if(var->getType() != type_unknow){
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
