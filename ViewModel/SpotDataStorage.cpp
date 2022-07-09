#include "SpotDataStorage.h"

#include <QUrlQuery>
#include <QJsonArray>
#include <QVariant>
#include <QCoreApplication>

#include "ViewModel/SpotData.h"

using namespace ViewModel;


SpotDataStorage::SpotDataStorage(const SettingsViewModelPtr &settings)
    : m_listModel(QSharedPointer<SpotDataStorageModel>::create())
    , m_settings(settings)
{
    m_dataFilter = QSharedPointer<DataFilter>::create();
    m_dataFilter->setSourceModel(m_listModel.get());

    update();
}


void SpotDataStorage::addData(const QJsonObject &json)
{
    auto jsonItems = json.value("data").toArray();
    if (jsonItems.isEmpty())
        return;

    for (const auto &jsonItem : jsonItems)
    {
        auto jsonObj = jsonItem.toObject();
        if (jsonObj.isEmpty())
            continue;

        QString baseId = jsonObj.value("baseId").toString();
        QString quoteId = jsonObj.value("quoteId").toString();
        QString baseSymbol = jsonObj.value("baseSymbol").toString();
        QString quoteSymbol = jsonObj.value("quoteSymbol").toString();
        QString exchangeId = jsonObj.value("exchangeId").toString();
        QPair<QString, QString> coinIdsPair = { baseId, quoteId };
        QPair<QString, QString> coinSymbolsPair = { baseSymbol, quoteSymbol };

        Model::CryptoPair pair = Model::CryptoPair::fromJson(jsonObj, m_settings->serviceFromId(exchangeId));
        if (pair.volumeUsd24Hr < m_settings->minVolume())
            continue;

        SpotDataPtr spotData;
        if (m_itemsMap.contains(coinIdsPair))
        {
            spotData = m_itemsMap.value(coinIdsPair);
        }
        else
        {
            spotData = SpotDataPtr::create(coinIdsPair, coinSymbolsPair);
            m_itemsMap.insert(coinIdsPair, spotData);
            m_listModel->append(spotData);

            emit itemsChanged();
        }

        spotData->appendItem(pair);
    }

    //m_dataFilter->sort(0, Qt::DescendingOrder);
    //emit itemsChanged();
}


void SpotDataStorage::update()
{
    clear();

    for (const auto& service : m_settings->services())
    {
        if (!service->enabled())
            continue;

        qDebug() << "SpotDataStorage::update making request for " << service->name();

        Common::RequestsPerformer * requestPerformer = new Common::RequestsPerformer();

        QUrl url = QString("https://api.coincap.io/v2/markets");
        QUrlQuery query;
        query.addQueryItem("quoteId", "tether");
        query.addQueryItem("limit", "500");
        query.addQueryItem("exchangeId", service->id());
        url.setQuery(query);

        QMap<QString, QString> headers;
        headers.insert("Accepts", "application/json");

        Common::Request req = {
            url,
            headers
        };

        QObject::connect(requestPerformer, QOverload<const QJsonObject &>::of(&Common::RequestsPerformer::finished), this, &SpotDataStorage::onUpdateRequestFinished);
        QObject::connect(requestPerformer, &Common::RequestsPerformer::failed, this, [=](){
            qDebug() << "SpotDataStorage request failed";
            requestPerformer->deleteLater();
        });

        requestPerformer->perform(req);
        qDebug() << "SpotDataStorage::update called perform request for " << service->name();
    }
}


void SpotDataStorage::sort()
{
    qDebug() << "SpotDataStorage::sort()";
    m_dataFilter->sort(0, m_sortedAscending ? Qt::DescendingOrder : Qt::AscendingOrder);
    m_sortedAscending = !m_sortedAscending;
    emit itemsChanged();
}


void SpotDataStorage::clear()
{
    m_itemsMap.clear();
    m_listModel->clear();
}


SpotDataStorageModel *SpotDataStorage::listModel() const
{
    return m_listModel.get();
}


DataFilter *SpotDataStorage::dataFilter() const
{
    return m_dataFilter.get();
}


void SpotDataStorage::onUpdateRequestFinished(const QJsonObject &result)
{
    Common::RequestsPerformer * requestPerformer = qobject_cast<Common::RequestsPerformer *>(sender());

    addData(result);

    requestPerformer->disconnect();
    requestPerformer->deleteLater();
}


SpotDataStorageModel::SpotDataStorageModel()
{
//    QPair<QString, QString> coinsPair = { "baseId", "quoteId" };
//    append(SpotDataPtr::create(coinsPair));
}


int SpotDataStorageModel::rowCount(const QModelIndex &parent) const
{
    return m_list.count();
}


QVariant SpotDataStorageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_list.count())
        return QVariant();

    switch (role)
    {
    case ObjectRole:
        return QVariant::fromValue<QObject*>(m_list.at(index.row()).get());
    default:
        return QVariant();
    }
}


QHash<int, QByteArray> SpotDataStorageModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ObjectRole] = "object";

    return roles;
}


void SpotDataStorageModel::append(const SpotDataPtr &spotData)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_list.append(spotData);
    endInsertRows();
}


void SpotDataStorageModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    m_list.clear();
    endRemoveRows();
}


DataFilter::SortMode DataFilter::sortMode() const
{
    return m_sortMode;
}


void DataFilter::setSortMode(DataFilter::SortMode value)
{
    if (m_sortMode == value)
        return;

    m_sortMode = value;
    emit sortModeChanged();
}


bool DataFilter::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    auto leftObject = left.data(SpotDataStorageModel::ObjectRole).value<SpotData *>();
    auto rightObject = right.data(SpotDataStorageModel::ObjectRole).value<SpotData *>();

    if (!leftObject || !rightObject)
    {
        return left.row() < right.row();
    }

    switch (sortMode()) {
    case SortMode::BySpread:
        return leftObject->spread() < rightObject->spread();
    default:
        return left.row() < right.row();
    }
}
