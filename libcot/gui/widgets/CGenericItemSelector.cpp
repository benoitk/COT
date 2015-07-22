#include "CGenericItemSelector.h"
#include "CGenericListModel.h"
#include "CGenericListDelegate.h"
#include "CToolButton.h"
#include "CVerticalButtonBar.h"

#include <QTimer>
#include <QAction>
#include <QScrollBar>
#include <QListView>

#include "cotgui_debug.h"

CGenericItemSelector::CGenericItemSelector(const IVariablePtrList &list, QWidget *parent)
    : CDialog(parent)
    , m_model(new CGenericListModel(list, this))
{
    setMinimumSize(640, 480);

    m_lvItems = new QListView(this);
    m_lvItems->setMouseTracking(true);
    m_lvItems->setFrameStyle(QFrame::NoFrame | QFrame::Plain);
    m_lvItems->setViewMode(QListView::IconMode);
    m_lvItems->setMovement(QListView::Static);
    m_lvItems->setSpacing(3);
    m_lvItems->setUniformItemSizes(true);
    m_lvItems->setResizeMode(QListView::Adjust);
    m_lvItems->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_lvItems->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_lvItems->setModel(m_model);
    m_lvItems->setItemDelegate(new CGenericListDelegate(m_lvItems, m_model));
    setMainWidget(m_lvItems);

    buttonBar()->addAction(CToolButton::ScrollUp);
    buttonBar()->addAction(CToolButton::ScrollDown);
    buttonBar()->addAction(CToolButton::Cancel);

    connect(m_lvItems, &QListView::clicked, this, &CGenericItemSelector::itemSelected);
    connect(buttonBar()->action(CToolButton::ScrollUp), &QAction::triggered, this, &CGenericItemSelector::scrollUp);
    connect(buttonBar()->action(CToolButton::ScrollDown), &QAction::triggered, this, &CGenericItemSelector::scrollDown);
    connect(buttonBar()->action(CToolButton::Cancel), &QAction::triggered, this, &CGenericItemSelector::reject);
}

CGenericItemSelector::~CGenericItemSelector()
{
}

IVariablePtr CGenericItemSelector::selectedItem() const
{
    return m_model->currentItem();
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
    QScrollBar *bar = m_lvItems->verticalScrollBar();
    buttonBar()->button(CToolButton::ScrollDown)->setDisabled(bar->value() >= bar->maximum());
    buttonBar()->button(CToolButton::ScrollUp)->setDisabled(bar->value() <= bar->minimum());
}

void CGenericItemSelector::setSelectedItem(IVariablePtr item)
{
    const QModelIndex index = m_model->indexForIVariable(item);

    if (index.isValid()) {
        if (m_lvItems->currentIndex() != index) {
            m_lvItems->setCurrentIndex(index);
        }

        if (m_model->currentItem() != item) {
            m_model->setCurrentItem(item);
        }

        // Most probably this call is made before the window is shown and will probably be resized.
        // Making the scroll move inconsistent, let delay that a bit
        QTimer::singleShot(25, this, [this, index]() {
            m_lvItems->scrollTo(index);
        });
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
    QScrollBar *bar = m_lvItems->verticalScrollBar();

    if (dir == ScrollUp) {
        bar->triggerAction(QAbstractSlider::SliderSingleStepSub);
    } else if (dir == ScrollDown) {
        bar->triggerAction(QAbstractSlider::SliderSingleStepAdd);
    }

    updateScrollButtons();
    // The listview viewport does not update correct with some styles (ie OSX style)
    m_lvItems->viewport()->update();
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
