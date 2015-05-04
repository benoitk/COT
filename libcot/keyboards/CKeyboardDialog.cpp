#include "CKeyboardDialog.h"
#include "ui_CKeyboardDialog.h"

CKeyboardDialog::CKeyboardDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CKeyboardDialog)
{
    ui->setupUi(this);

    connect(ui->vbbButtons->addAction(CToolButton::Ok), &QAction::triggered,
            this, &CKeyboardDialog::accept);
    connect(ui->vbbButtons->addAction(CToolButton::Cancel), &QAction::triggered,
            this, &CKeyboardDialog::reject);
}

CKeyboardDialog::~CKeyboardDialog()
{
    delete ui;
}

void CKeyboardDialog::setTitle(const QString &title)
{
    ui->twPages->setTabText(0, title);
}

QString CKeyboardDialog::stringValue() const
{
    return ui->kwKeyboard->text();
}

void CKeyboardDialog::setStringValue(const QString &value)
{
    ui->kwKeyboard->setText(value);
}

