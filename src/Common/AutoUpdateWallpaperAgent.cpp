//
// Created by xiao on 22-12-20.
//

#include "AutoUpdateWallpaperAgent.h"
#include <QImageReader>
#include <QDebug>
#include "ImageLoaderProxy.h"
#include "WallpaperItem.h"
#include "CommonHelper.h"
#include "QFileInfo"

void AutoUpdateWallpaperAgent::tryUpdateWallpaper(const QDate &date)
{
    auto imageLoaderProxy = new ImageLoaderProxy(date);
    connect(imageLoaderProxy, &ImageLoaderProxy::sigLoadImageFromPath, this, &AutoUpdateWallpaperAgent::slotSetWallpaper);
    connect(imageLoaderProxy, &ImageLoaderProxy::sigLoadImageFromPath, imageLoaderProxy, &ImageLoaderProxy::deleteLater);
    imageLoaderProxy->loadImage();
}

void AutoUpdateWallpaperAgent::slotSetWallpaper(const QString &imagePath)
{
    if (!QFileInfo::exists(imagePath)) {
        emit sigUpdateWallpaperFinished(false);
        return;
    }

    CommonHelper::setDesktopWallpaper(imagePath);
    emit sigUpdateWallpaperFinished(true);
}
