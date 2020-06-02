#ifndef WALLPAPERLISTVIEW_H
#define WALLPAPERLISTVIEW_H

#include <QListView>
#include <QDate>

class QStandardItemModel;

class WallpaperListView : public QListView
{
    Q_OBJECT
public:
    explicit WallpaperListView(QWidget *parent = nullptr);

private:
    void initListView();
    void initLoadImage(int row);
    void initTimer();

    QStandardItemModel *itemModel = nullptr;
    QDate               earliestData = QDate::currentDate() ;
    QTimer              *updateTimer = nullptr;

};

#endif // WALLPAPERLISTVIEW_H
