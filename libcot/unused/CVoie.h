#ifndef CVOIE_H
#define CVOIE_H

#include "ilistvariable.h"

class CVoie : public IVariable
{
    Q_OBJECT

public:
    CVoie(QObject *parent);
    CVoie(QObject *parent, int iNumVoie);
    ~CVoie();
    QString toString()const;
    int toInt()const;
    float toFloat()const;
    void setValeur(int iNumVoie);
    QString getLabel()const;
    void setLabel(QString);
private:
    int m_iNumVoie;
    QString m_label;
};

#endif // CVOIE_H
