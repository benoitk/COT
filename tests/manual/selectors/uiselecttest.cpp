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
    int r = handler->selectActionType(rowLabel(sender()).toInt());
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbVariableType_clicked()
{
    int r = handler->selectVariableType(variableType(rowLabel(sender()).toInt()));
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbOrganType_clicked()
{
    int r = handler->selectOrganType(VariableOrganType(rowLabel(sender()).toInt()));
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbCycleType_clicked()
{
    int r = handler->selectCycleType(eTypeCycle(rowLabel(sender()).toInt()));
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbVariable_clicked()
{
    QString r = handler->selectVariable(rowLabel(sender()).toString());
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbStream_clicked()
{
    QString r = handler->selectStream(rowLabel(sender()).toString());
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbMeasure_clicked()
{
    QString r = handler->selectMeasure(rowLabel(sender()).toString());
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbCycle_clicked()
{
    QString r = handler->selectCycle(rowLabel(sender()).toString());
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbAction_clicked()
{
    QString r = handler->selectAction(rowLabel(sender()).toString());
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbStreamMeasure_clicked()
{
    QString r = handler->selectStreamOrMeasure(rowLabel(sender()).toString());
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbExtension_clicked()
{
    QString r = handler->selectExtension(rowLabel(sender()).toString());
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbOrgan_clicked()
{
    QString r = handler->selectOrgan(rowLabel(sender()).toString());
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbText_clicked()
{
    QString r = handler->enterText(rowLabel(sender()).toString());
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbInteger_clicked()
{
    int r = handler->enterInteger(rowLabel(sender()).toInt());
    setRowLabel(sender(), r);
}

void UISelectTest::on_pbDouble_clicked()
{
    double r = handler->enterDouble(rowLabel(sender()).toDouble());
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
