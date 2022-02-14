#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QScopedPointer>
#include <QJsonDocument>
#include <QNetworkReply>

#include "HttpClient.h"

Q_GLOBAL_STATIC(HttpClient, httpClient)

HttpClient::HttpClient(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
}

HttpClient::~HttpClient()
{
    delete manager;
}

HttpClient *HttpClient::instance()
{
    return httpClient;
}

bool HttpClient::validateReplay(QNetworkReply *reply, QJsonDocument &doc)
{
    if (QNetworkReply::NoError != reply->error()) {
#ifdef QT_DEBUG
        qDebug() << reply->request().url().url();
        qDebug() << reply->errorString();
#endif
        return false;
    }

    QByteArray jsonByte = reply->readAll();
#ifdef QT_DEBUG
    qDebug() << reply->request().url().url();
    qDebug() << QString(jsonByte);
#endif
    QJsonParseError jsonError;
    doc = QJsonDocument::fromJson(jsonByte, &jsonError);
    if (doc.isNull()) {
#ifdef QT_DEBUG
        qDebug() << reply->request().url().url();
        qDebug() << jsonError.errorString();
#endif
        return false;
    } else {
        return true;
    }
}

QNetworkReply *HttpClient::getImageUrlRequest(qint64 distanceDay, int width, int height)
{
    //https://bing.ioliu.cn/v1/?type=json&d=3
    //https://bing.ioliu.cn/v1/?d=1&w=1920&h=1080
    //https://bing.ioliu.cn/v1/rand?w=1920&h=1200
    QString url = QString("https://bing.ioliu.cn/v1/?type=json&d=%1&w=%2&h=%3").arg(distanceDay).arg(width).arg(height);
    return manager->get(QNetworkRequest(url));
}

QNetworkReply *HttpClient::downloadImageRequest(QString url)
{
    return manager->get(QNetworkRequest(url));
}
