#ifndef CGRAPHICSWIDGET_H
#define CGRAPHICSWIDGET_H

#include <QWidget>
#include "cot_global.h"

class KPlotWidget;
class LIBCOT_EXPORT CGraphicsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CGraphicsWidget(QWidget *parent = Q_NULLPTR);
    ~CGraphicsWidget();

private:
    void initializeGraphic();
    KPlotWidget *m_plotWidget;
};

#endif // CGRAPHICSWIDGET_H
