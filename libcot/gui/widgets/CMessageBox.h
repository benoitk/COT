#ifndef CMESSAGEBOX_H
#define CMESSAGEBOX_H

#include "IWindow.h"
#include "cot_global.h"

/**
 * @brief This dialog displays a modal message.
 */

class QWidget;
class IVariableUIHandler;

class LIBCOT_EXPORT CMessageBox : public IWindow
{
    Q_OBJECT
public:
    explicit CMessageBox(const QString &message, QWidget *parent = Q_NULLPTR);
    ~CMessageBox();
private:
    void setupWindow() Q_DECL_OVERRIDE;
    QString m_message;
};

#endif // CMESSAGEBOX_H
