#include <QVBoxLayout>
#include <QHBoxLayout>
#include "FramelessWidget.h"
#include "Common/WallpaperItem.h"
#include "Common/Global.h"
#include "WallpaperListView.h"
#include "WallpaperItemDelegate.h"
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
    vLayout->setContentsMargins(20, 40, 20, 40);
    vLayout->addWidget(mainWidget);
    setLayout(vLayout);
}

void MainDialog::initMainWidget()
{
    wallpaperList = new WallpaperListView();
    wallpaperList->setAttribute(Qt::WA_TranslucentBackground);

    QFrame *paddingFrame = new QFrame();
    paddingFrame->setAttribute(Qt::WA_TranslucentBackground);
    paddingFrame->setFixedWidth(LIST_VIEWPORT_MARGIN_LEFT);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);
    //hLayout->addWidget(paddingFrame);
    hLayout->addWidget(wallpaperList);

    mainWidget = new QWidget();
    mainWidget->setLayout(hLayout);
}
