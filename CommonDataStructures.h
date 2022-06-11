#pragma once

#include <QMap>
#include <QString>

enum class CryptoCoins
{
    USDT,
    BNB,
    ETH,
    BTC
};

const QMap<CryptoCoins, QString> CryptoCoinsRelations = {
    { CryptoCoins::USDT, "USDT" },
    { CryptoCoins::BNB,  "BNB"  },
    { CryptoCoins::ETH,  "ETH"  },
    { CryptoCoins::BTC,  "BTC"  }
};

enum class FiatCoins
{
    RUB,
};

const QMap<FiatCoins, QString> FiatCoinsRelations = {
    { FiatCoins::RUB, "RUB" }
};

enum class PayMethod
{
    Any,
    Sberbank,
    Tinkoff,
    Rosbank,
    // ...
};
