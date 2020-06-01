#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QObject>
#include <QSize>

class AppConfig : public QObject
{
    Q_OBJECT
public:
    explicit AppConfig(QObject *parent = nullptr);

    static QSize screenGeometry();

private:
    static QSize screenSize;
};

#endif // APPCONFIG_H
