#include "SpotData.h"

using namespace ViewModel;


SpotData::SpotData(const QPair<QString, QString> &coinIdsPair,
                   const QPair<QString, QString> &coinSymbolsPair)
    : m_model(Model::SpotDataModelPtr::create(coinIdsPair, coinSymbolsPair))
{
    connect(m_model.get(), &Model::SpotDataModel::itemsChanged, this, &SpotData::itemsChanged);
}


QList<Model::CryptoPair> SpotData::items() const
{
    return m_model->items();
}


QString SpotData::baseCoinSymbol() const
{
    return m_model->baseCoinSymbol();
}


QString SpotData::quoteCoinSymbol() const
{
    return m_model->quoteCoinSymbol();
}


QString SpotData::baseCoinId() const
{
    return m_model->baseCoinId();
}


QString SpotData::quoteCoinId() const
{
    return m_model->quoteCoinId();
}


double SpotData::maxPrice() const
{
    return m_model->maxPrice();
}


double SpotData::minPrice() const
{
    return m_model->minPrice();
}


double SpotData::spread() const
{
    return m_model->spread();
}


void SpotData::appendItem(const Model::CryptoPair &item)
{
    m_model->appendItem(item);
}


//void SpotData::appendItem(const QJsonObject &jsonItem)
//{
//    m_model->appendItem(jsonItem);
//}
