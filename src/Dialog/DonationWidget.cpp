//
// Created by xiao on 22-12-18.
//

#include "DonationWidget.h"

#include <QLabel>
#include <QApplication>
#include <QVBoxLayout>

DonationWidget::DonationWidget(QWidget *parent)
{
    initUI();
}

void DonationWidget::initUI()
{
    auto *iconLabel = new QLabel();
    iconLabel->setFixedSize(156, 156);
    QPixmap icon(":/app_images/app_images/wx_donation.jpg");
    iconLabel->setPixmap(icon.scaled(iconLabel->size()));

    QFont font = QApplication::font();
    font.setPointSize(14);

    auto *donationLabel = new QLabel();
    donationLabel->setFont(font);
    donationLabel->setText(tr("Wei Xin Donation"));

    auto *vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(10, 10, 10, 10);
    vLayout->addWidget(iconLabel, 1, Qt::AlignCenter);
    vLayout->addSpacing(10);
    vLayout->addWidget(donationLabel, 1, Qt::AlignCenter);
    vLayout->addStretch(10);

    setLayout(vLayout);
}
