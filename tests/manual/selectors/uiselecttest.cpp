#include "uiselecttest.h"
#include "ui_uiselecttest.h"
#include "ConfiguratorUIHandler.h"

UISelectTest::UISelectTest(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UISelectTest)
    , handler(new ConfiguratorUIHandler(0, this))
{
    ui->setupUi(this);
}

UISelectTest::~UISelectTest()
{
    delete ui;
}

void UISelectTest::on_pbActionType_clicked()
{
    int r = handler->selectActionType();
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbVariableType_clicked()
{
    int r = handler->selectVariableType();
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbOrganType_clicked()
{
    int r = handler->selectOrganType();
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbCycleType_clicked()
{
    int r = handler->selectCycleType();
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbVariable_clicked()
{
    QString r = handler->selectVariable();
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbStream_clicked()
{
    QString r = handler->selectStream();
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbMeasure_clicked()
{
    QString r = handler->selectMeasure();
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbCycle_clicked()
{
    QString r = handler->selectCycle();
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbAction_clicked()
{
    QString r = handler->selectAction();
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbStreamMeasure_clicked()
{
    QString r = handler->selectStreamOrMeasure();
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbExtension_clicked()
{
    QString r = handler->selectExtension();
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbOrgan_clicked()
{
    QString r = handler->selectOrgan();
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbText_clicked()
{
    QString r = handler->enterText();
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbInteger_clicked()
{
    int r = handler->enterInteger();
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbDouble_clicked()
{
    double r = handler->enterDouble();
    setRowLabel(sender(), r);
}

void UISelectTest::setRowLabel(QObject *row, const QVariant &label)
{
    int i = ui->gridLayout->indexOf(qobject_cast<QWidget *>(row));
    int r;
    int c;
    int rs;
    int cs;
    ui->gridLayout->getItemPosition(i, &r, &c, &rs, &cs);
    QLabel *l = qobject_cast<QLabel *>(ui->gridLayout->itemAtPosition(r, c +1)->widget());
    l->setText(label.toString());
}
