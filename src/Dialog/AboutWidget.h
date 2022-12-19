//
// Created by xiao on 22-12-18.
//

#ifndef XBINGWALLPAPER_ABOUT_WIDGET_H
#define XBINGWALLPAPER_ABOUT_WIDGET_H

#include <QWidget>

class AboutWidget : public QWidget
{
Q_OBJECT
public:
    explicit AboutWidget(QWidget *parent = nullptr);

private:
    void initUI();
};


#endif //XBINGWALLPAPER_ABOUT_WIDGET_H
