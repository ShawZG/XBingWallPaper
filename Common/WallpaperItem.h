#ifndef WALLPAPERITEM_H
#define WALLPAPERITEM_H

#include <QDate>
#include <QObject>
#include <QSize>

class WallpaperItem : public QObject
{
    Q_OBJECT
public:
    explicit WallpaperItem(QDate date, QObject *parent = nullptr);
    WallpaperItem();
    WallpaperItem(const WallpaperItem &item);
    ~WallpaperItem();

    qint64  distanceToday = -1;
    QDate   imageData = QDate();
    QImage  *image = nullptr;
    QSize   imageSize = QSize(0, 0);
    QString imageFormat = QString();
    bool    imageLoadResult = false;

private slots:
    void parseWallpaperUrlRequest();
    void saveWallpaper();

private:
    void getWallpaperUrlRequest();
    void downloadWallpaperRequest();
};

Q_DECLARE_METATYPE(WallpaperItem)

#endif // WALLPAPERITEM_H
