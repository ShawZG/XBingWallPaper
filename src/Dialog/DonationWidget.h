//
// Created by xiao on 22-12-18.
//

#ifndef XBINGWALLPAPER_DONATIONWIDGET_H
#define XBINGWALLPAPER_DONATIONWIDGET_H

#include <QWidget>

class DonationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DonationWidget(QWidget *parent = nullptr);

private:
    void initUI();
};



#endif //XBINGWALLPAPER_DONATIONWIDGET_H
