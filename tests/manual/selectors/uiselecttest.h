#ifndef UISELECTTEST_H
#define UISELECTTEST_H

#include <QWidget>
#include <QVariant>

#include "cot_global.h"

namespace Ui {
class UISelectTest;
}

class ConfiguratorUIHandler;

class LIBCOT_EXPORT UISelectTest : public QWidget
{
    Q_OBJECT

public:
    explicit UISelectTest(QWidget *parent = 0);
    ~UISelectTest();

private slots:
    void on_pbActionType_clicked();
    void on_pbVariableType_clicked();
    void on_pbOrganType_clicked();
    void on_pbCycleType_clicked();
    void on_pbVariable_clicked();
    void on_pbStream_clicked();
    void on_pbMeasure_clicked();
    void on_pbCycle_clicked();
    void on_pbAction_clicked();
    void on_pbStreamMeasure_clicked();
    void on_pbExtension_clicked();
    void on_pbOrgan_clicked();
    void on_pbText_clicked();
    void on_pbInteger_clicked();
    void on_pbDouble_clicked();

private:
    Ui::UISelectTest *ui;
    ConfiguratorUIHandler *handler;

    void setRowLabel(QObject* row, const QVariant &label);
};

#endif // UISELECTTEST_H
