//
// Created by xiao on 22-12-18.
//

#ifndef XBINGWALLPAPER_SETTINGWIDGET_H
#define XBINGWALLPAPER_SETTINGWIDGET_H

#include <QWidget>
#include <QCheckBox>

class SettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWidget(QWidget *parent = nullptr);

private slots:
    void slotUpdateWallpaperConfigChanged();

private:
    void initUI();
    QCheckBox* autoUpdateCheckBox = nullptr;
};
#endif //XBINGWALLPAPER_SETTINGWIDGET_H
