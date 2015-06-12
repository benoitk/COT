#include "CNumericalKeyboardDialog.h"
#include "ui_CNumericalKeyboardDialog.h"

#include <CPCWindow.h>

CNumericalKeyboardDialog::CNumericalKeyboardDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CNumericalKeyboardDialog)
{
    ui->setupUi(this);
    initialize(CNumericalKeyboardWidget::Double);
}

CNumericalKeyboardDialog::CNumericalKeyboardDialog(CNumericalKeyboardWidget::Mode mode, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CNumericalKeyboardDialog)
{
    ui->setupUi(this);
    initialize(mode);
}

CNumericalKeyboardDialog::~CNumericalKeyboardDialog()
{
    delete ui;
}

void CNumericalKeyboardDialog::setTitle(const QString &title)
{
    ui->twPages->setTabText(0, title);
}

int CNumericalKeyboardDialog::integerValue() const
{
    return ui->nkwKeyboard->integerNumber();
}

void CNumericalKeyboardDialog::setIntegerValue(int value)
{
    ui->nkwKeyboard->setIntegerNumber(value);
}

float CNumericalKeyboardDialog::floatValue() const
{
    return ui->nkwKeyboard->floatNumber();
}

void CNumericalKeyboardDialog::setFloatValue(float value)
{
    ui->nkwKeyboard->setFloatNumber(value);
}

bool CNumericalKeyboardDialog::getInteger(int &value, const QString &title, QWidget *parent)
{
    CNumericalKeyboardDialog dlg(CNumericalKeyboardWidget::Integer, parent);
    dlg.setTitle(!title.isEmpty() ? title : tr("Enter a new value"));
    dlg.setIntegerValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.integerValue();
        return true;
    }

    return false;
}

void CNumericalKeyboardDialog::initialize(CNumericalKeyboardWidget::Mode mode)
{
    ui->nkwKeyboard->setMode(mode);

    connect(ui->vbbButtons->addAction(CToolButton::Ok), &QAction::triggered,
            this, &CNumericalKeyboardDialog::accept);
    connect(ui->vbbButtons->addAction(CToolButton::Cancel), &QAction::triggered,
            this, &CNumericalKeyboardDialog::reject);
}

