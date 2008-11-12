#include "renderingstyle.h"

#include <QVariant>


namespace udg {


QVariant RenderingStyle::toVariant() const
{
    QMap<QString, QVariant> map;
    map["method"] = method;
    map["diffuseLighting"] = diffuseLighting;
    map["specularLighting"] = specularLighting;
    map["specularPower"] = specularPower;
    map["transferFunction"] = transferFunction.toVariant();
    map["obscurance"] = obscurance;
    map["obscuranceQuality"] = obscuranceQuality;
    map["obscuranceFactor"] = obscuranceFactor;

    return map;
}


RenderingStyle RenderingStyle::fromVariant( const QVariant &variant )
{
    RenderingStyle renderingStyle;
    QMap<QString, QVariant> map = variant.toMap();

    renderingStyle.method = static_cast<Method>( map["method"].toInt() );
    renderingStyle.diffuseLighting = map["diffuseLighting"].toBool();
    renderingStyle.specularLighting = map["specularLighting"].toBool();
    renderingStyle.specularPower = map["specularPower"].toDouble();
    renderingStyle.transferFunction = TransferFunction::fromVariant( map["transferFunction"] );
    renderingStyle.obscurance = map["obscurance"].toBool();
    renderingStyle.obscuranceQuality = static_cast<ObscuranceQuality>( map["obscuranceQuality"].toInt() );
    renderingStyle.obscuranceFactor = map["obscuranceFactor"].toDouble();

    return renderingStyle;
}


}
