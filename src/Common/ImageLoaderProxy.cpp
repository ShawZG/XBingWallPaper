//
// Created by xiao on 2/14/22.
//

#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QImage>
#include <QDebug>
#include <QTimer>
#include <QDir>
#include <QFileInfo>

#include "HttpClient.h"
#include "CommonHelper.h"
#include "AppConfig.h"

#include "ImageLoaderProxy.h"

ImageLoaderProxy::ImageLoaderProxy(const QDate &date, QObject *parent) : QObject(parent), imageDate(date)
{
    if (imageDate.isValid()) {
        imageDirPath = translateImageDateToDirPath();
        imagePath = imageDirPath + "/" + imageDate.toString("yyyy_MM_dd") + ".jpg";
    }
}

void ImageLoaderProxy::getImageFromUrl()
{
    QSize screenSize = AppConfig::screenGeometry();
    QNetworkReply *reply = HttpClient::instance()->getImageUrlRequest(imageDate.daysTo(QDate::currentDate()),
                                                                      screenSize.width(), screenSize.height());
    connect(reply, &QNetworkReply::finished, this, &ImageLoaderProxy::parseImageUrlRequest);
}

void ImageLoaderProxy::parseImageUrlRequest()
{
    auto *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    reply->deleteLater();

    QJsonDocument doc;
    if (!HttpClient::validateReplay(reply, doc)) {
        return;
    }

    QJsonObject jsonObj = doc.object();
    if (!jsonObj.contains("status")) {
        return;
    }
    QJsonObject statusObj = jsonObj.value("status").toObject();
    if (!statusObj.contains("code") || HTTP_RESPONSE_OK != statusObj.value("code").toInt()) {
        return;
    }
    if (!jsonObj.contains("data")) {
        return;
    }
    QJsonObject dataObj = jsonObj.value("data").toObject();
    if (dataObj.contains("url")) {
        QString downloadUrl = dataObj.value("url").toString();
        if (!downloadUrl.isEmpty()) {
            QNetworkReply *reply = HttpClient::instance()->downloadImageRequest(downloadUrl);
            connect(reply, &QNetworkReply::finished, this, &ImageLoaderProxy::saveImage);
        }
    }
}

void ImageLoaderProxy::saveImage()
{
    auto *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    reply->deleteLater();

    auto imageSize = CommonHelper::parseUrlImageSize(reply->request().url().url());
    auto imageFormat = CommonHelper::parseUrlImageFormat(reply->request().url().url());
    if ( imageSize.width() > 0 && imageSize.height() > 0 && !imageFormat.isEmpty()) {
        image = QImage(imageSize.width(), imageSize.height(), QImage::Format_RGB32);
        auto result = image.loadFromData(reply->readAll(), imageFormat.toStdString().c_str());
        qDebug() << QString("download %1 image %2").arg(imageDate.toString()).arg(result);

        if (saveImageToLocalDir()) {
            QTimer::singleShot(0, [this] {emit sigLoadImageFromPath(imagePath);});
        } else {
            // TODO 发送默认图片路径
            QTimer::singleShot(0, [this] {emit sigLoadImageFromPath(imagePath);});
        }
    }
}

void ImageLoaderProxy::loadImage()
{
    if (imageDate.isValid()) {
        if (QFileInfo::exists(imagePath)) {
            QTimer::singleShot(0, [this] {emit sigLoadImageFromPath(imagePath);});
        } else {
            getImageFromUrl();
        }
    } else {
        // TODO 发送默认图片路径
    }
}

QString ImageLoaderProxy::translateImageDateToDirPath()
{
    return QString("%1/%2/%3").arg(AppConfig::getImageStorageDir()).arg(imageDate.toString("yyyy")).arg(imageDate.toString("MM"));
}

bool ImageLoaderProxy::saveImageToLocalDir()
{
    QDir dir;
    if (not dir.mkpath(imageDirPath)) {
        return false;
    }
    return image.save(imagePath, "jpg");
}