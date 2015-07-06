#include "uiselecttest.h"
#include "ui_uiselecttest.h"
#include "IConfiguratorUIHandler.h"

UISelectTest::UISelectTest(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UISelectTest)
    , handler(new IConfiguratorUIHandler(0, this))
{
    ui->setupUi(this);
}

UISelectTest::~UISelectTest()
{
    delete ui;
}

void UISelectTest::on_pbActionType_clicked()
{
    actionType r = static_cast<actionType>(rowLabel(sender()).toInt());
    handler->selectActionType(r);
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbVariableType_clicked()
{
    variableType r = variableType(rowLabel(sender()).toInt());
    handler->selectVariableType(r);
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbOrganType_clicked()
{
    VariableOrganType r = VariableOrganType(rowLabel(sender()).toInt());
    handler->selectOrganType(r);
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbCycleType_clicked()
{
    eTypeCycle r = eTypeCycle(rowLabel(sender()).toInt());
    handler->selectCycleType(r);
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbVariable_clicked()
{
    QString r = rowLabel(sender()).toString();
    handler->selectVariable(r);
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbStream_clicked()
{
    QString r = rowLabel(sender()).toString();
    handler->selectStream(r);
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbMeasure_clicked()
{
    QString r = rowLabel(sender()).toString();
    handler->selectMeasure(r);
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbCycle_clicked()
{
    QString r = rowLabel(sender()).toString();
    handler->selectCycle(r);
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbAction_clicked()
{
    QString r = rowLabel(sender()).toString();
    handler->selectAction(r);
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbStreamMeasure_clicked()
{
    QString r = rowLabel(sender()).toString();
    handler->selectStreamOrMeasure(r);
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbExtension_clicked()
{
    QString r = rowLabel(sender()).toString();
    handler->selectExtension(r);
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbOrgan_clicked()
{
    QString r = rowLabel(sender()).toString();
    handler->selectOrgan(r);
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbUnit_clicked()
{
    QString r = rowLabel(sender()).toString();
    handler->selectUnit(r);
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbText_clicked()
{
    QString r = rowLabel(sender()).toString();
    handler->enterText(r);
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbInteger_clicked()
{
    int r = rowLabel(sender()).toInt();
    handler->enterInteger(r);
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbDouble_clicked()
{
    float r = rowLabel(sender()).toFloat();
    handler->enterFloat(r);
    setRowLabel(sender(), r);
}

QVariant UISelectTest::rowLabel(QObject *row) const
{
    int i = ui->gridLayout->indexOf(qobject_cast<QWidget *>(row));
    int r;
    int c;
    int rs;
    int cs;
    ui->gridLayout->getItemPosition(i, &r, &c, &rs, &cs);
    QLabel *l = qobject_cast<QLabel *>(ui->gridLayout->itemAtPosition(r, c +1)->widget());
    return l->text();
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
