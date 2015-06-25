#ifndef CCONTROLERAUTOMATE_H
#define CCONTROLERAUTOMATE_H

#include <QObject>
#include <qthread.h>

#include "../cot_global.h"

class LIBCOT_EXPORT CControlerAutomate : public QObject
{
    Q_OBJECT
private:
    QThread m_automateThread;

public slots:
    void automateStopped();
public:
    CControlerAutomate();
    ~CControlerAutomate();

};

#endif
