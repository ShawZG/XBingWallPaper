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

protected:
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);

private:
    void initListView();
    void initConnect();
    void loadImages(int row);
    void initTimer();
    void updateGridSize();

    QStandardItemModel *itemModel = nullptr;
    QDate               earliestData = QDate::currentDate() ;
    QTimer              *updateTimer = nullptr;

};

#endif // WALLPAPERLISTVIEW_H
