#ifndef WALLPAPERITEMDELEGATE_H
#define WALLPAPERITEMDELEGATE_H

#include <QStyledItemDelegate>

class WallpaperItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit WallpaperItemDelegate(QWidget *parent);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

private:
    QRect adjustNormalImageRect(const QRect &rect) const;
    QRect adjustSelectedImageRect(const QRect &rect) const;
    void paintImage(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QWidget *parentWidget = nullptr;
};

#endif // WALLPAPERITEMDELEGATE_H
