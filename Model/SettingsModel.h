#pragma once

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "Common/CommonDataStructures.h"

namespace Model
{

class SettingsModel : public QObject
{
    Q_OBJECT
public:
    SettingsModel();

    QList<QSharedPointer<Common::ServiceData>> services() const;
    QSharedPointer<Common::ServiceData> serviceFromId(const QString &id);

    double minVolume() const;
    void setMinVolume(const double &value);

signals:
    void minVolumeChanged();

private:
    QList<QSharedPointer<Common::ServiceData>> m_services;

    double m_minVolume = 5000;
};

using SettingsModelPtr = QSharedPointer<SettingsModel>;

} // Model
