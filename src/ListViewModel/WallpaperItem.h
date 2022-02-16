#ifndef WALLPAPERITEM_H
#define WALLPAPERITEM_H

#include <QDate>
#include <QObject>
#include <QImage>

class WallpaperItem : public QObject
{
    Q_OBJECT
public:
    explicit WallpaperItem(QDate date, QObject *parent = nullptr);

    QImage  image;
    QString imageFilePath;
    bool    loadingImageResult = false;

private slots:
    void loadImageFromLocal(const QString &imagePath);
};

//Q_DECLARE_METATYPE(WallpaperItem)

#endif // WALLPAPERITEM_H
