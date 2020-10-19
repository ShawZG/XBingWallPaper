#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QImage>
#include <QDebug>

#include "HttpClient.h"
#include "CommonHelper.h"
#include "AppConfig.h"

#include "WallpaperItem.h"

WallpaperItem::WallpaperItem(QDate date, QObject *parent) : QObject(parent), imageData(date)
{
    if (true == imageData.isValid()) {
        distanceToday = imageData.daysTo(QDate::currentDate());
    }
    getWallpaperUrlRequest();
    //loadImageFromFile();
}

WallpaperItem::WallpaperItem()
{
}

WallpaperItem::WallpaperItem(const WallpaperItem &item)
{
    distanceToday = item.distanceToday;
    imageData = item.imageData;
    imageSize = item.imageSize;
    imageFormat = item.imageFormat;
    imageLoadResult = item.imageLoadResult;

    if ( imageSize.width() > 0 && imageSize.height() > 0 &&  nullptr != item.image ) {
        image = new QImage(*(item.image));
    }
}

WallpaperItem::~WallpaperItem()
{
    if (nullptr != image) {
        delete image;
    }
}

void WallpaperItem::getWallpaperUrlRequest()
{
    QSize screenSize = AppConfig::screenGeometry();
    QNetworkReply *reply = HttpClient::instance()->getBingWallpaperUrlRequest(distanceToday, screenSize.width(), screenSize.height());

    connect(reply, &QNetworkReply::finished, this, &WallpaperItem::parseWallpaperUrlRequest);
}

void WallpaperItem::parseWallpaperUrlRequest()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    reply->deleteLater();

    QJsonDocument doc;
    if (false == HttpClient::validateReplay(reply, doc)) {
        return;
    }

    QJsonObject jsonObj = doc.object();
    if ( false == jsonObj.contains("status")) {
        return;
    }
    QJsonObject statusObj = jsonObj.value("status").toObject();
    if (false == statusObj.contains("code") || HTTP_RESPONSE_OK != statusObj.value("code").toInt()) {
        return;
    }
    if ( false == jsonObj.contains("data")) {
        return;
    }
    QJsonObject dataObj = jsonObj.value("data").toObject();
    if (true == dataObj.contains("url")) {
        QString downloadUrl = dataObj.value("url").toString();
        if ( false == downloadUrl.isEmpty()) {
            QNetworkReply *reply = HttpClient::instance()->downloadWallpaperRequest(downloadUrl);
            connect(reply, &QNetworkReply::finished, this, &WallpaperItem::saveWallpaper);
        }
    }
}

void WallpaperItem::saveWallpaper()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    reply->deleteLater();

    imageSize = CommonHelper::parseUrlImageSize(reply->request().url().url());
    imageFormat = CommonHelper::parseUrlImageFormat(reply->request().url().url());
    if ( imageSize.width() > 0 && imageSize.height() > 0 && true != imageFormat.isEmpty()) {
        image = new QImage(imageSize.width(), imageSize.height(), QImage::Format_RGB32);
        imageLoadResult = image->loadFromData(reply->readAll(), imageFormat.toStdString().c_str());
        qDebug() << QString("download %1 image %2").arg(imageData.toString()).arg(imageLoadResult);
    }
}

void WallpaperItem::loadImageFromFile()
{
    image = new QImage("/home/xiaozhiguo/Colorful-Abstraction02.jpeg");
    imageLoadResult = true;
    imageSize = image->size();
}
