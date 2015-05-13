#ifndef CInt_H
#define CInt_H

#include "IVariable.h"

class CInt : public IVariable
{
    Q_OBJECT

public:
    CInt(QObject *parent);
    ~CInt();

    QString toString()const;
    int toInt()const;
    float toFloat()const;
    void setValeur(int iValeur);
    QString getLabel()const;
    void setLabel(QString);

private:
    int m_iValeur;
    QString m_label;
};

#endif // CInt_H
