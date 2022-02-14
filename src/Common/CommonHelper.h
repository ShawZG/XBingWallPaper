#ifndef COMMONHELPER_H
#define COMMONHELPER_H

#include <QObject>

class CommonHelper : public QObject
{
    Q_OBJECT
public:
    explicit CommonHelper(QObject *parent = nullptr);

    static void     setStyle(const QString &stylePath);

    static bool     getJsonValue(QJsonObject obj, QString key, QVariant &value);
    static QSize    parseUrlImageSize(const QString& url);
    static QString  parseUrlImageFormat(const QString& url);

    static QDir     createWallpaperDir(const QDate &imageDate);
    static QString  translateImageDateToDir(const QDate &imageDate);
};

#endif // COMMONHELPER_H
