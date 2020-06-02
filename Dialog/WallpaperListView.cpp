#include <QStandardItem>
#include <QVariant>
#include <QTimer>

#include <QStandardItemModel>
#include "Common/WallpaperItem.h"
#include "Common/AppConfig.h"
#include "WallpaperItemDelegate.h"
#include "WallpaperListView.h"

WallpaperListView::WallpaperListView(QWidget *parent) : QListView(parent)
{
    initListView();
    initLoadImage(1);
    initTimer();
}

void WallpaperListView::initListView()
{
    setViewMode(QListView::IconMode);
    setResizeMode(QListView::Adjust);
    setMovement(QListView::Static);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setItemAlignment(Qt::AlignCenter);
    setLayoutMode(QListView::Batched);
    setDragEnabled(false);
    setSpacing(0);
    itemModel = new QStandardItemModel();
    setModel(itemModel);
    setItemDelegate(new WallpaperItemDelegate(this));
}

void WallpaperListView::initLoadImage(int row)
{
    int imageNumPerRow = AppConfig::getImageNumPerRowInListView();
    for (int i = 0; i < row * imageNumPerRow; i++) {
        QStandardItem *item = new QStandardItem;
        item->setData(QVariant::fromValue(new WallpaperItem(earliestData)), Qt::DisplayRole);
        itemModel->appendRow(item);
        earliestData = earliestData.addDays(-1);
    }
}

void WallpaperListView::initTimer()
{
    updateTimer = new QTimer();
    updateTimer->setSingleShot(false);
    updateTimer->setInterval(50);
    connect(updateTimer, &QTimer::timeout, [this]() {
        this->update();
    });
    updateTimer->start();
}
