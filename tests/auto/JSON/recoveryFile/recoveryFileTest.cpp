#include <qtest.h>
#include <qtestmouse.h>
#include <QSignalSpy>
#include <QObject>
#include <QFileInfo>

#include "CConfigurationBackup.h"

/**
 * @brief automated test to see if the backup/restore of the JSON file works correctly.
 * CConfigurationBackup is tested here.
 */

static const QString SAVE_FILE("save.json");
static const QString RECOVERY_FILE("save-recovery.json");

class recoveryFileTest : public QObject
{
    Q_OBJECT
private:
    QString jsonFilePath() const;
private slots:
    void initTestCase();
    void testRecovery();

private:
    QByteArray fileContents(const QString &fileName);
};

QString recoveryFileTest::jsonFilePath() const
{
    QFileInfo file(QStringLiteral(COT_JSON_FILE_PATH));
    QString path = file.absolutePath();
    path += QLatin1Char('/') + SAVE_FILE;
    return path;
}

void recoveryFileTest::initTestCase()
{
    // check that we have the JSon file available and ready to read
    QVERIFY(!QStringLiteral(COT_JSON_FILE_PATH).isEmpty());

    // put save.json in the current directory for the tests.
    QByteArray exampleJSONContents = fileContents(QStringLiteral(COT_JSON_FILE_PATH));
    QFile jsonExampleFile(jsonFilePath());
    QVERIFY(jsonExampleFile.exists());
    QVERIFY(jsonExampleFile.open(QIODevice::ReadWrite | QIODevice::Text));
    QCOMPARE(jsonExampleFile.write(exampleJSONContents), exampleJSONContents.length());
}

void recoveryFileTest::testRecovery()
{
    QByteArray exampleJSONContents = fileContents(jsonFilePath());
    QVERIFY(!exampleJSONContents.isEmpty());

    // * create save-recovery.json
    // * Create a backup of save.json with timestamp
    // * Overwtire save.json with contents from save-recovery.json
    CConfigurationBackup backup;
    QString backupFileName;
    QVERIFY(backup.createRecoveryFile(exampleJSONContents));
    QVERIFY(backup.overwriteConfigurationFile(&backupFileName));

    // let's see if the files are here and populated with the expected data
    QByteArray saveFileContents = fileContents(jsonFilePath());
    QVERIFY(!saveFileContents.isEmpty());
    QByteArray recoveryFileContents = fileContents(RECOVERY_FILE);
    QVERIFY(!recoveryFileContents.isEmpty());
    QByteArray backupFileContents = fileContents(backupFileName);
    QVERIFY(!backupFileContents.isEmpty());

    QCOMPARE(saveFileContents, recoveryFileContents);
    QCOMPARE(saveFileContents, backupFileContents);
    QCOMPARE(recoveryFileContents, backupFileContents);


    // test updating the contents of the save.json file
    QByteArray updatedContents(QString("this would be the new contents").toLatin1());
    QVERIFY(backup.writeToConfigurationFile(updatedContents));
    saveFileContents = fileContents(jsonFilePath());
    QVERIFY(!saveFileContents.isEmpty());
    QCOMPARE(saveFileContents, updatedContents);

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
