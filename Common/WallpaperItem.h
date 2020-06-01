#ifndef WALLPAPERITEM_H
#define WALLPAPERITEM_H

#include <QDate>
#include <QObject>

class WallpaperItem : public QObject
{
    Q_OBJECT
public:
    explicit WallpaperItem(QDate date, QObject *parent = nullptr);

private slots:
    void parseWallpaperUrlRequest();
    void saveWallpaper();

private:
    void getWallpaperUrlRequest();
    void downloadWallpaperRequest();

    QDate   wallpaperData;
    int     distanceToday = -1;
    QImage  *wallpaper = nullptr;
};

#endif // WALLPAPERITEM_H
