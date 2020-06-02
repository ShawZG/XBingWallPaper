#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QObject>
#include <QSize>

class QSettings;

class AppConfig : public QObject
{
    Q_OBJECT
public:
    explicit AppConfig(QObject *parent = nullptr);

    static QString  getAppVersion();
    static QSize    screenGeometry();
    static void     setImageNumPerRowInListView(int num);
    static int      getImageNumPerRowInListView();

private:
    static void        loadConfig();
    static QVariant    getConfig(QString key, QVariant defaultValue);
    static void        setConfig(QString key, QVariant value);

    static QSettings    *setting;
    static QString      appVer;
    static QSize        screenSize;
    static int          defaultImageNumPerRow;
};

#endif // APPCONFIG_H
