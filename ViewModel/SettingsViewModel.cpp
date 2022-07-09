#include "SettingsViewModel.h"

#include "Model/SettingsModel.h"


using namespace ViewModel;


SettingsViewModel::SettingsViewModel()
    : m_model(Model::SettingsModelPtr::create())
{
    connect(m_model.get(), &Model::SettingsModel::minVolumeChanged, this, &SettingsViewModel::minVolumeChanged);
}


QList<QSharedPointer<Common::ServiceData> > SettingsViewModel::services() const
{
    return m_model->services();
}


QList<Common::ServiceData *> SettingsViewModel::servicesQML() const
{
    auto servicesList = services();
    QList<Common::ServiceData *> result;

    for (const auto &service : servicesList)
        result.append(service.get());

    return result;
}


QSharedPointer<Common::ServiceData> SettingsViewModel::serviceFromId(const QString &id)
{
    return m_model->serviceFromId(id);
}


double SettingsViewModel::minVolume() const
{
    return m_model->minVolume();
}


void SettingsViewModel::setMinVolume(const double &value)
{
    m_model->setMinVolume(value);
}
