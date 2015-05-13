#ifndef CORGAN_H
#define CORGAN_H

#include <QObject>
#include "IOrgan.h"
#include <QObject>
#include "qvariant.h"



//Class générique pour tous les organs pour l'instant
//pas sur que l'on est des traitements spécifique pour chaque organ, les traitements se faisent dans les actions.

class IVariable;
class COrgan : public IOrgan
{
    Q_OBJECT

public:
    COrgan(const QVariantMap& mapOrgan);

    QString getName()const Q_DECL_OVERRIDE;
    void setName(const QString &) Q_DECL_OVERRIDE;
    organType getType()const Q_DECL_OVERRIDE;
    //adresse physique sur le materiel, varie selon protocol
    QString getAddress()const Q_DECL_OVERRIDE;
    void setAddress(const QString &) Q_DECL_OVERRIDE;
    QString toString()const Q_DECL_OVERRIDE;
    //QList<IVariable*> getListParamters()const Q_DECL_OVERRIDE;

private:

    int m_address;
    organType m_type;
    QString m_name;

};

#endif // CORGAN_H