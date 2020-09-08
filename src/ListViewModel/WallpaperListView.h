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
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

private slots:
    void slotShowMenu(const QPoint &pos);
    void slotShowPreview(const QModelIndex &index);

private:
    void initListView();
    void initConnect();
    void loadImages(int row);
    void initTimer();
    void updateGridSize();
    void initMenu();

    QStandardItemModel *itemModel = nullptr;
    QDate               earliestData = QDate::currentDate() ;
    QTimer              *updateTimer = nullptr;
    QMenu               *menu = nullptr;

};

#endif // WALLPAPERLISTVIEW_H
