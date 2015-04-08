#include <QCoreApplication>
#include <QCommandLineParser>
#include <QFile>
#include <QDebug>

#include "CTranslator.h"

void showUsage(const QString &message, QCommandLineParser &parser, int exitCode) {
    qWarning("%s\n", qPrintable(message));
    parser.showHelp(exitCode);
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("cot-translator");
    QCoreApplication::setApplicationVersion("1.0.0");

    QCommandLineOption modeOption(QStringList() << "m" << "mode",
            QCoreApplication::translate("main", "The execution mode of the translator: 'import' or 'export' (default)."),
            QCoreApplication::translate("main", "mode"));

    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::translate("main",
                                    "A command line tool to extract and import translations for the cot application."));
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption(modeOption);
    parser.addPositionalArgument("json", QCoreApplication::translate("main", "Json file to read or write."));
    parser.addPositionalArgument("translations", QCoreApplication::translate("main",
                                                                "The folder to read or write the translations files."));

    parser.process(app);

    const QString mode = parser.value("mode").toLower();
    const bool import = mode == "import";
    const QStringList args = parser.positionalArguments();
    const QString jsonFilePath = args.value(0);
    const QString translationsPath = args.value(1);

    if (!mode.isEmpty() && (mode != "import" && mode != "export")) {
        showUsage("Wrong mode used.", parser, 1);
    }

    if (jsonFilePath.isEmpty()) {
        showUsage("The json file is empty.", parser, 1);
    }
    else if (!QFile::exists(jsonFilePath)) {
        showUsage("The json file does not exists.", parser, 1);
    }

    if (translationsPath.isEmpty()) {
        showUsage("The translations folder is empty.", parser, 1);
    }
    else if (import) {
        if (!QFile::exists(translationsPath)) {
            showUsage("The translations folder does not exists.", parser, 1);
        }
    }

    CTranslator translator;

    if (import) {
        if (!translator.importFrom(translationsPath, jsonFilePath)) {
            qDebug("%s: Can't import translations (%s).", Q_FUNC_INFO, qPrintable(translationsPath));
            return 2;
        }
    }
    else {
        if (!translator.exportFrom(jsonFilePath, translationsPath)) {
            qDebug("%s: Can't export translations (%s).", Q_FUNC_INFO, qPrintable(translationsPath));
            return 2;
        }
    }

    return 0;
}
