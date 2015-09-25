#ifndef IORGAN_H
#define IORGAN_H

#include <QObject>
#include "qstring.h"
#include "qlist.h"
#include "qvariant.h"
enum organType{
        organ_type_output_bool = 0,
        organ_type_output_float,
        organ_type_output_int,
        organ_type_input_bool,
        organ_type_input_float,
        organ_type_input_int
};

class IVariable;
class CModelExtensionCard;
class IOrgan : public QObject
{
    Q_OBJECT

public:
    virtual QString getName()const=0;
    virtual void setName(const QString &)=0;
    virtual organType getType()const=0;
    //adresse physique sur le materiel, varie selon protocol
    virtual QString getAddress()const=0;
    virtual void setAddress(const QString &)=0;
    virtual QString toString()const=0;
    //virtual QList<IVariable*> getListParamters()const=0;
    virtual CModelExtensionCard* getExtCard()=0;
    virtual QVariantMap serialize();
private:
    organType m_type;
};

#endif // IORGAN_H
