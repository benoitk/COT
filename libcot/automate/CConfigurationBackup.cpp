#include "CConfigurationBackup.h"

#include <QDir>
#include <QDateTime>

namespace {
static const QString recoveryFileName = QStringLiteral("save-recovery.json");
static const QString saveFileName = QStringLiteral("save.json");
static const QDir jsonDirectory(QStringLiteral("./")); // KDAB_TODO: Use correct path once it have been choosen.

}

CConfigurationBackup::CConfigurationBackup(QObject *parent)
    : QObject(parent)
{}

QString CConfigurationBackup::jsonRecoveryFile() const
{
    return jsonDirectory.absolutePath() + '/' + recoveryFileName;
}

QString CConfigurationBackup::jsonSaveFile() const
{
    return jsonDirectory.absolutePath() + '/' + saveFileName;
}

bool CConfigurationBackup::createRecoveryFile(const QByteArray &contents)
{
    // remove the file if it exists
    if (QFile::exists(jsonRecoveryFile()) && !QFile::remove(jsonRecoveryFile())) {
        return false;
    }

    return createFile(jsonRecoveryFile(), contents);
}

bool CConfigurationBackup::overwriteConfigurationFile(QString *generatedBackupFileName)
{
    QFile recoveryFile(jsonRecoveryFile());
    QFile saveFile(jsonSaveFile());

    if (!saveFile.exists() || !recoveryFile.exists()) {
        return false;
    }

    // make a backup of save.json
    QString backupFileName(QDateTime::currentDateTime().toString("dd:MM:yyyy:hh:mm:ss-") + saveFileName);

    if (generatedBackupFileName != Q_NULLPTR) {
        *generatedBackupFileName = backupFileName;
    }


    if (QFile::exists(backupFileName)) {
        return false;
    }

    if (!saveFile.copy(backupFileName)) {
        return false;
    }

    // copy recovery-save.json into save.json
    if (!recoveryFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    writeToConfigurationFile(recoveryFile.readAll());
    return true;
}

bool CConfigurationBackup::writeToConfigurationFile(const QByteArray &newContents)
{
    if (newContents.isEmpty()) {
        return false;
    }

    // remove save,json and create a new one
    if (!QFile::remove(jsonSaveFile())) {
        return false;
    }

    return createFile(jsonSaveFile(), newContents);

}

bool CConfigurationBackup::createFile(const QString &fileName, const QByteArray &contents)
{
    QFile file(fileName);

    if (file.exists()) {
        return false;
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    qint64 writtenBytes = file.write(contents);
    const bool correctAmountOfBytesWritten = writtenBytes == contents.size();

    return correctAmountOfBytesWritten && file.flush();
}

