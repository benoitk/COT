#include "CConverterFactory.h"
#include "CConverterCoef.h"
#include "CConverterCoefOffset.h"
#include "CConverterOffset.h"
#include "CConverterOffsetCoef.h"
#include "CConverterUnknow.h"
#include "IConverter.h"

#include "qvariant.h"
#include "qmap.h"
#include "cotautomate_debug.h"

IConverter* CConverterFactory::build(const QVariantMap &mapConverter){
    
    IConverter* converter = NULL;
    if(mapConverter[QStringLiteral("type")].toString() == QStringLiteral("coef")){
        converter = new CConverterCoef(mapConverter);
    }
    else if(mapConverter[QStringLiteral("type")].toString() == QStringLiteral("coef_offset")){
        converter = new CConverterCoefOffset(mapConverter);
    }
    else if(mapConverter[QStringLiteral("type")].toString() == QStringLiteral("offset")){
        converter = new CConverterOffset(mapConverter);
    }
    else if(mapConverter[QStringLiteral("type")].toString() == QStringLiteral("offset_coef")){
        converter = new CConverterOffsetCoef(mapConverter);
    
    }else{
        converter = new CConverterUnknow();
        qCDebug(COTAUTOMATE_LOG) << "Classe converter INCONNUE :  " << mapConverter[QStringLiteral("type")].toString();
    
    }

    return converter;
}