#include "ListModel.h"

using namespace Common;


namespace
{
constexpr auto objectRole = "object";
} // Anonymous


//ListModel::ListModel(QList< QSharedPointer<QObject> > * list)
//    : m_list(list)
//{

//}

int ListModel::rowCount(const QModelIndex &parent) const
{
    return m_list->count();
}


QVariant ListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_list->count())
        return QVariant();

    switch (role)
    {
    case ObjectRole:
        return QVariant::fromValue<QObject*>(m_list->at(index.row()).get());
    default:
        return QVariant();
//        default:
//        {
//            auto propertyIndex = role - ObjectRole - 1;
//            if (propertyIndex < 0 || propertyIndex >= m_properties.count())
//                return QVariant();
//            return m_list->at(index.row())->property(m_properties[propertyIndex].toLatin1());
//        }
    }
}

QHash<int, QByteArray> ListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ObjectRole] = objectRole;

//    int role = ObjectRole + 1;
//    for (auto &property : m_properties)
//    {
//        roles[role] = property.toLatin1();
//        ++role;
//    }

    return roles;
}
