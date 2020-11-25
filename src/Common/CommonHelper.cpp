#include <QJsonObject>
#include <QVariant>
#include <QSize>
#include <QFile>
#include <QApplication>

#include "CommonHelper.h"

CommonHelper::CommonHelper(QObject *parent) : QObject(parent)
{

}

void CommonHelper::setStyle(const QString &stylePath)
{
    QFile qss(stylePath);
    if (true == qss.open(QFile::ReadOnly)) {
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
}

bool CommonHelper::getJsonValue(QJsonObject obj, QString key, QVariant &value)
{
    if (true == obj.isEmpty() || true == key.isEmpty()) {
        return false;
    }

    if (true == obj.contains(key)) {
        value = obj.value(key).toVariant();
        return true;
    } else {
        return false;
    }
}

QSize CommonHelper::parseUrlImageSize(QString url)
{
    //https://www4.bing.com/az/hprichbg/rb/GreatReefDay_ZH-CN1185297376_1920x1080.jpg
    int dot = url.lastIndexOf(QChar('.'));
    int underline = url.lastIndexOf(QChar('_'));
    QStringList sizeList = url.mid(underline + 1, dot - underline - 1).split(QChar('x'));

    return QSize(sizeList.at(0).toInt(), sizeList.at(1).toInt());
}

QString CommonHelper::parseUrlImageFormat(QString url)
{
    //https://www4.bing.com/az/hprichbg/rb/GreatReefDay_ZH-CN1185297376_1920x1080.jpg
    int dot = url.lastIndexOf(QChar('.'));
    QString format = url.mid(dot + 1).toUpper();
    return format;
}
