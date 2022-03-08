#include <QImageReader>
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
    QImageReader imageReader(imagePath);
    imageReader.setScaledSize(QSize(480, 270));
    image = QPixmap::fromImageReader(&imageReader);
    loadingImageResult = !image.isNull();
}

