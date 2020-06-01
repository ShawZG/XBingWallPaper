#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include "HttpClient.h"
#include "CommonHelper.h"
#include "AppConfig.h"
#include "WallpaperItem.h"

WallpaperItem::WallpaperItem(QDate date, QObject *parent) : QObject(parent), wallpaperData(date)
{
    if (true == wallpaperData.isValid()){
        distanceToday = wallpaperData.daysTo(QDate::currentDate());
    }
    getWallpaperUrlRequest();
}

void WallpaperItem::getWallpaperUrlRequest()
{
    QSize screenSize = AppConfig::screenGeometry();
    QNetworkReply *reply = HttpClient::instance()->getBingWallpaperUrlRequest(distanceToday, screenSize.width(), screenSize.height());

    connect(reply, &QNetworkReply::finished, this, &WallpaperItem::parseWallpaperUrlRequest);
}

void WallpaperItem::parseWallpaperUrlRequest()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    reply->deleteLater();

    QJsonDocument doc;
    if (false == HttpClient::validateReplay(reply, doc)) {
        return;
    }

    QJsonObject jsonObj = doc.object();
    if ( false == jsonObj.contains("status")){
        return;
    }
    QJsonObject statusObj = jsonObj.value("status").toObject();
    if (false == statusObj.contains("code") || HTTP_RESPONSE_OK != statusObj.value("code").toInt()){
        return;
    }
    if ( false == jsonObj.contains("data")){
        return;
    }
    QJsonObject dataObj = jsonObj.value("data").toObject();
    if (true == dataObj.contains("url")){
        QString downloadUrl = dataObj.value("url").toString();
        if ( false == downloadUrl.isEmpty()){
             QNetworkReply *reply = HttpClient::instance()->downloadWallpaperRequest(downloadUrl);
             connect(reply, &QNetworkReply::finished, this, &WallpaperItem::saveWallpaper);
        }
    }
}

void WallpaperItem::saveWallpaper()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());

    QSize imageSize = CommonHelper::parseUrlImageSize(reply->request().url().url());

}
