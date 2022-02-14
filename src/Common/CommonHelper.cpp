#include <QJsonObject>
#include <QVariant>
#include <QSize>
#include <QFile>
#include <QDate>
#include <QDir>
#include <QApplication>

#include "CommonHelper.h"

#include "AppConfig.h"

CommonHelper::CommonHelper(QObject *parent) : QObject(parent)
{

}

void CommonHelper::setStyle(const QString &stylePath)
{
    QFile qss(stylePath);
    if (qss.open(QFile::ReadOnly)) {
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
}

bool CommonHelper::getJsonValue(QJsonObject obj, QString key, QVariant &value)
{
    if (obj.isEmpty() || key.isEmpty()) {
        return false;
    }

    if (obj.contains(key)) {
        value = obj.value(key).toVariant();
        return true;
    } else {
        return false;
    }
}

QSize CommonHelper::parseUrlImageSize(const QString& url)
{
    //https://www4.bing.com/az/hprichbg/rb/GreatReefDay_ZH-CN1185297376_1920x1080.jpg
    int dot = url.lastIndexOf(QChar('.'));
    int underline = url.lastIndexOf(QChar('_'));
    QStringList sizeList = url.mid(underline + 1, dot - underline - 1).split(QChar('x'));

    return {sizeList.at(0).toInt(), sizeList.at(1).toInt()};
}

QString CommonHelper::parseUrlImageFormat(const QString& url)
{
    //https://www4.bing.com/az/hprichbg/rb/GreatReefDay_ZH-CN1185297376_1920x1080.jpg
    int dot = url.lastIndexOf(QChar('.'));
    QString format = url.mid(dot + 1).toUpper();
    return format;
}

QString CommonHelper::translateImageDateToDir(const QDate &imageDate){
    auto imageDir = QString("%1/%2/%3").arg(AppConfig::getImageStorageDir()).arg(imageDate.toString("MM")).arg(imageDate.toString("dd"));
}

QDir CommonHelper::createWallpaperDir(const QDate &imageDate){
    if (not imageDate.isValid()) {
        return {};
    }

    auto imageFileName = imageDate.toString("yyyy_MM_dd") + ".jpg";
    auto imageDir = QString("%1/%2/%3").arg(AppConfig::getImageStorageDir()).arg(imageDate.toString("MM")).arg(imageDate.toString("dd"));
}