//
// Created by xiao on 22-12-18.
//

#include "SettingDialog.h"

#include <QVBoxLayout>
#include <QPainter>
#include <QLabel>
#include <QApplication>
#include <QBitmap>
#include <QButtonGroup>
#include <QPushButton>
#include <QStackedLayout>

#include "AppConfig.h"
#include "FramelessWidget.h"
#include "TitleWidget.h"
#include "AboutWidget.h"
#include "SettingWidget.h"
#include "DonationWidget.h"

SettingDialog::SettingDialog(QWidget *parent) : QDialog(parent)
{
    framelessWidget = new FramelessWidget(this);
    framelessWidget->setFramelessWidgetResizeEnable(false);
    initUI();
    setObjectName("SettingDialog");
}

void SettingDialog::initUI()
{
    initTitleWidget();
    initMainWidget();

    auto *vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
    vLayout->addWidget(titleWidget);

    /* 不遮挡当前主窗口的的圆角矩形 */
    auto *hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(5, 5, 5, 5);
    hLayout->addWidget(mainWidget);
    vLayout->addLayout(hLayout);

    setFixedWidth(560);
    setLayout(vLayout);
}

void SettingDialog::initTitleWidget()
{
    titleWidget = new TitleWidget(QString(), tr("Setting"), false, false, false, this);
}

void SettingDialog::initMainWidget()
{
    // 添加右侧设置页面
    auto sLayout = new QStackedLayout();
    sLayout->setContentsMargins(2, 2, 2, 2);

    int settingIndex = sLayout->addWidget(new SettingWidget());
    int aboutIndex = sLayout->addWidget(new AboutWidget());
    int donationIndex = sLayout->addWidget(new DonationWidget());

    // 添加左侧设置按钮
    auto settingButton = new QPushButton(tr("Setting"), this);
    settingButton->setFixedSize(128, 36);
    settingButton->setCheckable(true);
    settingButton->setObjectName("settingButton");

    auto aboutButton = new QPushButton(tr("About"), this);
    aboutButton->setFixedSize(128, 36);
    aboutButton->setCheckable(true);
    aboutButton->setObjectName("aboutButton");

    auto donateButton = new QPushButton(tr("Donation"), this);
    donateButton->setFixedSize(128, 36);
    donateButton->setCheckable(true);
    donateButton->setObjectName("donateButton");

    auto* settingButtonGroup = new QButtonGroup(this);
    settingButtonGroup->setExclusive(true);
    settingButtonGroup->addButton(settingButton, settingIndex);
    settingButtonGroup->addButton(aboutButton, aboutIndex);
    settingButtonGroup->addButton(donateButton, donationIndex);

    auto* vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(2, 2, 2, 2);
    vLayout->setSpacing(10);
    vLayout->addWidget(settingButton);
    vLayout->addWidget(aboutButton);
    vLayout->addWidget(donateButton);
    vLayout->addStretch();

    connect(settingButtonGroup, QOverload<int>::of(&QButtonGroup::buttonPressed), sLayout, &QStackedLayout::setCurrentIndex);

    auto hLayout =new QHBoxLayout();
    hLayout->setContentsMargins(2, 2, 2, 2);
    hLayout->addLayout(vLayout);
    hLayout->addLayout(sLayout);

    mainWidget = new QWidget;
    mainWidget->setLayout(hLayout);
}

void SettingDialog::paintEvent(QPaintEvent *event)
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
