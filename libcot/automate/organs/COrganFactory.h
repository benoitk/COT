#ifndef CORGANFACTORY_H
#define CORGANFACTORY_H

#include <QObject>

class IOrgan;
class CModelExtensionCard;
class COrganFactory : public QObject
{
    Q_OBJECT

public:
    static IOrgan* build(const QVariantMap&, CModelExtensionCard* arg_extCard);


private:

};

#endif // CORGANFACTORY_H
