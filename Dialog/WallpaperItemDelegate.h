#ifndef WALLPAPERITEMDELEGATE_H
#define WALLPAPERITEMDELEGATE_H

#include <QStyledItemDelegate>

class WallpaperItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    WallpaperItemDelegate();

//    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
//    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // WALLPAPERITEMDELEGATE_H
