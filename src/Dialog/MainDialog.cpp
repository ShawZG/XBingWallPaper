#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPalette>
#include <QPainter>
#include <QGuiApplication>
#include "FramelessWidget.h"
#include "src/Common/AppConfig.h"
#include "src/Common/Global.h"
#include "src/ListViewModel/WallpaperItem.h"
#include "src/ListViewModel/WallpaperListView.h"
#include "src/ListViewModel/WallpaperItemDelegate.h"
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

    initMainWidget();

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(20, 40, 20, 40);
    vLayout->addWidget(mainWidget);
    setLayout(vLayout);

    adjustDialogSize();
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
    painter.drawRoundedRect(dialogRect, 15, 15);
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
