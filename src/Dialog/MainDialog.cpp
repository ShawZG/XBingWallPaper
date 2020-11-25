#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPalette>
#include <QPainter>
#include <QGuiApplication>

#include "TitleWidget.h"
#include "FramelessWidget.h"
#include "AppConfig.h"
#include "Global.h"
#include "WallpaperItem.h"
#include "WallpaperListView.h"
#include "WallpaperItemDelegate.h"

#include "MainDialog.h"

MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
{
    framelessWidget = new FramelessWidget(this);
    initUI();
}

MainDialog::~MainDialog()
{
}

void MainDialog::initUI()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    initTitleWidget();
    initMainWidget();

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
    vLayout->addWidget(titleWidget);
    /* 不遮挡MainDialog的圆角矩形 */
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(8, 0, 8, 8);
    hLayout->setSpacing(0);
    hLayout->addWidget(mainWidget);

    vLayout->addLayout(hLayout);
    setLayout(vLayout);

    adjustDialogSize();
}

void MainDialog::initTitleWidget()
{
    titleWidget = new TitleWidget(QString(":/app_images/app_images/logo.svg"), "XBingWallPaper", true, true, true, this);
}

void MainDialog::initMainWidget()
{
    wallpaperList = new WallpaperListView();
    wallpaperList->setAttribute(Qt::WA_TranslucentBackground);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->addWidget(wallpaperList);

    mainWidget = new QWidget();
    mainWidget->setLayout(hLayout);
}

void MainDialog::adjustDialogSize()
{
    setMinimumSize(AppConfig::screenGeometry() *= 0.4);
    restoreAppGeometry();
}

void MainDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPalette pa = QGuiApplication::palette();
    painter.setBrush(pa.window());
    painter.setPen(Qt::transparent);
    QRect dialogRect;
    dialogRect.setWidth(rect().width() - 1);
    dialogRect.setHeight(rect().height() - 1);
    painter.drawRoundedRect(dialogRect, 10, 10);
    QDialog::paintEvent(event);
}

void MainDialog::closeEvent(QCloseEvent *event)
{
    QRect rect = geometry();
    AppConfig::setAppGeometry(rect);
    QDialog::closeEvent(event);
}

void MainDialog::restoreAppGeometry()
{
    QRect rect = AppConfig::getAppGeometry();
    if (true == rect.isValid()){
        setGeometry(rect);
    } else {
        resize(AppConfig::screenGeometry() *= 0.6);
    }
}
