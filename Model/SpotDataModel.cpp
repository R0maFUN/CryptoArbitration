#include "SpotDataModel.h"

#include <QJsonObject>
#include <QJsonArray>

#include "Common/CommonDataStructures.h"
#include "Common/RequestsPerformer.h"

using namespace Model;


SpotDataModel::SpotDataModel(const QPair<QString, QString> &coinIdsPair,
                             const QPair<QString, QString> &coinSymbolsPair)
    : m_coinIdsPair(coinIdsPair)
    , m_coinSymbolsPair(coinSymbolsPair)
{

}


void SpotDataModel::init(const QList<CryptoPair> &items)
{
    m_items = items;

    emit itemsChanged();
}


//void SpotDataModel::init(const QJsonObject &json)
//{
//    if (json.isEmpty())
//        return;

//    auto jsonItems = json.value("data").toArray();
//    if (jsonItems.isEmpty())
//        return;

//    QList<CryptoPair> items;
//    items.reserve(jsonItems.size());

//    for (const auto &jsonItem : jsonItems)
//    {
//        auto jsonObj = jsonItem.toObject();
//        if (jsonObj.isEmpty())
//            continue;

//        CryptoPair item = CryptoPair::fromJson(jsonObj);

//        items.append(item);
//    }

//    m_items = items;

//    emit itemsChanged();
//}


void SpotDataModel::update()
{
    // make request and init

    //Common::RequestsPerformer *
}


void SpotDataModel::appendItem(const CryptoPair &item)
{
    m_items.append(item);

    emit itemsChanged();
}


//void SpotDataModel::appendItem(const QJsonObject &jsonItem)
//{
//    if (jsonItem.isEmpty())
//        return;

//    appendItem(CryptoPair::fromJson(jsonItem));
//}


QList<CryptoPair> SpotDataModel::items() const
{
    return m_items;
}


QString SpotDataModel::baseCoinSymbol() const
{
    return m_coinSymbolsPair.first;
}


QString SpotDataModel::quoteCoinSymbol() const
{
    return m_coinSymbolsPair.second;
}


QString SpotDataModel::baseCoinId() const
{
    return m_coinIdsPair.first;
}


QString SpotDataModel::quoteCoinId() const
{
    return m_coinIdsPair.second;
}


double SpotDataModel::maxPrice() const
{
    double max = -1;
    for (const auto &item : m_items)
        if (item.price > max)
            max = item.price;

    return max;
}


double SpotDataModel::minPrice() const
{
    double min = m_items.first().price;
    for (const auto &item : m_items)
        if (item.price < min)
            min = item.price;

    return min;
}


double SpotDataModel::spread() const
{
    if (m_items.count() <= 1)
        return 0;

    double result = maxPrice() / minPrice() * 100 - 100;
    return QString::number(result, 'f', 2).toDouble();
}


void SpotDataModel::onUpdateResult(const QJsonObject &result)
{

}


Common::ServiceData * CryptoPair::serviceData() const
{
    return m_service.data();
}


CryptoPair CryptoPair::fromJson(const QJsonObject &jsonItem, const QSharedPointer<Common::ServiceData> &serviceData)
{
    QString exchangeId = jsonItem.value("exchangeId").toString();
    double priceQuote = jsonItem.value("priceQuote").toString().toDouble();
    double priceUsd = jsonItem.value("priceUsd").toString().toDouble();
    double volumeUsd24Hr = QString::number(jsonItem.value("volumeUsd24Hr").toString().toDouble(), 'f', 2).toDouble();
    //auto service = Common::CoinCap::serviceFrom(exchangeId);

    CryptoPair item = {
        serviceData,
        priceQuote,
        priceUsd,
        volumeUsd24Hr
    };

    return item;
}
