#pragma once

#include <QtCore/QAbstractItemModel>
#include <QtCore/QPointer>

namespace Common
{

class ListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    using List = QList< QSharedPointer<QObject> >;

    enum Role { ObjectRole = Qt::UserRole + 1 };
    Q_ENUM(Role)

    template<class T>
    ListModel(T* &&list)
        : m_list(std::forward<T*>(list))
    {

    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const final;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int,QByteArray> roleNames() const override;

protected:
    List * m_list;
};

} // Common
