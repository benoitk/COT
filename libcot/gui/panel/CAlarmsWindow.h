#ifndef CALARMSWINDOW_H
#define CALARMSWINDOW_H

#include "IWindow.h"
#include "cot_global.h"

/**
 * @brief This window displays the current alarms status.
 */

class QWidget;
class IVariableUIHandler;

class LIBCOT_EXPORT CAlarmsWindow : public IWindow
{
    Q_OBJECT

public:
    explicit CAlarmsWindow(QWidget *parent = Q_NULLPTR);

protected slots:
    void updateAlarms();

private:
    void setupWindow() Q_DECL_OVERRIDE;
    IVariableUIHandler *m_alarmsHandler;
};

#endif // CALARMSWINDOW_H
