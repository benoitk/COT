#ifndef CCOMFACTORY_H
#define CCOMFACTORY_H

#include <QObject>

class ICom;
class CComFactory : public QObject
{
    Q_OBJECT

public:
    static ICom* build(const QVariantMap&);


};

#endif // CCOMFACTORY_H