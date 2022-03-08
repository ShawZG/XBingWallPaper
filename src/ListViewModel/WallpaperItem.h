#ifndef WALLPAPERITEM_H
#define WALLPAPERITEM_H

#include <QDate>
#include <QObject>
#include <QPixmap>

class WallpaperItem : public QObject
{
    Q_OBJECT
public:
    explicit WallpaperItem(QDate date, QObject *parent = nullptr);

    QPixmap image;
    QString imageFilePath;
    bool    loadingImageResult = false;

private slots:
    void loadImageFromLocal(const QString &imagePath);
};

//Q_DECLARE_METATYPE(WallpaperItem)

#endif // WALLPAPERITEM_H
