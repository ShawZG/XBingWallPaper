#include <QStandardItem>
#include <QVariant>
#include <QTimer>
#include <QScrollBar>
#include <QScroller>
#include <QDebug>
#include <QAbstractScrollArea>

#include <QStandardItemModel>
#include "Common/WallpaperItem.h"
#include "Common/AppConfig.h"
#include "Common/Global.h"
#include "WallpaperItemDelegate.h"
#include "WallpaperListView.h"

WallpaperListView::WallpaperListView(QWidget *parent) : QListView(parent)
{
    initListView();
    loadImages(AppConfig::getInitShowImageRowNum());
    initConnect();
    initTimer();
}

void WallpaperListView::initListView()
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setViewMode(QListView::IconMode);
    setResizeMode(QListView::Adjust);
    setMovement(QListView::Static);
    setFlow(QListView::LeftToRight);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setSpacing(0);
    setWrapping(true);
    itemModel = new QStandardItemModel();
    setModel(itemModel);
    setItemDelegate(new WallpaperItemDelegate(this));

    QScrollBar *vScrollBar = verticalScrollBar();
    vScrollBar->setFixedWidth(16);
}

void WallpaperListView::initConnect()
{
    QScrollBar *vScrollBar = verticalScrollBar();
    connect(vScrollBar, &QScrollBar::valueChanged, [this, vScrollBar](int value) {
        if (vScrollBar->maximum() == value) {
            this->loadImages(1);
        }
    });
}

void WallpaperListView::loadImages(int row)
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

void WallpaperListView::updateGridSize()
{
    int imageNumPerRow = AppConfig::getImageNumPerRowInListView();
    int width = (viewport()->width() - 4) / imageNumPerRow;
    QSize size = AppConfig::screenGeometry();
    size.scale(width, width, Qt::KeepAspectRatio);
    //setIconSize(size);
    setGridSize(size);
}

void WallpaperListView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    updateGridSize();
    QListView::resizeEvent(event);
}

void WallpaperListView::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    updateGridSize();
    QListView::showEvent(event);
}
