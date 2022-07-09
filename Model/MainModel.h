#pragma once

#include <QObject>
#include <QNetworkAccessManager>

namespace Model
{

class MainModel
{
public:
    MainModel();

    static QNetworkAccessManager * networkAccessManager();

private:
    QNetworkAccessManager * m_networkAccessManager;
};

} // Model
