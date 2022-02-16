#include <QJsonObject>
#include <QVariant>
#include <QSize>
#include <QFile>
#include <QDate>
#include <QDir>
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QDBusInterface>
#include <QUrl>

#include "AppConfig.h"

#include "CommonHelper.h"

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

bool CommonHelper::copyFileToDir(const QString &filePath, const QString &dirPath)
{
    QFileInfo fileInfo(filePath);
    return QFile::copy(filePath, dirPath + "/" + fileInfo.fileName());
}

void CommonHelper::setDesktopWallpaper(const QString &wallpaperPath)
{
    auto screen = QGuiApplication::screenAt( QCursor::pos());

    QString service = "com.deepin.daemon.Appearance";
    QString path = "/com/deepin/daemon/Appearance";
    QString interfaceName = "com.deepin.daemon.Appearance";
    QDBusInterface interface(service, path,interfaceName);
    //NOTE 文件的路径格式形如file:///home/user/file.txt，故用QUrl转换
    interface.call("SetMonitorBackground",screen->name(),QUrl::fromLocalFile(wallpaperPath).toLocalFile());
}