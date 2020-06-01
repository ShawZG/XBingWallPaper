#include <QListView>
#include <QVBoxLayout>
#include "FramelessWidget.h"
#include "Common/WallpaperItem.h"
#include "MainDialog.h"

MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
//    QScopedPointer<FramelessWidget> framelessWidget(new FramelessWidget(this));
//    std::shared_ptr<FramelessWidget> framelessWidget = std::make_shared<FramelessWidget>(this);
    framelessWidget = new FramelessWidget(this);

    initUI();

    WallpaperItem *item = new WallpaperItem(QDate(2020, 6, 1));

}

MainDialog::~MainDialog()
{
}

void MainDialog::initUI()
{
    initMainWidget();

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(2, 2, 2, 2);
    vLayout->addWidget(mainWidget);
    setLayout(vLayout);
}

void MainDialog::initMainWidget()
{
    wallpaperList = new QListView();
    wallpaperList->setViewMode(QListView::IconMode);

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(0 ,0 ,0 ,0);
    vLayout->addWidget(wallpaperList);

    mainWidget = new QWidget();
    mainWidget->setLayout(vLayout);
}
