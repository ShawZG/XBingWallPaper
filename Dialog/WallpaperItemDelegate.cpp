#include <QPainter>
#include <QVariant>
#include <QModelIndex>
#include <QDebug>
#include <QListView>

#include "Common/AppConfig.h"
#include "Common/WallpaperItem.h"
#include "WallpaperItemDelegate.h"

WallpaperItemDelegate::WallpaperItemDelegate(QWidget *parent) : parentWidget(parent)
{
}

void WallpaperItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid()) {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing, true);

        if (true == index.data(Qt::DisplayRole).canConvert<WallpaperItem *>()) {
            WallpaperItem *item = index.data(Qt::DisplayRole).value<WallpaperItem *>();
            if ( true == item->imageLoadResult) {
                painter->drawImage(option.rect, *(item->image));
            }
        }
        painter->restore();
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize WallpaperItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int num = AppConfig::getImageNumPerRowInListView();

    if (nullptr != parentWidget && true == index.data(Qt::DisplayRole).canConvert<WallpaperItem *>()) {
        QListView *listView = qobject_cast<QListView*>(parentWidget);
        int width = (listView->viewport()->width() - (listView->spacing() + 1) * (num + 1)) / num - 1;
        QSize size = AppConfig::screenGeometry();
        int height = width * size.height() / size.width();
        return QSize(width, height);
    } else {
        return option.rect.size();
    }
}
