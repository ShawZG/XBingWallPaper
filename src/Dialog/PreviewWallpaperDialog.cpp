#include <QGridLayout>
#include <QImage>
#include <QKeyEvent>
#include <QPushButton>
#include <QApplication>
#include <QPainter>
#include <QLabel>
#include <QDesktopWidget>

#include "PreviewWallpaperDialog.h"

PreviewWallpaperDialog::PreviewWallpaperDialog(QWidget *parent) : QDialog(parent)
{
    initUI();
    initConnect();
}

void PreviewWallpaperDialog::initUI()
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    closeButton = new QPushButton(QIcon(":/images/close_preview.svg"), QString());
    closeButton->setFlat(true);
    closeButton->setFixedSize(64, 64);
    /* todo 设置closebutton背景透明 */

    wallpaperQLabel = new QLabel();
    wallpaperQLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto *gLayout = new QGridLayout();
    gLayout->setContentsMargins(2, 2, 2, 2);
    gLayout->addWidget(wallpaperQLabel, 0, 0, Qt::AlignCenter);
    gLayout->addWidget(closeButton, 0, 0, Qt::AlignTop | Qt::AlignRight);

    setLayout(gLayout);

    setFocusPolicy(Qt::StrongFocus);

    setFixedSize(800, 600);
}

void PreviewWallpaperDialog::initConnect()
{
    connect(closeButton, &QPushButton::clicked, this, &PreviewWallpaperDialog::close);
}

void PreviewWallpaperDialog::setWallpaper(const QImage &image)
{
    wallpaperQLabel->setPixmap(QPixmap::fromImage(image).scaledToWidth(rect().width()));
}

void PreviewWallpaperDialog::keyPressEvent(QKeyEvent *event)
{
    if (Qt::Key_Enter == event->key()){
        close();
    } else {
        QDialog::keyPressEvent(event);
    }
}

