//
// Created by xiao on 22-12-18.
//

#include "SettingWidget.h"
#include <QApplication>
#include <QVBoxLayout>
#include "AppConfig.h"

SettingWidget::SettingWidget(QWidget *parent)
{
    initUI();
}

void SettingWidget::initUI()
{
    QFont font = QApplication::font();
    font.setPointSize(14);

    autoUpdateCheckBox = new QCheckBox(tr("Automatically update wallpaper daily"), this);
    autoUpdateCheckBox->setChecked(AppConfig::getUpdateWallpaperDaily());
    autoUpdateCheckBox->setFont(font);

    connect(autoUpdateCheckBox, &QCheckBox::stateChanged, this, &SettingWidget::slotUpdateWallpaperConfigChanged);

    auto *vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(10, 10, 10, 10);
    vLayout->addWidget(autoUpdateCheckBox, 1, Qt::AlignLeft);
    vLayout->addStretch(10);

    setLayout(vLayout);
}

void SettingWidget::slotUpdateWallpaperConfigChanged()
{
    AppConfig::setUpdateWallpaperDaily(autoUpdateCheckBox->isChecked());
    if (autoUpdateCheckBox->isChecked()) {

    } else {

    }
}
