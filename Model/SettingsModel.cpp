#include "SettingsModel.h"


using namespace Model;

SettingsModel::SettingsModel()
    : m_services(Common::CoinCap::availableServices())
{

}


QList<QSharedPointer<Common::ServiceData> > SettingsModel::services() const
{
    return m_services;
}


QSharedPointer<Common::ServiceData> SettingsModel::serviceFromId(const QString &id)
{
    auto it = std::find_if(m_services.begin(), m_services.end(),
                           [=](const QSharedPointer<Common::ServiceData> &item){
        return item->id() == id;
    });

    if (it != m_services.end())
        return *it;
    else
        return QSharedPointer<Common::ServiceData>();
}


double SettingsModel::minVolume() const
{
    return m_minVolume;
}


void SettingsModel::setMinVolume(const double &value)
{
    if (m_minVolume == value)
        return;

    m_minVolume = value;

    emit minVolumeChanged();
}
