#include <QGridLayout>
#include <QImage>
#include <QKeyEvent>
#include <QPushButton>
#include <QApplication>
#include <QPainter>
#include <QLabel>
#include <QDesktopWidget>
#include <QBitmap>

#include "FramelessWidget.h"
#include "PreviewWallpaperDialog.h"

PreviewWallpaperDialog::PreviewWallpaperDialog(QWidget *parent) : QDialog(parent)
{
    framelessWidget = new FramelessWidget(this);
    initUI();
    initConnect();
}

void PreviewWallpaperDialog::initUI()
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    closeButton = new QPushButton(QIcon(":/app_images/app_images/close_preview.svg"), QString());
    closeButton->setFixedSize(32, 32);
    closeButton->setFlat(true);
    closeButton->setIconSize(QSize(32, 32));
    closeButton->setAttribute(Qt::WA_TranslucentBackground, true);
    closeButton->setFocusPolicy(Qt::NoFocus);

    wallpaperQLabel = new QLabel();
    wallpaperQLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto *gLayout = new QGridLayout();
    gLayout->setContentsMargins(0, 0, 0, 0);
    gLayout->addWidget(wallpaperQLabel, 0, 0, Qt::AlignCenter);
    gLayout->addWidget(closeButton, 0, 0, Qt::AlignTop | Qt::AlignRight);

    setLayout(gLayout);

    setFocusPolicy(Qt::StrongFocus);

    QDesktopWidget desktopWidget;
    auto rect = desktopWidget.screenGeometry(this);
    setFixedSize(static_cast<int>(rect.width() * 0.75), static_cast<int>(rect.height() * 0.75));
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

void PreviewWallpaperDialog::paintEvent(QPaintEvent *event)
{
    QBitmap bmp(size());
    bmp.fill();
    QPainter p(&bmp);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),8,8);
    setMask(bmp);
    QDialog::paintEvent(event);
}