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
    static QSize    parseUrlImageSize(QString url);
    static QString  parseUrlImageFormat(QString url);
};

#endif // COMMONHELPER_H
