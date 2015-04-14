#include "CGenericItemSelector.h"
#include "CGenericListModel.h"
#include "CGenericListDelegate.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QScrollBar>

#include <QDebug>

static const int buttonsHeight = 50;

CGenericItemSelector::CGenericItemSelector(const IVariablePtrList &list, QWidget *parent)
    : QDialog(parent),
      m_model(new CGenericListModel(list, this)),
      m_currentItem(Q_NULLPTR)
{

    m_listView = new QListView(this);
    m_listView->setViewMode(QListView::IconMode);
    m_listView->setModel(m_model);
    m_listView->setResizeMode(QListView::Adjust);
    m_listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    CGenericListDelegate *delegate = new CGenericListDelegate(this);
    m_listView->setItemDelegate(delegate);

    QPushButton *cancelButton = new QPushButton(this);
    cancelButton->setText(tr("Cancel"));
    cancelButton->setFixedHeight(buttonsHeight);

    m_upButton = new QPushButton(this);
    m_upButton->setText(tr("▲"));
    m_upButton->setFixedHeight(buttonsHeight);
    m_upButton->setEnabled(false); // we're on top of the list atm

    m_downButton = new QPushButton(this);
    m_downButton->setText(tr("▼"));
    m_downButton->setFixedHeight(buttonsHeight);

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(m_upButton);
    vLayout->addWidget(m_downButton);
    vLayout->addWidget(cancelButton);
    vLayout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(m_listView);
    hLayout->addLayout(vLayout);
    hLayout->setContentsMargins(0, 0, 0, 0);

    connect(m_listView, SIGNAL(clicked(QModelIndex)), this, SLOT(itemSelected(QModelIndex)));

    connect(m_upButton, SIGNAL(clicked()), this, SLOT(scrollUp()));
    connect(m_downButton, SIGNAL(clicked()), this, SLOT(scrollDown()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
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

void CGenericItemSelector::setSelectedItem(const IVariablePtr item)
{
    if (item && modelContains(item->toString())) {
        m_currentItem = item;
        Q_EMIT selectedItemChanged(m_currentItem);
    }
}

void CGenericItemSelector::scroll(CGenericItemSelector::Direction dir)
{
    QScrollBar *bar = m_listView->verticalScrollBar();

    if (dir == ScrollUp) {
        bar->triggerAction(QAbstractSlider::SliderSingleStepSub);

    } else if (dir == ScrollDown) {
        bar->triggerAction(QAbstractSlider::SliderSingleStepAdd);
    }

    m_downButton->setDisabled(bar->value() >= bar->maximum());
    m_upButton->setDisabled(bar->value() <= bar->minimum());
}

bool CGenericItemSelector::modelContains(const QString &itemLabel)
{
    for (int row = 0; row < m_model->rowCount(); ++row) {
        if (itemLabel == m_model->data(m_model->index(row)).toString()) {
            return true;
        }
    }
    return false;
}

