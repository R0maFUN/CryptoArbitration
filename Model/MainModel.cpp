#include "MainModel.h"

using namespace Model;

MainModel::MainModel()
{
    delete networkAccessManager();
}


QNetworkAccessManager * MainModel::networkAccessManager()
{
    static QNetworkAccessManager * manager = new QNetworkAccessManager();

    return manager;
}
