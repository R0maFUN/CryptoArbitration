#pragma once

#include <QObject>
#include <QSharedPointer>

#include "Common/CommonDataStructures.h"

#include "Model/SpotDataModel.h"

namespace ViewModel
{

class SpotData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<Model::CryptoPair> items READ items NOTIFY itemsChanged)
    Q_PROPERTY(QString baseCoinSymbol READ baseCoinSymbol CONSTANT)
    Q_PROPERTY(QString quoteCoinSymbol READ quoteCoinSymbol CONSTANT)
    Q_PROPERTY(QString baseCoinId READ baseCoinId CONSTANT)
    Q_PROPERTY(QString quoteCoinId READ quoteCoinId CONSTANT)
    Q_PROPERTY(double maxPrice READ maxPrice NOTIFY itemsChanged)
    Q_PROPERTY(double minPrice READ minPrice NOTIFY itemsChanged)
    Q_PROPERTY(double spread READ spread NOTIFY itemsChanged)
public:
    SpotData(const QPair<QString, QString> &coinIdsPair,
             const QPair<QString, QString> &coinSymbolsPair);

    QList<Model::CryptoPair> items() const;
    QString baseCoinSymbol() const;
    QString quoteCoinSymbol() const;
    QString baseCoinId() const;
    QString quoteCoinId() const;
    double maxPrice() const;
    double minPrice() const;
    double spread() const;

    void appendItem(const Model::CryptoPair &item);
    //void appendItem(const QJsonObject &jsonItem);

signals:
    void itemsChanged();

private:
    Model::SpotDataModelPtr m_model;
};

using SpotDataPtr = QSharedPointer<SpotData>;

} // ViewModel
