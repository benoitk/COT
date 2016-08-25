#include "CConfigurationBackup.h"

#include <QDir>
#include <QDateTime>
#include <QJsonDocument>
#include <QDebug>

namespace {
static const QString RECOVERY_FILE_NAME = QStringLiteral("save-recovery.json");
static const QString SAVE_FILE_NAME = QStringLiteral("save.json");
}

CConfigurationBackup::CConfigurationBackup(QObject *parent)
    : QObject(parent),
      m_jsonDirectory(JSON_DIRECTORY)
{}

QString CConfigurationBackup::jsonRecoveryFile() const
{
    QString path(m_jsonDirectory);
    path += QLatin1Char('/') + RECOVERY_FILE_NAME;
    return path;
}

QString CConfigurationBackup::jsonSaveFile() const
{
    QString path(m_jsonDirectory);
    path += QLatin1Char('/') + SAVE_FILE_NAME;
    return path;
}

QString CConfigurationBackup::createRecoveryFile()
{
    // remove the file if it exists
    if (QFile::exists(jsonRecoveryFile()) && !QFile::remove(jsonRecoveryFile())) {
        return tr("Could not remove existing recovery file %1.").arg(jsonRecoveryFile());
    }

    QFile saveFile(jsonSaveFile());
    if (!saveFile.exists() || !saveFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return tr("Could not open json save file %1 for reading.").arg(jsonSaveFile());
    }
    return createFile(jsonRecoveryFile(), saveFile.readAll());
}

QString CConfigurationBackup::overwriteConfigurationFile(QString *generatedBackupFileName){
    QFile recoveryFile(jsonRecoveryFile());
    QFile saveFile(jsonSaveFile());

    if (!saveFile.exists()) {
        return tr("Save file %1 does not exist.").arg(SAVE_FILE_NAME);
    } else if (!recoveryFile.exists()) {
        return tr("Recovery file %1 does not exist.").arg(RECOVERY_FILE_NAME);
    }

    // make a backup of save.json
    QString backupFileName(QDateTime::currentDateTime().toString("dd:MM:yyyy:hh:mm:ss-") + SAVE_FILE_NAME);

    if (generatedBackupFileName != Q_NULLPTR) {
        *generatedBackupFileName = backupFileName;
    }


    if (QFile::exists(backupFileName)) {
        return tr("Backup file %1 exists already.").arg(backupFileName);
    }

    if (!saveFile.copy(backupFileName)) {
        return tr("Could not create backup file %1.").arg(backupFileName);
    }

    // copy recovery-save.json into save.json
    if (!recoveryFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return tr("Failed to read recovery file %1.").arg(jsonRecoveryFile());
    }

    return writeToConfigurationFile(recoveryFile.readAll());
}

void CConfigurationBackup::setJsonDirectory(const QString &directory){
    if (!directory.isEmpty()) {
        m_jsonDirectory = directory;
    }
}

QString CConfigurationBackup::jsonDirectory() const{
    return m_jsonDirectory;
}

QString CConfigurationBackup::writeToConfigurationFile(const QByteArray &newContents){
    if (newContents.isEmpty()) {
        return tr("Cannot override configuration file with empty data.");
    }
    QJsonParseError error;
    QJsonDocument::fromJson(newContents, &error);
    if (error.error != QJsonParseError::NoError) {
        return tr("JSON data is invalid: %1").arg(error.errorString());
    }

    // remove save,json and create a new one
    if (!QFile::remove(jsonSaveFile())) {
        return tr("Could not remove configuration file %1").arg(jsonSaveFile());
    }

    return createFile(jsonSaveFile(), newContents);

}

QString CConfigurationBackup::createFile(const QString &fileName, const QByteArray &contents)
{
    qDebug() << "CConfigurationBackup::createFile " << fileName;
    QFile file(fileName);

    if (file.exists()) {
        return tr("Not creating file %1, it exists already.").arg(fileName);
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return tr("Could not open file %1 for writing.").arg(fileName);

    qint64 writtenBytes = file.write(contents);
    const bool correctAmountOfBytesWritten = writtenBytes == contents.size();

    if (!correctAmountOfBytesWritten || !file.flush()) {
        return tr("Failed to write data into file %1.").arg(fileName);
    }
    return QString();
}

