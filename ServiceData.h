#pragma once

#include <QObject>
#include <QSharedPointer>

#include "P2PData.h"
#include "SpotData.h"
#include "CommonDataStructures.h"

class ServiceData : QObject
{
    Q_OBJECT
public:
    ServiceData();

private:
    SpotDataPtr m_spotData;
    P2PDataPtr m_p2pData;
    QString m_serviceName;
};
