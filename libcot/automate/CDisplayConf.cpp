#include "CDisplayConf.h"
#include "IVariable.h"
#include "CAutomate.h"
#include "qvariant.h"
#include "qjsonarray.h"
#include "qdebug.h"


// JSON names for elec_tests, they are used to retrieve the correct IVariable array in a map.
// the strings are coming from save.json
// see getMapForScreenElectricalTests()
const QString CDisplayConf::strElec420 = QString("tab_EV");
const QString CDisplayConf::strElecRelays = QString("tab_Actionneurs");
const QString CDisplayConf::strElecInputs = QString("tab_entrees");
const QString CDisplayConf::strElecPump = QString("tab_pump");
const QString CDisplayConf::strElecActuator = QString("tab_selecteur");

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
                else qDebug() << "CDisplay Conf diagnostic type_unknow" << mapScreen;

            }
        }else if(mapScreen.contains(QStringLiteral("name")) && mapScreen["name"].toString() == QStringLiteral("options")){
            QVariantList variantList = mapScreen.value(QStringLiteral("variables")).toList();
            foreach(QVariant variant, variantList){
                IVariable* var = CAutomate::getInstance()->getVariable(variant.toString());
                if(var->getType() != type_unknow){
                    addVariableToScreenOptions(var);
                }
                else qDebug() << "CDisplay Conf options type_unknow" << mapScreen;
            }
        }else if(mapScreen.contains(QStringLiteral("name")) && mapScreen["name"].toString() == QStringLiteral("history")){
            QVariantList variantList = mapScreen.value(QStringLiteral("variables")).toList();
            foreach(QVariant variant, variantList){
                IVariable* var = CAutomate::getInstance()->getVariable(variant.toString());
                if(var->getType() != type_unknow){
                    addVariableToScreenHistory(var);
                }
                else qDebug() << "CDisplay Conf history type_unknow" << mapScreen;
            }
        }else if(mapScreen.contains(QStringLiteral("name")) && mapScreen["name"].toString() == QStringLiteral("alarms")){
            QVariantList variantList = mapScreen.value(QStringLiteral("variables")).toList();
            foreach(QVariant variant, variantList){
                IVariable* var = CAutomate::getInstance()->getVariable(variant.toString());
                if(var->getType() != type_unknow){
                    addVariableToScreenAlarms(var);
                }
                else qDebug() << "CDisplay Conf alarms type_unknow" << mapScreen;
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
                    //else qDebug() << "CDisplay Conf elec_tests type_unknow" << mapScreen;
                }
            }
            
        }else{ 
            qDebug() << "display écran inconnu " << mapScreen;
        }		
	}

    qDebug() << "diagnostic" << m_listForScrenDiagnostic;
    qDebug() << "elec_tests" << m_mapForScrenElectricalTests;
    qDebug() << "options" << m_listForScrenOptions;
    qDebug() << "history" << m_listForScrenHistory;
    qDebug() << "alarms" << m_listForScrenAlarms;
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
QList<IVariable*> CDisplayConf::getListForScreenDiagnostic(){
    return m_listForScrenDiagnostic;
}
QMap<QString, QList<IVariable*> > CDisplayConf::getMapForScreenElectricalTests(){
    return m_mapForScrenElectricalTests;
}
QList<IVariable*> CDisplayConf::getListForScreenOptions(){
    return m_listForScrenOptions;
}
QList<IVariable*> CDisplayConf::getListForScreenHistory(){
    return m_listForScrenHistory;
}
QList<IVariable*> CDisplayConf::getListForScreenAlarms(){
    return m_listForScrenAlarms;
}
