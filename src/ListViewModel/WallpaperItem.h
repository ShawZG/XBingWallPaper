#ifndef WALLPAPERITEM_H
#define WALLPAPERITEM_H

#include <QDate>
#include <QObject>

class WallpaperItem : public QObject
{
    Q_OBJECT
public:
    explicit WallpaperItem(QDate date, QObject *parent = nullptr);
    WallpaperItem(const WallpaperItem& item);

    QImage  image;
    bool    loadingImageResult = false;

private slots:
    void loadImageFromLocal(const QString &imagePath);
};

//Q_DECLARE_METATYPE(WallpaperItem)

#endif // WALLPAPERITEM_H
