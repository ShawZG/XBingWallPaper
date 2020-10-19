#include <QPainter>
#include <QVariant>
#include <QModelIndex>
#include <QDebug>
#include <QListView>

#include "AppConfig.h"
#include "Global.h"
#include "WallpaperItem.h"

#include "WallpaperItemDelegate.h"

WallpaperItemDelegate::WallpaperItemDelegate(QWidget *parent) : parentWidget(parent)
{
}

QRect WallpaperItemDelegate::adjustNormalImageRect(const QRect &rect) const
{
    int x = rect.x() + static_cast<int>(rect.width() * 0.05);
    int y = rect.y() + static_cast<int>(rect.height() * 0.05);
    int width = static_cast<int>(rect.width() * 0.9);
    int height = static_cast<int>(rect.height() * 0.9);
    return QRect(QPoint(x, y), QSize(width, height));
}

QRect WallpaperItemDelegate::adjustSelectedImageRect(const QRect &rect) const
{
    int x = rect.x() + static_cast<int>(rect.width() * 0.03);
    int y = rect.y() + static_cast<int>(rect.height() * 0.03);
    int width = static_cast<int>(rect.width() * 0.94);
    int height = static_cast<int>(rect.height() * 0.94);
    return QRect(QPoint(x, y), QSize(width, height));
}

void WallpaperItemDelegate::paintImage(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    WallpaperItem *item = index.data(Qt::DisplayRole).value<WallpaperItem *>();
    QRect adjustRect = option.rect.adjusted(0, 0, 0, 0);
    if ( true == item->imageLoadResult) {
        QPoint mousePoint = parentWidget->mapFromGlobal(QCursor::pos());
        if (/* false == option.state.testFlag(QStyle::State_Selected)
             && */false == option.rect.contains(mousePoint)) {
            adjustRect = adjustNormalImageRect(adjustRect);
        }
        QPainterPath clipPath;
        clipPath.addRoundedRect(adjustRect, 6, 6);
        painter->setPen(Qt::transparent);
        painter->setClipPath(clipPath);
        painter->drawImage(clipPath.boundingRect().toRect(), *(item->image));
        painter->drawPath(clipPath);
    }
#ifdef QT_DEBUG
    QString str = QString("(%1, %2, %3 x %4)").arg(option.rect.x()).arg(option.rect.y()).arg(option.rect.width()).arg(option.rect.height());
    painter->drawRect(adjustRect);
    painter->drawText(adjustRect, str);
#endif
}

void WallpaperItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid() && index.data(Qt::DisplayRole).canConvert<WallpaperItem *>()) {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing, true);
        paintImage(painter, option, index);
        painter->restore();
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize WallpaperItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    return option.rect.size();

    //    int num = AppConfig::getImageNumPerRowInListView();
    //    if (nullptr != parentWidget) {
    //        QListView *listView = qobject_cast<QListView *>(parentWidget);
    //        int width = (listView->viewport()->width() - (listView->spacing()) * (num + 1)) / num;
    //        QSize size = AppConfig::screenGeometry();
    //        int height = width * size.height() / size.width();
    //        return QSize(width - 1, height);
    //    } else {
    //        return option.rect.size();
    //    }
}
