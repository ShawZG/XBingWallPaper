#include <QApplication>
#include <QScreen>
#include <QSettings>
#include "AppConfig.h"

QString     AppConfig::appVer = "1.0.0";
QSettings  *AppConfig::setting = nullptr;
QSize       AppConfig::screenSize = QSize(1920, 1080);

int         AppConfig::defaultImageNumPerRow = 4;
int         AppConfig::initShowImageRowNum = 2;

AppConfig::AppConfig(QObject *parent) : QObject(parent)
{
}

QSize AppConfig::screenGeometry()
{
    if (false == AppConfig::screenSize.isValid()) {
        QRect rect = QApplication::primaryScreen()->geometry();
        AppConfig::screenSize.setWidth(rect.width());
        AppConfig::screenSize.setHeight(rect.height());
    }
    return AppConfig::screenSize;
}

int AppConfig::getInitShowImageRowNum()
{
    return AppConfig::initShowImageRowNum;
}

void AppConfig::setImageNumPerRowInListView(int num)
{
    AppConfig::setConfig("ImageNumPerRow", num);
}

int AppConfig::getImageNumPerRowInListView()
{
    return AppConfig::getConfig("ImageNumPerRow", AppConfig::defaultImageNumPerRow).toInt();
}

QString AppConfig::getAppVersion()
{
    return AppConfig::appVer;
}

void AppConfig::loadConfig()
{
    /*
    do not need function saveConfig, because QSettings::sync() is called automatically from QSettings's destructor
    and by the event loop at regular intervals, so you normally don't need to call it yourself.
    QSettings::sync() Writes any unsaved changes to permanent storage, and reloads any settings
    that have been changed in the meantime by another application.
    */
    AppConfig::setting = new QSettings("xbingwallpaper.config", QSettings::NativeFormat);
}

QVariant AppConfig::getConfig(QString key, QVariant defaultValue)
{
    if (nullptr == AppConfig::setting) {
        AppConfig::loadConfig();
    }
    return AppConfig::setting->value(key, defaultValue);
}

void AppConfig::setConfig(QString key, QVariant value)
{
    if (nullptr == AppConfig::setting) {
        AppConfig::loadConfig();
    }
    AppConfig::setting->setValue(key, value);
    AppConfig::setting->sync();
}



