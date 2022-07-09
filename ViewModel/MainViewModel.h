#pragma once

#include <memory>

#include <QObject>
#include <QDebug>
#include <QSharedPointer>

#include "Common/RequestsPerformer.h"

#include "ViewModel/SpotDataStorage.h"
#include "ViewModel/SettingsViewModel.h"


namespace ViewModel
{

class MainViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SpotDataStorage * spotData READ spotDataStorage CONSTANT)
    Q_PROPERTY(SettingsViewModel * settings READ settings CONSTANT)

public:
    MainViewModel();

    SpotDataStorage * spotDataStorage() const;
    SettingsViewModel * settings() const;


private:
    QSharedPointer<Common::RequestsPerformer> m_requestsPerformer;
    SettingsViewModelPtr m_settings;
    QSharedPointer<SpotDataStorage> m_spotData;
};

} // ViewModel
