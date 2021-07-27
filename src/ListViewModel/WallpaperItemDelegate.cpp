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
    return {QPoint(x, y), QSize(width, height)};
}

QRect WallpaperItemDelegate::adjustSelectedImageRect(const QRect &rect) const
{
    int x = rect.x() + static_cast<int>(rect.width() * 0.03);
    int y = rect.y() + static_cast<int>(rect.height() * 0.03);
    int width = static_cast<int>(rect.width() * 0.94);
    int height = static_cast<int>(rect.height() * 0.94);
    return {QPoint(x, y), QSize(width, height)};
}

void WallpaperItemDelegate::paintImage(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto *item = index.data(Qt::DisplayRole).value<WallpaperItem *>();
    QRect adjustRect;
    if (item->imageLoadResult) {
        if ( /*option.state.testFlag(QStyle::State_Selected)
             || */option.state.testFlag(QStyle::State_MouseOver)) {
            adjustRect = adjustSelectedImageRect(option.rect);
        } else {
            adjustRect = adjustNormalImageRect(option.rect);
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
    painter->drawRect(option.rect);
    painter->drawText(option.rect, str);
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
}
