#pragma once

#include <QObject>
#include <QSharedPointer>
#include <QList>
#include <QPair>

#include "Common/CommonDataStructures.h"

namespace Model
{

struct CryptoPair
{
private:
    Q_GADGET
    Q_PROPERTY(Common::ServiceData * service READ serviceData)
    Q_PROPERTY(double price MEMBER price)
    Q_PROPERTY(double priceUsd MEMBER priceUsd)
    Q_PROPERTY(double volumeUsd24Hr MEMBER volumeUsd24Hr)

public:
    QSharedPointer<Common::ServiceData> m_service;
    //QString serviceStr
    double price;
    double priceUsd;
    double volumeUsd24Hr;

    Common::ServiceData * serviceData() const;

    static CryptoPair fromJson(const QJsonObject &jsonItem, const QSharedPointer<Common::ServiceData> &serviceData);
};

class SpotDataModel : public QObject
{
    Q_OBJECT

public:
    SpotDataModel(const QPair<QString, QString> &coinIdsPair,
                  const QPair<QString, QString> &coinSymbolsPair);

    void init(const QList<CryptoPair> &items);
    //void init(const QJsonObject &json);

    void update();

    void appendItem(const CryptoPair &item);
    //void appendItem(const QJsonObject &jsonItem);

    QList<CryptoPair> items() const;
    QString baseCoinSymbol() const;
    QString quoteCoinSymbol() const;
    QString baseCoinId() const;
    QString quoteCoinId() const;
    double maxPrice() const;
    double minPrice() const;
    double spread() const;

public slots:
    void onUpdateResult(const QJsonObject &result);

signals:
    void itemsChanged();

private:
    QList<CryptoPair> m_items;
    QPair<QString, QString> m_coinIdsPair;
    QPair<QString, QString> m_coinSymbolsPair;
};

using SpotDataModelPtr = QSharedPointer<SpotDataModel>;

} // Model

Q_DECLARE_METATYPE(Model::CryptoPair)
