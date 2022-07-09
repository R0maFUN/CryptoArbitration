#pragma once

#include <QObject>
#include <QUrl>
#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

namespace Common
{

using ReplyPtr = QSharedPointer<QNetworkReply>;

enum class RequestMethod
{
    GET,
    POST
};

struct Request
{
    QUrl url;
    QMap<QString, QString> headers;
    QJsonObject data;
    RequestMethod method;
};

// this should be pure c++ class, but im using only qt for this project
class RequestsPerformer : public QObject
{
    Q_OBJECT
public:
    RequestsPerformer();

    bool perform(const Request &req);

protected slots:
    void onFinished();
    void onFailed();

signals:
    void finished(const QJsonObject &replyJson); // mb QString
    void finished(const QString &rawReply);
    void failed();

private:
    QList<QNetworkReply *> m_replies;
};

} // Common
