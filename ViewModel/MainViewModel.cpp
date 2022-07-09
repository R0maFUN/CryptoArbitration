#include "MainViewModel.h"

#include <QtGlobal>
#include <QSharedPointer>
#include <QUrlQuery>

#include "Model/MainModel.h"

using namespace ViewModel;


template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


MainViewModel::MainViewModel()
    : m_requestsPerformer(QSharedPointer<Common::RequestsPerformer>::create())
    , m_settings(SettingsViewModelPtr::create())
    , m_spotData(QSharedPointer<SpotDataStorage>::create(m_settings))
{

}


SpotDataStorage * MainViewModel::spotDataStorage() const
{
    return m_spotData.get();
}


SettingsViewModel *MainViewModel::settings() const
{
    return m_settings.get();
}
