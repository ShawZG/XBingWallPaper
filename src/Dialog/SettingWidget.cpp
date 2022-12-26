//
// Created by xiao on 22-12-18.
//

#include "SettingWidget.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QString>
#include <QDir>
#include <QTextStream>
#include "AppConfig.h"
#include "CommonHelper.h"

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
    QString desktopContent = R"#([Desktop Entry]
Categories=Graphics
Exec=/opt/apps/org.xzg.xbingwallpaper/files/xbingwallpaper --update-today
Icon=/opt/apps/org.xzg.xbingwallpaper/entries/icons/hicolor/scalable/apps/org.xzg.xbingwallpaper.svg
Name=xBingWallpaper-bg
Type=Application
NoDisplay=true
)#";
    QString desktopName = "org.xzg.xbingwallpaper-bg.desktop";
    auto desktopPath = CommonHelper::localAutoStartLocation() + QDir::separator() + desktopName;

    AppConfig::setUpdateWallpaperDaily(autoUpdateCheckBox->isChecked());
    if (autoUpdateCheckBox->isChecked()) {
        QFile::remove(desktopPath);

        QFile desktopFile(desktopPath);
        if (!desktopFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            return;
        }

        QTextStream out(&desktopFile);
        out << desktopContent;
        out.flush();
        desktopFile.close();
    } else {
        QFile::remove(desktopPath);
    }
}
