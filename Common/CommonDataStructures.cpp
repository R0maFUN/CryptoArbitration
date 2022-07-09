#include "CommonDataStructures.h"

#include <QDebug>

#include <functional>


using namespace Common;


QMap<QString, ServiceData::Service> CoinCap::serviceRelation()
{
    static const QMap<QString, ServiceData::Service> relation = {
        { "binance", ServiceData::Service::Binance },
        { "huobi", ServiceData::Service::Huobi },
        { "kucoin", ServiceData::Service::Kucoin },
        { "bitfinex", ServiceData::Service::Bitfinex },
        { "bithumbglobal", ServiceData::Service::Bithumbglobal },
        { "bitmax", ServiceData::Service::Bitmax },
        { "bitso", ServiceData::Service::Bitso },
        { "bitstamp", ServiceData::Service::Bitstamp },
        { "gdax", ServiceData::Service::CoinBase },
        { "uniswap-v3", ServiceData::Service::Uniswap },
        { "digifinex", ServiceData::Service::DigiFinex },
        { "kraken", ServiceData::Service::Kraken },
        { "bigone", ServiceData::Service::BigONE },
        { "cointiger", ServiceData::Service::CoinTiger },
        { "hotbit", ServiceData::Service::Hotbit },
    };

    return relation;
}


//QSharedPointer<ServiceData> CoinCap::serviceFrom(const QString &exchangeId)
//{
//    auto it = std::find_if(availableServices().begin(), availableServices().end(),
//                           [=](const QSharedPointer<ServiceData> &item){
//        return item->id() == exchangeId;
//    });

//    auto item = *it;
//    qDebug() << "item name" << item->name();

//    if (it != availableServices().end())
//        return *it;
//    else
//        return QSharedPointer<ServiceData>();
//}


ServiceData::ServiceData(const QString &name, const QString &id, const QUrl &icon, const QUrl &url)
    : m_name(name)
    , m_id(id)
    , m_icon(icon)
    , m_url(url)
    , m_service(CoinCap::serviceRelation().value(id))
{

}


bool ServiceData::enabled() const
{
    return m_enabled;
}


void ServiceData::setEnabled(const bool &value)
{
    if (m_enabled == value)
        return;

    m_enabled = value;
    emit enabledChanged();
}


void ServiceData::toggleEnabled()
{
    setEnabled(!enabled());
}


QString ServiceData::name()
{
    return m_name;
}


QString ServiceData::id()
{
    return m_id;
}


QUrl ServiceData::icon()
{
    return m_icon;
}


QUrl ServiceData::url()
{
    return m_url;
}


QList<QSharedPointer<ServiceData> > CoinCap::availableServices()
{
    const static QList<QSharedPointer<ServiceData> > res = {
        QSharedPointer<ServiceData>::create("Binance", "binance",
                                            QUrl("https://bin.bnbstatic.com/static/images/common/favicon.ico"),
                                            QUrl("https://www.binance.com/ru")),
        QSharedPointer<ServiceData>::create("Huobi", "huobi",
                                            QUrl("https://bin.bnbstatic.com/static/images/common/favicon.ico"),
                                            QUrl("https://www.binance.com/ru")),
        QSharedPointer<ServiceData>::create("KuCoin", "kucoin",
                                            QUrl("https://bin.bnbstatic.com/static/images/common/favicon.ico"),
                                            QUrl("https://www.binance.com/ru")),
        QSharedPointer<ServiceData>::create("Bitfinex", "bitfinex",
                                            QUrl("https://bin.bnbstatic.com/static/images/common/favicon.ico"),
                                            QUrl("https://bitfinex.com")),
        QSharedPointer<ServiceData>::create("Bithumbglobal", "bithumbglobal",
                                            QUrl("https://bin.bnbstatic.com/static/images/common/favicon.ico"),
                                            QUrl("https://www.binance.com/ru")),
        QSharedPointer<ServiceData>::create("Bitmax", "bitmax",
                                            QUrl("https://bin.bnbstatic.com/static/images/common/favicon.ico"),
                                            QUrl("https://www.binance.com/ru")),
        QSharedPointer<ServiceData>::create("Bitso", "bitso",
                                            QUrl("https://bin.bnbstatic.com/static/images/common/favicon.ico"),
                                            QUrl("https://www.binance.com/ru")),
        QSharedPointer<ServiceData>::create("Bitstamp", "bitstamp",
                                            QUrl("https://bin.bnbstatic.com/static/images/common/favicon.ico"),
                                            QUrl("https://www.bitstamp.net/")),
        QSharedPointer<ServiceData>::create("CoinBase", "gdax",
                                            QUrl("https://bin.bnbstatic.com/static/images/common/favicon.ico"),
                                            QUrl("https://pro.coinbase.com/")),
        QSharedPointer<ServiceData>::create("Uniswap", "uniswap-v3",
                                            QUrl("https://bin.bnbstatic.com/static/images/common/favicon.ico"),
                                            QUrl("https://uniswap.org/")),
        QSharedPointer<ServiceData>::create("DigiFinex", "digifinex",
                                            QUrl("https://bin.bnbstatic.com/static/images/common/favicon.ico"),
                                            QUrl("https://www.digifinex.com/")),
        QSharedPointer<ServiceData>::create("Kraken", "kraken",
                                            QUrl("https://bin.bnbstatic.com/static/images/common/favicon.ico"),
                                            QUrl("https://kraken.com")),
        QSharedPointer<ServiceData>::create("BigONE", "bigone",
                                            QUrl("https://bin.bnbstatic.com/static/images/common/favicon.ico"),
                                            QUrl("https://big.one/")),
        QSharedPointer<ServiceData>::create("CoinTiger", "cointiger",
                                            QUrl("https://bin.bnbstatic.com/static/images/common/favicon.ico"),
                                            QUrl("https://www.cointiger.com/")),
        QSharedPointer<ServiceData>::create("Hotbit", "hotbit",
                                            QUrl("https://bin.bnbstatic.com/static/images/common/favicon.ico"),
                                            QUrl("https://www.hotbit.io/")),
    };

    return res;
}
