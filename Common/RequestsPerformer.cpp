#include "RequestsPerformer.h"

#include <QJsonDocument>

#include <QFile>
#include <QTextStream>

#include "Model/MainModel.h" // mb remove it from here

using namespace Common;


RequestsPerformer::RequestsPerformer()
{

}


bool RequestsPerformer::perform(const Request &req)
{
    qDebug() << "RequestsPerformer::perform url = " << req.url;
    QNetworkRequest request;
    request.setUrl(req.url);

    for (const auto &key : req.headers.keys())
    {
        request.setRawHeader(key.toUtf8(), req.headers.value(key).toUtf8());
    }

    request.setRawHeader("User-Agent", "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.101 Mobile Safari/537.36");

    qDebug() << "RequestsPerformer::perform getting reply for " << req.url;
    QNetworkAccessManager * am = new QNetworkAccessManager();

    QNetworkReply * reply = /*Model::MainModel::networkAccessManager()*/am->get(request);
    m_replies.append(reply);

    qDebug() << "RequestsPerformer::perform connecting reply for " << req.url;
    //connect(reply, &QIODevice::readyRead, this, &RequestsPerformer::onFinished);
    //connect(reply, &QNetworkReply::finished, this, &RequestsPerformer::onFinished);
    //connect(reply, &QNetworkReply::errorOccurred, this, &RequestsPerformer::onFailed);
    qDebug() << "RequestsPerformer::perform done for " << req.url;
}


void RequestsPerformer::onFinished()
{
    qDebug() << "RequestsPerformer::onFinished";
    QNetworkReply * reply = qobject_cast<QNetworkReply *>(sender());

    QString rawReply = reply->readAll();
    qDebug() << "RequestsPerformer::onFinished, url = " << reply->url();
    //qDebug() << "rawReply = " << rawReply;
    QJsonObject json = QJsonDocument::fromJson(rawReply.toUtf8()).object();

    //qDebug() << "reply = " << QString(QJsonDocument(json).toJson(QJsonDocument::Indented));

    QString filePath = "./tst.json";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << QString("Failed to open \'%1\'.").arg(filePath);
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << QString(QJsonDocument(json).toJson(QJsonDocument::Indented));
    file.close();

    qDebug() << "json.isEmpty() = " << json.isEmpty();

    if (json.isEmpty())
        emit finished(rawReply);
    else
        emit finished(json);

    reply->deleteLater();
}


void RequestsPerformer::onFailed()
{
    qDebug() << "RequestsPerformer::onFailed";
    QNetworkReply * reply = qobject_cast<QNetworkReply *>(sender());

    qDebug() << "Request failed";

    reply->deleteLater();
}
