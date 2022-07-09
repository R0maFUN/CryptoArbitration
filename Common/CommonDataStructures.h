#pragma once

#include <QObject>
#include <QMap>
#include <QString>
#include <QUrl>
#include <QSharedPointer>

namespace Common
{

enum class CryptoCoin
{
    USDT,
    BNB,
    ETH,
    BTC
};

const QMap<CryptoCoin, QString> CryptoCoinsRelations = {
    { CryptoCoin::USDT, "USDT" },
    { CryptoCoin::BNB,  "BNB"  },
    { CryptoCoin::ETH,  "ETH"  },
    { CryptoCoin::BTC,  "BTC"  }
};

enum class FiatCoin
{
    RUB,
};

const QMap<FiatCoin, QString> FiatCoinsRelations = {
    { FiatCoin::RUB, "RUB" }
};

enum class PayMethod
{
    Any,
    Sberbank,
    Tinkoff,
    Rosbank,
    // ...
};


class ServiceData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString label READ name CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QUrl icon READ icon CONSTANT)
    Q_PROPERTY(QUrl url READ url CONSTANT)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

public:
    enum Service
    {
        Unknown,
        Binance,
        Huobi,
        Kucoin,
        Bitfinex,
        Bithumbglobal,
        Bitmax,
        Bitso,
        Bitstamp,
        CoinTiger,
        CoinBase,
        Uniswap,
        DigiFinex,
        Kraken,
        BigONE,
        Hotbit
    };
    Q_ENUM(Service)

    ServiceData(const QString &name, const QString &id, const QUrl &icon, const QUrl &url);

    bool enabled() const;
    void setEnabled(const bool &value);
    Q_INVOKABLE void toggleEnabled();

    QString name();
    QString id();
    QUrl icon();
    QUrl url();
    Service service();

signals:
    void enabledChanged();


private:
    const QString m_name;
    const QString m_id;
    const QUrl m_icon;
    const QUrl m_url;
    const Service m_service;
    bool m_enabled = true;
};


class CoinCap
{
public:
    explicit CoinCap() = default;

    static QMap<QString, ServiceData::Service> serviceRelation();
    //static const QMap<Service, ServiceData> serviceDataRelation();

    //static QSharedPointer<ServiceData> serviceFrom(const QString &exchangeId);
    //static ServiceData serviceDataFrom(const Service &service);

    static QList<QSharedPointer<ServiceData>> availableServices();
};

} // Common

//Q_DECLARE_METATYPE(Common::ServiceData)
