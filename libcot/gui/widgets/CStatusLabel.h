#ifndef CSTATUSLABEL_H
#define CSTATUSLABEL_H

#include <QLabel>

class CStatusLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CStatusLabel(QWidget *parent = Q_NULLPTR);
    ~CStatusLabel();
};

#endif // CSTATUSLABEL_H
