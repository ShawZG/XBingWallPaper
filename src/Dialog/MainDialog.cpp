#include <QVBoxLayout>
#include <QPainter>
#include <QGuiApplication>
#include <QBitmap>
#include <QMenu>

#include "TitleWidget.h"
#include "FramelessWidget.h"
#include "AppConfig.h"
#include "Global.h"
#include "WallpaperListView.h"
#include "SettingDialog.h"
#include "MainDialog.h"

MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
{
    framelessWidget = new FramelessWidget(this);
    initUI();
}

MainDialog::~MainDialog() = default;

void MainDialog::initUI()
{
    setWindowFlags(windowFlags() | Qt::WindowTitleHint | Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground);

    initTitleWidget();
    initMainWidget();

    auto *vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
    vLayout->addWidget(titleWidget);
    /* 不遮挡MainDialog的圆角矩形 */
    auto *hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(8, 0, 8, 8);
    hLayout->setSpacing(0);
    hLayout->addWidget(mainWidget);

    vLayout->addLayout(hLayout);
    setLayout(vLayout);

    adjustDialogSize();
}

void MainDialog::initTitleWidget()
{
    titleWidget = new TitleWidget(QString(":/app_images/app_images/logo.svg"), tr("xBingWallpaper"), true, true, true, this);
    auto titleMenu = new QMenu();
    titleMenu->addAction(tr("Setting"), this, &MainDialog::slotShowSettingDialog);
    titleWidget->setTitleMenu(titleMenu);
}

void MainDialog::initMainWidget()
{
    wallpaperList = new WallpaperListView();
    wallpaperList->setAttribute(Qt::WA_TranslucentBackground);
    wallpaperList->setMouseTracking(true);

    auto *hLayout = new QHBoxLayout();
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

void MainDialog::closeEvent(QCloseEvent *event)
{
    QRect rect = geometry();
    AppConfig::setAppGeometry(rect);
    QDialog::closeEvent(event);
}

void MainDialog::restoreAppGeometry()
{
    QRect rect = AppConfig::getAppGeometry();
    if (rect.isValid()){
        setGeometry(rect);
    } else {
        resize(AppConfig::screenGeometry() *= 0.6);
    }
}

void MainDialog::slotShowSettingDialog()
{
    SettingDialog dialog;
    dialog.exec();
}
