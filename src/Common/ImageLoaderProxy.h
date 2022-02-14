//
// Created by xiao on 2/14/22.
//

#ifndef XBINGWALLPAPER_IMAGEPROXY_H
#define XBINGWALLPAPER_IMAGEPROXY_H

#include <QDate>
#include <QObject>

class WallpaperItem;

class ImageLoaderProxy: public QObject {
    Q_OBJECT
public:
    explicit ImageLoaderProxy(const QDate &date, QObject *parent = nullptr);
    void loadImage();

signals:
    void sigLoadImageFromPath(const QString imagePath);

private:
    QString translateImageDateToDirPath();
    void getImageFromUrl();
    void parseImageUrlRequest();
    void saveImage();
    bool saveImageToLocalDir();

    QImage image;
    QDate imageDate;
    QString imageDirPath;
    QString imagePath;
};

#endif //XBINGWALLPAPER_IMAGEPROXY_H
