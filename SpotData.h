#pragma once

#include <QObject>
#include <QSharedPointer>

class SpotData
{
public:
    SpotData();
};

using SpotDataPtr = QSharedPointer<SpotData>;
