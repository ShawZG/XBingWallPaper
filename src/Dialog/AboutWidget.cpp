#include "AboutWidget.h"
#include <QLabel>
#include <QApplication>
#include <QVBoxLayout>

#include "AppConfig.h"

AboutWidget::AboutWidget(QWidget *parent)
{
    initUI();
}

void AboutWidget::initUI()
{
    auto *iconLabel = new QLabel();
    iconLabel->setFixedSize(96, 96);
    QPixmap icon(":/app_images/app_images/logo.svg");
    iconLabel->setPixmap(icon.scaled(iconLabel->size()));

    QFont font = QApplication::font();
    font.setPointSize(14);

    auto *verLabel = new QLabel();
    verLabel->setFont(font);
    verLabel->setText(tr("Version: ") + AppConfig::getAppVersion());

    auto *fallbackLabel = new QLabel();
    fallbackLabel->setFont(font);
    fallbackLabel->setText(tr("Author: ") + "blueshaw@163.com");

    auto *warningLabel = new QLabel();
    warningLabel->setFont(font);
    warningLabel->setText(tr("Just for learning, not Commercial！"));

    auto *vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(10, 10, 10, 10);
    vLayout->addWidget(iconLabel, 1, Qt::AlignCenter);
    vLayout->addSpacing(10);
    vLayout->addWidget(verLabel, 1, Qt::AlignCenter);
    vLayout->addWidget(fallbackLabel, 1, Qt::AlignCenter);
    vLayout->addWidget(warningLabel, 1, Qt::AlignCenter);
    vLayout->addStretch(10);

    setLayout(vLayout);
}
