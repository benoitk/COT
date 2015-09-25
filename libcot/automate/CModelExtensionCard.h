#ifndef CMODELEXTENSIONCARD_H
#define CMODELEXTENSIONCARD_H

#include "IComObserver.h"

#include <QObject>
#include "qlist.h"
#include "qvariant.h"

class ICom;
class IVariableInput;
class IOrgan;
class CModelExtensionCard : public QObject, public IComObserver
{
    Q_OBJECT

public:
    //Use for API
    QList<IOrgan*>  getListOrgans()const;
    QString getLabel()const;
    ICom* getICom()const;
    IOrgan* getOrgan(const QString& arg_name);
    QMap<QString, IOrgan*> getMapOrgans();
    //
    CModelExtensionCard(QObject *parent);
    CModelExtensionCard(const QVariantMap& mapExt);
    ~CModelExtensionCard();

    QString getName()const;
    QVariant readOrganneValue(IVariableInput*);

    QVariantMap serialize();


    //IComObserver
    IVariable* getVariableByAddr(const QString &addr_var)const Q_DECL_OVERRIDE;
    void setCom(ICom*) Q_DECL_OVERRIDE;


private:

    //qmap<name, type>

    QMap<QString, IOrgan*> m_mapOrgans;
    ICom* m_interfaceCom;

    QString m_label;
    QString m_name;

};

#endif // CMODELEXTENSIONCARD_H
