#pragma once

#include <QObject>
#include <QSharedPointer>

#include "Common/CommonDataStructures.h"

namespace Model
{

struct P2PDataPair
{
    Common::CryptoCoin cryptoCoin;
    Common::FiatCoin fiatCoin;
    double price;
    Common::PayMethod payMethod;
    // double tax
};

class P2PData
{
public:
    P2PData();

    virtual void update() = 0; // makes request
    virtual void initFromJson(const QJsonObject &jsonObject) = 0; // after succeeded request

    QList<P2PDataPair> getData() const;

private:
    QList<P2PDataPair> m_dataPairList;
};

using P2PDataPtr = QSharedPointer<P2PData>;

} // Model
