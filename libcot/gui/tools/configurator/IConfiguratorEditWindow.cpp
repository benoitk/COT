#include "IConfiguratorEditWindow.h"
#include "ui_IConfiguratorEditWindow.h"
#include "IConfiguratorEditTab.h"

#include <QDebug>

IConfiguratorEditWindow::IConfiguratorEditWindow(const QVariant &object, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IConfiguratorEditWindow)
    , m_editedObject(object)
{
    ui->setupUi(this);
}

IConfiguratorEditWindow::~IConfiguratorEditWindow()
{
    delete ui;
}

void IConfiguratorEditWindow::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);

    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
        slotRetranslate();
    }
}

QVariant IConfiguratorEditWindow::editedObject() const
{
    return m_editedObject;
}

void IConfiguratorEditWindow::initBaseWindow()
{
    ui->retranslateUi(this);
    slotRetranslate();
}

void IConfiguratorEditWindow::addTab(IConfiguratorEditTab *tab)
{
    ui->twPages->addTab(tab, QString());
    connect(tab, &IConfiguratorEditTab::signalOkTriggered, this, &IConfiguratorEditWindow::slotOkTriggered);
    connect(tab, &IConfiguratorEditTab::signalCancelTriggered, this, &IConfiguratorEditWindow::slotCancelTriggered);
}

void IConfiguratorEditWindow::setTabText(int index, const QString &text)
{
    ui->twPages->setTabText(index, text);
}

void IConfiguratorEditWindow::applyProperties()
{
    for (int i = 0; i < ui->twPages->count(); ++i) {
        IConfiguratorEditTab *tab = qobject_cast<IConfiguratorEditTab *>(ui->twPages->widget(i));
        qDebug() << tab << ui->twPages->widget(i);
        tab->applyProperties(m_editedObject);
    }
}
