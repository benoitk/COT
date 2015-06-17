#include <qtest.h>
#include <qtestmouse.h>
#include <QSignalSpy>
#include <QObject>
#include <QDir>

#include "CConfigurationBackup.h"

/**
 * @brief automated test to see if the backup/restore of the JSON file works correctly.
 * CConfigurationBackup is tested here.
 */

static const QString SAVE_FILE("save.json");
static const QString RECOVERY_FILE("save-recovery.json");
static const QString TEST_DIR(QDir::currentPath());

class recoveryFileTest : public QObject
{
    Q_OBJECT
private:
    QString jsonFilePath() const;
    QString recoveryFilePath() const;
    QByteArray fileContents(const QString &fileName);

private slots:
    void initTestCase();
    void testRecovery();
};

QString recoveryFileTest::jsonFilePath() const
{
    return TEST_DIR + '/' + SAVE_FILE;
}

QString recoveryFileTest::recoveryFilePath() const
{
    return TEST_DIR + '/' + RECOVERY_FILE;
}


void recoveryFileTest::initTestCase()
{
    const QString filePath = JSON_DIRECTORY "/save.json";
    // check that we have the JSon file available and ready to read
    QVERIFY(QFile::exists(filePath));

    // put save.json in the current directory for the tests.
    QFile jsonExampleFile(filePath);
    if (QFile::exists(jsonFilePath())) {
        QFile::remove(jsonFilePath());
    }
    QVERIFY(jsonExampleFile.copy(jsonFilePath()));
    QCOMPARE(fileContents(filePath), fileContents(jsonFilePath()));
}

void recoveryFileTest::testRecovery()
{
    // * create save-recovery.json
    // * Create a backup of save.json with timestamp
    // * Overwtire save.json with contents from save-recovery.json
    CConfigurationBackup backup;
    backup.setJsonDirectory(TEST_DIR);
    QString backupFileName;
    QVERIFY(backup.createRecoveryFile().isEmpty());
    QVERIFY(backup.overwriteConfigurationFile(&backupFileName).isEmpty());

    // let's see if the files are here and populated with the expected data
    QByteArray saveFileContents = fileContents(jsonFilePath());
    QVERIFY(!saveFileContents.isEmpty());
    QByteArray recoveryFileContents = fileContents(recoveryFilePath());
    QVERIFY(!recoveryFileContents.isEmpty());
    QByteArray backupFileContents = fileContents(backupFileName);
    QVERIFY(!backupFileContents.isEmpty());

    QCOMPARE(saveFileContents, recoveryFileContents);
    QCOMPARE(saveFileContents, backupFileContents);
    QCOMPARE(recoveryFileContents, backupFileContents);

    // test updating the contents of the save.json file
    QVERIFY(!backup.writeToConfigurationFile("this is invalid json").isEmpty());
    QCOMPARE(saveFileContents, fileContents(jsonFilePath()));
    QByteArray updatedContents("{\"answer\":42}\n");
    QVERIFY(backup.writeToConfigurationFile(updatedContents).isEmpty());
    saveFileContents = fileContents(jsonFilePath());
    QVERIFY(!saveFileContents.isEmpty());
    QCOMPARE(saveFileContents, updatedContents);

    //remove files
    QFile saveFile(jsonFilePath());
    QVERIFY(saveFile.remove());
    QFile recoveryFile(recoveryFilePath());
    QVERIFY(recoveryFile.remove());
    QFile backupFile(backupFileName);
    QVERIFY(backupFile.remove());
}

QByteArray recoveryFileTest::fileContents(const QString &fileName)
{   
    QFile file(fileName);
    if (!file.exists()) {
        return QByteArray();
    } else if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QByteArray();
    }


    QByteArray contents;
    while (!file.atEnd()) {
        contents.append(file.readLine());
    }
    return contents;
}


QTEST_MAIN(recoveryFileTest)

#include "recoveryFileTest.moc"
