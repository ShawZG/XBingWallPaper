#include <QApplication>
#include <QScreen>
#include "AppConfig.h"


QSize AppConfig::screenSize = QSize();


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

