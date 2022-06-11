#pragma once

#include <QObject>
#include <QSharedPointer>

#include "CommonDataStructures.h"

struct P2PDataPair
{
    CryptoCoins cryptoCoin;
    FiatCoins fiatCoin;
    double price;
    PayMethod payMethod;
    // double tax
};

class P2PData
{
public:
    P2PData();

    virtual void update() = 0; // makes request
    virtual void initFromJson(const QJsonObject &jsonObject); // after succeeded request

    QList<P2PDataPair> getData() const;

private:
    QList<P2PDataPair> m_dataPairList;
};

using P2PDataPtr = QSharedPointer<P2PData>;
