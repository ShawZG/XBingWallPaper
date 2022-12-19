//
// Created by xiao on 22-12-18.
//

#ifndef XBINGWALLPAPER_SETTINGDIALOG_H
#define XBINGWALLPAPER_SETTINGDIALOG_H

#include <QDialog>

class FramelessWidget;
class TitleWidget;

class SettingDialog: public QDialog
{
Q_OBJECT
public:
    explicit SettingDialog(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void initUI();
    void initTitleWidget();
    void initMainWidget();

    FramelessWidget *framelessWidget = nullptr;
    TitleWidget     *titleWidget = nullptr;
    QWidget         *mainWidget = nullptr;
};

#endif //XBINGWALLPAPER_SETTINGDIALOG_H
