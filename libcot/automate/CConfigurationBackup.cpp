#include "CConfigurationBackup.h"

#include <QDir>
#include <QDateTime>

namespace {
static const QString recoveryFileName = QStringLiteral("save-recovery.json");
static const QString saveFileName = QStringLiteral("save.json");
static const QDir jsonDirectory(QStringLiteral("./"));
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
    QFile file(jsonRecoveryFile());

    if (file.exists()) {
        file.remove();
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    qint64 writtenBytes = file.write(contents);
    const bool correctAmountOfBytesWritten = writtenBytes == contents.size();

    return correctAmountOfBytesWritten;
}

bool CConfigurationBackup::overwriteConfigurationFile()
{
    QFile recoveryFile(jsonRecoveryFile());
    QFile saveFile(jsonSaveFile());

    if (!saveFile.exists() || !recoveryFile.exists()) {
        return false;
    }

    // make a backup of save.json
    QString backupFileName(QDateTime::currentDateTime().toString("dd:MM:yyyy:hh:mm:ss-") + saveFileName);
    if (QFile::exists(backupFileName)) {
        return false;
    }

    if (!saveFile.copy(backupFileName)) {
        return false;
    }

    // copy recovery-save.json into save.json
    if (!saveFile.remove()) {
        return false;
    }
    else if (!recoveryFile.copy(saveFile.fileName())) {
        return false;
    }

    return true;
}

