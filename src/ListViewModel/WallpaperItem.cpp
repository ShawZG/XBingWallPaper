#include <QImage>
#include <QDebug>
#include "ImageLoaderProxy.h"
#include "WallpaperItem.h"

WallpaperItem::WallpaperItem(QDate date, QObject *parent) : QObject(parent)
{
    auto imageLoaderProxy = new ImageLoaderProxy(date);
    connect(imageLoaderProxy, &ImageLoaderProxy::sigLoadImageFromPath, this, &WallpaperItem::loadImageFromLocal);
    connect(imageLoaderProxy, &ImageLoaderProxy::sigLoadImageFromPath, imageLoaderProxy, &ImageLoaderProxy::deleteLater);
    imageLoaderProxy->loadImage();
}

void WallpaperItem::loadImageFromLocal(const QString &imagePath) {
    imageFilePath = imagePath;
    loadingImageResult = image.load(imagePath);
}

WallpaperItem::WallpaperItem(const WallpaperItem &item) {
    imageFilePath = item.imageFilePath;
    image = item.image;
    loadingImageResult = item.loadingImageResult;
}
