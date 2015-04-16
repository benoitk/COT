#ifndef CCONVERTERFACTORY_H
#define CCONVERTERFACTORY_H

#include <QObject>

class IConverter;
class CConverterFactory : public QObject
{
   	Q_OBJECT

public:
    static IConverter* build(const QVariantMap&);
    
};

#endif //CCONVERTERFACTORY_H