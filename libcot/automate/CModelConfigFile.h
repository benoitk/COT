#ifndef CMODELCONFIGFILE_H
#define CMODELCONFIGFILE_H

#include <QObject>
#include "qmap.h"


class QByteArray;
class IAction;
class ICycle;
class CModelConfigFile : public QObject
{
    Q_OBJECT

public:
    CModelConfigFile(QObject *parent);
    ~CModelConfigFile();

    QString getLblAnalyser(const QLocale &);
    QList<ICycle*> getListSequencesMesure();
    QMap<QString, ICycle*> getMapCycle();
    
    int getNumberOfStream() const;
    ICycle* getCycle(int);

private:
    QJsonDocument* m_jsonDoc;

    QMap<QString, IAction*> m_mapActions; 
    QMap<QString, ICycle*> m_mapCycles; 
    //QMap<QString, ICycle*> m_mapSequences; 
    QList<ICycle*> m_listSequences; 

};

#endif // CMODELCONFIGFILE_H
