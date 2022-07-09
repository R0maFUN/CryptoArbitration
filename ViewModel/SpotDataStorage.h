#pragma once

#include <memory>

#include <QObject>
#include <QList>
#include <QAbstractListModel>
#include <QSortFilterProxyModel>

#include "Common/RequestsPerformer.h"
#include "Common/ListModel.h"

#include "ViewModel/SpotData.h"
#include "ViewModel/SettingsViewModel.h"

namespace ViewModel
{

class SpotDataStorageModel : public QAbstractListModel
{
    Q_OBJECT
public:
    using List = QList<SpotDataPtr>;

    enum Role { ObjectRole = Qt::UserRole + 1 };
    Q_ENUM(Role)

    SpotDataStorageModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const final;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int,QByteArray> roleNames() const override;

    void append(const SpotDataPtr &spotData);
    void clear();

protected:
    List m_list;
};

class DataFilter : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    enum SortMode { BySpread };
    Q_ENUM(SortMode)

    explicit DataFilter() = default;

    SortMode sortMode() const;
    void setSortMode(SortMode value);

signals:
    void sortModeChanged();

private:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const final;
    // bool filterAcceptsRow(int row, const QModelIndex &parent) const final;

protected:
    SortMode m_sortMode = SortMode::BySpread;
};

class SpotDataStorage : public QObject // QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(DataFilter * items READ dataFilter NOTIFY itemsChanged)

public:
    SpotDataStorage(const SettingsViewModelPtr &settings);

    void addData(const QJsonObject &json);
    Q_INVOKABLE void update();
    Q_INVOKABLE void sort();
    void clear();

    SpotDataStorageModel * listModel() const;
    DataFilter * dataFilter() const;

signals:
    void itemsChanged();

protected slots:
    void onUpdateRequestFinished(const QJsonObject &result);

private:
    //QSharedPointer<QList<SpotDataPtr>> m_items;
    QSharedPointer<SpotDataStorageModel> m_listModel;
    QSharedPointer<DataFilter> m_dataFilter;
    SettingsViewModelPtr m_settings;
    QMap<QPair<QString, QString>, SpotDataPtr> m_itemsMap;
    bool m_sortedAscending = false;
    //std::unique_ptr<Common::RequestsPerformer> m_requestsPerformer;
};

} // ViewModel

