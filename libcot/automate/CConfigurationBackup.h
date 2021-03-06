#ifndef CCONFIGURATIONBACKUP_H
#define CCONFIGURATIONBACKUP_H

#include <QObject>
#include <QFile>

#include "cot_global.h"

/**
 * @brief The CConfigurationBackup class is used to backup/restore data from the automaton
 * It takes a QByteArray from the automaton to write a JSon recovery file (save-recovery.json),
 * and is able to overwrite the regular JSon file (save.json) with the contents of the recovery file.
 */

class LIBCOT_EXPORT CConfigurationBackup : public QObject
{
    Q_OBJECT

public:
    explicit CConfigurationBackup(QObject *parent = Q_NULLPTR);

    /// file accessors for external use.
    QString jsonRecoveryFile() const;
    QString jsonSaveFile() const;

    /**
     * @brief Creates a save-recovery.json file with the contents of current save file.
     * @return empty string if the file was successfully created, error message otherwise
     * @warning if the file already exists, it is deleted.
     */
    QString createRecoveryFile();

    /**
     * @brief Overwrite save.json with save-recovery.json
     * @return empty string if the file was successfully overwritten, or an error message otherwise.
     * @param generatedBackupFileName, a way to get the generated backup file.
     */
    QString overwriteConfigurationFile(QString *generatedBackupFileName = Q_NULLPTR);

    void setJsonDirectory(const QString &directory);
    QString jsonDirectory() const;


public slots:
    /**
     * @brief rewriteConfigurationFile writes the passed QByteArray into save.json.
     * @return empty string if the file was successfully written (Also checks the integrity of newContents to some extend)
     *         or an error message otherwise.
     */
    QString writeToConfigurationFile(const QByteArray &newContents);

private:

    /**
     * @brief Creates a file  with the name "filename" and the contents "contents"
     * @return empty string if no error occurred, or an error message otherwise.
     */
    QString createFile(const QString &fileName, const QByteArray &contents);

    QString m_jsonDirectory;



};

#endif // CCONFIGURATIONBACKUP_H
