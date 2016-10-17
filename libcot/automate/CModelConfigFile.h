#ifndef CMODELCONFIGFILE_H
#define CMODELCONFIGFILE_H

#include <QObject>
#include "qmap.h"


class QByteArray;
class IAction;
class ICycle;
class CScheduler;
class CModelConfigFile : public QObject
{
    Q_OBJECT

public:
    CModelConfigFile(QObject *parent, CScheduler* scheduler);
    ~CModelConfigFile();

    QString getLabelAnalyser(const QLocale &);
    QList<ICycle*> getListSequencesMesure();
    QMap<QString, ICycle*> getMapCycle();

    int getNumberOfStream() const;
    ICycle* getCycle(int);

    void saveJson(const QVariantMap& arg_mapSerialized);

private:
    QJsonDocument* m_jsonDoc;

    QMap<QString, IAction*> m_mapActions;
    QMap<QString, ICycle*> m_mapCycles;
    //QMap<QString, ICycle*> m_mapSequences;
    QList<ICycle*> m_listSequences;
    CScheduler* m_scheduler;

};

#endif // CMODELCONFIGFILE_H
