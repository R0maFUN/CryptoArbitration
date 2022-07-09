#pragma once

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "Model/SettingsModel.h"

#include "Common/CommonDataStructures.h"


namespace ViewModel
{

class SettingsViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double minVolume READ minVolume WRITE setMinVolume NOTIFY minVolumeChanged)
    Q_PROPERTY(QList<Common::ServiceData* > services READ servicesQML CONSTANT)

public:
    SettingsViewModel();

    QList<QSharedPointer<Common::ServiceData> > services() const;
    QList<Common::ServiceData* > servicesQML() const;
    QSharedPointer<Common::ServiceData> serviceFromId(const QString &id);

    double minVolume() const;
    void setMinVolume(const double &value);

signals:
    void minVolumeChanged();

private:
    Model::SettingsModelPtr m_model;
};

using SettingsViewModelPtr = QSharedPointer<SettingsViewModel>;

} // ViewModel
