//
// Created by xiao on 22-12-20.
//

#ifndef XBINGWALLPAPER_AUTOUPDATEWALLPAPERAGENT_H
#define XBINGWALLPAPER_AUTOUPDATEWALLPAPERAGENT_H

#include <QObject>
#include <QDate>

class AutoUpdateWallpaperAgent: public QObject
{
    Q_OBJECT
public:
    void tryUpdateWallpaper(const QDate &date);

private slots:
    void slotSetWallpaper(const QString &imagePath);

signals:
    void sigUpdateWallpaperFinished(bool result);
};


#endif //XBINGWALLPAPER_AUTOUPDATEWALLPAPERAGENT_H
