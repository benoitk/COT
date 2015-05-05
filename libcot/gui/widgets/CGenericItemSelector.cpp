#include "CGenericItemSelector.h"
#include "ui_CGenericItemSelector.h"
#include "CGenericListModel.h"
#include "CGenericListDelegate.h"

#include <QTimer>
#include <QScrollBar>
#include <QDebug>

CGenericItemSelector::CGenericItemSelector(const IVariablePtrList &list, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CGenericItemSelector)
    , m_model(new CGenericListModel(list, this))
    , m_currentItem(Q_NULLPTR)
{
    setMinimumSize(640, 480);

    ui->setupUi(this);
    ui->lvItems->setMouseTracking(true);
    ui->lvItems->setModel(m_model);
    ui->lvItems->setItemDelegate(new CGenericListDelegate(this));
    ui->vbbButtons->addAction(CToolButton::ScrollUp);
    ui->vbbButtons->addAction(CToolButton::ScrollDown);
    ui->vbbButtons->addAction(CToolButton::Cancel);

    connect(ui->lvItems, &QListView::clicked, this, &CGenericItemSelector::itemSelected);
    connect(ui->vbbButtons->action(CToolButton::ScrollUp), &QAction::triggered, this, &CGenericItemSelector::scrollUp);
    connect(ui->vbbButtons->action(CToolButton::ScrollDown), &QAction::triggered, this, &CGenericItemSelector::scrollDown);
    connect(ui->vbbButtons->action(CToolButton::Cancel), &QAction::triggered, this, &CGenericItemSelector::reject);
}

CGenericItemSelector::~CGenericItemSelector()
{
    delete ui;
}

void CGenericItemSelector::setTitle(const QString &title)
{
    ui->twPages->setTabText(0, title);
}

IVariablePtr CGenericItemSelector::selectedItem() const
{
    return m_currentItem;
}

void CGenericItemSelector::itemSelected(const QModelIndex &index)
{
    IVariablePtr var = m_model->IVariableForIndex(index);
    setSelectedItem(var);
    QDialog::accept();
}

void CGenericItemSelector::scrollUp()
{
    scroll(ScrollUp);
}

void CGenericItemSelector::scrollDown()
{
    scroll(ScrollDown);
}

void CGenericItemSelector::updateScrollButtons()
{
    QScrollBar *bar = ui->lvItems->verticalScrollBar();
    ui->vbbButtons->button(CToolButton::ScrollDown)->setDisabled(bar->value() >= bar->maximum());
    ui->vbbButtons->button(CToolButton::ScrollUp)->setDisabled(bar->value() <= bar->minimum());
}

void CGenericItemSelector::setSelectedItem(IVariablePtr item)
{
    const QModelIndex index = m_model->indexForIVariable(item);

    if (index.isValid()) {
        const bool locked = ui->lvItems->blockSignals(true);

        if (ui->lvItems->currentIndex() != index) {
            ui->lvItems->setCurrentIndex(index);
        }

        ui->lvItems->blockSignals(locked);
        ui->lvItems->scrollTo(index);
        m_currentItem = item;
        emit selectedItemChanged(m_currentItem);
    }
}

void CGenericItemSelector::setSelectedName(const QString &name)
{
    setSelectedItem(m_model->IVAriableForName(name));
}

void CGenericItemSelector::setSelectedValue(const QVariant &value)
{
    setSelectedItem(m_model->IVAriableForValue(value.toString()));
}

void CGenericItemSelector::scroll(CGenericItemSelector::Direction dir)
{
    QScrollBar *bar = ui->lvItems->verticalScrollBar();

    if (dir == ScrollUp) {
        bar->triggerAction(QAbstractSlider::SliderSingleStepSub);
    } else if (dir == ScrollDown) {
        bar->triggerAction(QAbstractSlider::SliderSingleStepAdd);
    }

    updateScrollButtons();
}

void CGenericItemSelector::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    QTimer::singleShot(25, this, &CGenericItemSelector::updateScrollButtons);
}

void CGenericItemSelector::wheelEvent(QWheelEvent *event)
{
    QDialog::wheelEvent(event);
    QTimer::singleShot(25, this, &CGenericItemSelector::updateScrollButtons);
}
