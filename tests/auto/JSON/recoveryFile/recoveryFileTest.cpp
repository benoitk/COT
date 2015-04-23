#include <qtest.h>
#include <qtestmouse.h>
#include <QSignalSpy>
#include <QObject>

#include "CConfigurationBackup.h"

/**
 * @brief automated test to see if the backup/restore of the JSON file works correctly.
 * CConfigurationBackup is tested here.
 */
class recoveryFileTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void initTestCase();
    void test();

private:
    QFile m_jsonExampleFile;
    QByteArray fileContents(QFile &file);
};

void recoveryFileTest::initTestCase()
{
    // check that we have the JSon file available and ready to read
    QVERIFY(!QStringLiteral(COT_JSON_FILE_PATH).isEmpty());
    QFile originalSaveFile(QStringLiteral(COT_JSON_FILE_PATH));
    QVERIFY(originalSaveFile.exists());
    QVERIFY(originalSaveFile.open(QIODevice::ReadOnly | QIODevice::Text));

    // put save.json in the current directory for the tests.
    QByteArray exampleJSONContents = fileContents(originalSaveFile);
    m_jsonExampleFile.setFileName(QStringLiteral("save.json"));
    QVERIFY(m_jsonExampleFile.open(QIODevice::ReadWrite | QIODevice::Text));
    QCOMPARE(m_jsonExampleFile.write(exampleJSONContents), exampleJSONContents.length());
    QVERIFY(m_jsonExampleFile.seek(0));
}

void recoveryFileTest::test()
{
    QByteArray exampleJSONContents = fileContents(m_jsonExampleFile);
    QVERIFY(!exampleJSONContents.isEmpty());

    CConfigurationBackup backup;
    QVERIFY(backup.createRecoveryFile(exampleJSONContents));
    QVERIFY(backup.overwriteConfigurationFile());
}

QByteArray recoveryFileTest::fileContents(QFile &file)
{
    if (!file.isOpen() && !file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QByteArray();
    }

    QByteArray exampleJSONContents;
    while (!file.atEnd()) {
        exampleJSONContents.append(file.readLine());
    }
    return exampleJSONContents;
}

QTEST_MAIN(recoveryFileTest)

#include "recoveryFileTest.moc"
