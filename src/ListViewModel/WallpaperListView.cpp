#include <QStandardItem>
#include <QVariant>
#include <QTimer>
#include <QScrollBar>
#include <QScroller>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QAbstractScrollArea>
#include <QStandardItemModel>
#include <QStandardPaths>

#include "AppConfig.h"
#include "Global.h"
#include "PreviewWallpaperDialog.h"
#include "WallpaperItemDelegate.h"
#include "WallpaperItem.h"
#include "CommonHelper.h"
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
    setFrameShape(QFrame::NoFrame);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setViewMode(QListView::IconMode);
    setResizeMode(QListView::Adjust);
    setMovement(QListView::Static);
    setFlow(QListView::LeftToRight);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setSpacing(0);
    setWrapping(true);
    itemModel = new QStandardItemModel();
    setModel(itemModel);
    setItemDelegate(new WallpaperItemDelegate(this));

    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    setContextMenuPolicy(Qt::CustomContextMenu);
    initMenu();
}

void WallpaperListView::initConnect()
{
    QScrollBar *vScrollBar = verticalScrollBar();
    connect(vScrollBar, &QScrollBar::valueChanged, [this, vScrollBar](int value) {
        if (vScrollBar->maximum() == value) {
            this->loadImages(1);
        }
    });

    connect(this, &WallpaperListView::customContextMenuRequested, this, &WallpaperListView::slotShowMenu);
    connect(this, &WallpaperListView::doubleClicked, this, &WallpaperListView::slotShowPreview);
}

void WallpaperListView::loadImages(int row)
{
    int imageNumPerRow = AppConfig::getImageNumPerRowInListView();
    for (int i = 0; i < row * imageNumPerRow; i++) {
        auto *item = new QStandardItem;
        item->setData(QVariant::fromValue(new WallpaperItem(earliestData)), Qt::DisplayRole);
        itemModel->appendRow(item);
        earliestData = earliestData.addDays(-1);
    }
}

void WallpaperListView::initTimer()
{
    updateTimer = new QTimer();
    updateTimer->setSingleShot(false);
    updateTimer->setInterval(1000);
    // 图片从网络下载到本地，再加载到Item，View静止条件下不会主动更新画面，设置可视区域为脏区，强制更新画面。
    connect(updateTimer, &QTimer::timeout, [this](){setDirtyRegion(QRegion(viewport()->rect(),  QRegion::Rectangle));});
    updateTimer->start();
}

void WallpaperListView::updateGridSize()
{
    int imageNumPerRow = AppConfig::getImageNumPerRowInListView();
    int width = (viewport()->width() - 1) / imageNumPerRow;
    QSize size = AppConfig::screenGeometry();
    size.scale(width, width, Qt::KeepAspectRatio);
    //setIconSize(size);
    setGridSize(size);
}

void WallpaperListView::initMenu()
{
    menu = new QMenu(this);
    QAction *setAction = menu->addAction(QIcon(":/app_images/app_images/set_wallpaper.svg"), tr("Set wallpaper"));
    connect(setAction, &QAction::triggered, this, &WallpaperListView::slotSettingWallpaper);

    QAction *downloadAction = menu->addAction(QIcon(":/app_images/app_images/download_wallpaper.svg"), tr("Save to desktop"));
    connect(downloadAction, &QAction::triggered, this, &WallpaperListView::slotSaveImageToDesktop);

    QAction *previewAction = menu->addAction(QIcon(":/app_images/app_images/preview_wallpaper.svg"), tr("Preview wallpaper"));
//    connect(previewAction, &QAction::toggle, this, [this](){ this->slotShowPreview();});
    connect(previewAction, &QAction::triggered, this, &WallpaperListView::slotShowPreview);
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

void WallpaperListView::slotShowMenu(const QPoint &pos)
{
    Q_UNUSED(pos);
    if (!selectionModel()->selectedIndexes().isEmpty()){
        menu->exec(QCursor::pos());
    }
}

void WallpaperListView::slotShowPreview()
{
    if( currentIndex().isValid()) {
        auto *item = currentIndex().data(Qt::DisplayRole).value<WallpaperItem*>();
        if (item->loadingImageResult) {
            PreviewWallpaperDialog dialog;
            dialog.setWallpaper(item->imageFilePath);
            dialog.exec();
        }
    }
}

void WallpaperListView::slotSaveImageToDesktop()
{
    if( currentIndex().isValid()) {
        auto *item = currentIndex().data(Qt::DisplayRole).value<WallpaperItem*>();
        if (item->loadingImageResult) {
            CommonHelper::copyFileToDir(item->imageFilePath, QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0));
        }
    }
}

void WallpaperListView::slotSettingWallpaper()
{
    if( currentIndex().isValid()) {
        auto *item = currentIndex().data(Qt::DisplayRole).value<WallpaperItem*>();
        if (item->loadingImageResult) {
            CommonHelper::setDesktopWallpaper(item->imageFilePath);
        }
    }
}
