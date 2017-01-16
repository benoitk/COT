#ifndef CMODELCONFIGFILE_H
#define CMODELCONFIGFILE_H

#include <QObject>
#include "qmap.h"


class QByteArray;
class IAction;
class ICycle;
class CScheduler;
class CAutomate;
class CConfigFileHandler : public QObject
{
    Q_OBJECT

public:
    CConfigFileHandler(CAutomate *parent, CScheduler* scheduler);
    ~CConfigFileHandler();

    QString getLabelAnalyser(const QLocale &);
    QList<ICycle*> getListSequencesMesure();
    QMap<QString, ICycle*> getMapCycle();

    int getNumberOfStream() const;
    ICycle* getCycle(int);

    void saveJson(const QVariantMap& arg_mapSerialized);
    bool loadConf();
    bool checkSyntaxeError(const QString & arg_fileName = "");

private:
    QJsonDocument* m_jsonDoc;

    QMap<QString, IAction*> m_mapActions;
    QMap<QString, ICycle*> m_mapCycles;
    //QMap<QString, ICycle*> m_mapSequences;
    QList<ICycle*> m_listSequences;
    CScheduler* m_scheduler;
    CAutomate* m_automate;

};

#endif // CMODELCONFIGFILE_H
