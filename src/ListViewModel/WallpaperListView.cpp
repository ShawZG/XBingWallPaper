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

#include "AppConfig.h"
#include "Global.h"
#include "PreviewWallpaperDialog.h"
#include "WallpaperItemDelegate.h"
#include "WallpaperItem.h"

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

    QScrollBar *vScrollBar = verticalScrollBar();
    vScrollBar->setFixedWidth(16);

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
    updateTimer->setInterval(100);
    connect(updateTimer, &QTimer::timeout, [this](){this->update();});
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
    QAction *setAction = menu->addAction(QIcon(":/images/set_wallpaper.svg"), tr("set to wallpaper"));
    connect(setAction, &QAction::toggle, this, [](){});

    QAction *downloadAction = menu->addAction(QIcon(":/images/download_wallpaper.svg"), tr("download wallpaper"));
    connect(downloadAction, &QAction::toggle, this, [](){});

    QAction *previewAction = menu->addAction(QIcon(":/images/preivew_wallpaper.svg"), tr("preview wallpaper"));
    //connect(previewAction, &QAction::toggle, this, [this](){this->slotShowPreview();});
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
    if (true != selectionModel()->selectedIndexes().isEmpty()){
        menu->exec(QCursor::pos());
    }
}

void WallpaperListView::slotShowPreview(const QModelIndex &index)
{
    if (true == index.isValid()) {
        PreviewWallpaperDialog dialog;
        WallpaperItem *item = index.data(Qt::DisplayRole).value<WallpaperItem*>();
        dialog.setWallpaper(*(item->image));
        dialog.exec();
    }
}
