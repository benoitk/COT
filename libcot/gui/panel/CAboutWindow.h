#ifndef CABOUTWINDOW_H
#define CABOUTWINDOW_H

#include <CDialog.h>

class CAboutWindow : public CDialog
{
    Q_OBJECT
public:
    explicit CAboutWindow(QWidget *parent = Q_NULLPTR);
    ~CAboutWindow();

private:
    QString analyzerString() const;
};

#endif // CABOUTWINDOW_H
