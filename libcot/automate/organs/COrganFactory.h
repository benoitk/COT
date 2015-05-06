#ifndef CORGANFACTORY_H
#define CORGANFACTORY_H

#include <QObject>

class IOrgan;
class COrganFactory : public QObject
{
    Q_OBJECT

public:
    static IOrgan* build(const QVariantMap&);


private:
    
};

#endif // CORGANFACTORY_H
