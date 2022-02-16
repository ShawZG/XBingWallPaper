#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPalette>
#include <QPainter>
#include <QLabel>
#include <QApplication>
#include <QBitmap>

#include "AppConfig.h"
#include "FramelessWidget.h"
#include "TitleWidget.h"

#include "AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent)
{
    framelessWidget = new FramelessWidget(this);
    framelessWidget->setFramelessWidgetResizeEnable(false);
    initUI();
}

void AboutDialog::initUI()
{
    initTitleWidget();
    initCenterWidget();

    auto *vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
    vLayout->addWidget(titleWidget);

    /* 不遮挡当前主窗口的的圆角矩形 */
    auto *hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(5, 5, 5, 5);
    hLayout->addWidget(centerWidget);
    vLayout->addLayout(hLayout);
    setLayout(vLayout);
}

void AboutDialog::initTitleWidget()
{
    titleWidget = new TitleWidget(QString(), QString::fromLocal8Bit("关于"), false, false, false, this);
}

void AboutDialog::initCenterWidget()
{
    centerWidget = new QWidget();

    auto *iconLabel = new QLabel();
    iconLabel->setFixedSize(96, 96);
    QPixmap icon(":/app_images/app_images/logo.svg");
    iconLabel->setPixmap(icon.scaled(iconLabel->size()));

    QFont font = QApplication::font();
    font.setPointSize(14);

    auto *verLabel = new QLabel();
    verLabel->setFont(font);
    verLabel->setText("版    本: " + AppConfig::getAppVersion());

    auto *fallbackLabel = new QLabel();
    fallbackLabel->setFont(font);
    fallbackLabel->setText("作    者: blueshaw@163.com");

    auto *warningLabel = new QLabel();
    warningLabel->setFont(font);
    warningLabel->setText(QString::fromLocal8Bit("学习参考，壁纸请勿商用！"));

    auto *vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(10);
    vLayout->addStretch();
    vLayout->addWidget(verLabel);
    vLayout->addWidget(fallbackLabel);
    vLayout->addWidget(warningLabel);
    vLayout->addStretch();

    auto *hLayout = new QHBoxLayout();
    hLayout->setSpacing(0);
    hLayout->setContentsMargins(10, 10, 10, 10);
    hLayout->addWidget(iconLabel);
    hLayout->addSpacing(20);
    hLayout->addLayout(vLayout);

    centerWidget->setLayout(hLayout);
}

void AboutDialog::paintEvent(QPaintEvent *event)
{
    QBitmap bmp(size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),8,8);
    setMask(bmp);
    QDialog::paintEvent(event);

    QDialog::paintEvent(event);
}
