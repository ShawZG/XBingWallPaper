#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

class FramelessWidget;
class QListView;
class QLabel;
class QCheckBox;
class WallpaperListView;

class MainDialog : public QDialog
{
    Q_OBJECT
public:
    MainDialog(QWidget *parent = nullptr);
    ~MainDialog();

private:
    void initUI();
    void initMainWidget();

    FramelessWidget *framelessWidget = nullptr;

    QWidget     *titleWidget = nullptr;
    QLabel      *appLogoLabel = nullptr;
    QPushButton *appMiniButton = nullptr;
    QPushButton *appMaxButton = nullptr;
    QPushButton *appCloseButton = nullptr;

    QWidget             *mainWidget = nullptr;
    WallpaperListView   *wallpaperList = nullptr;

    QWidget     *bottomWidget = nullptr;
    QCheckBox   *autoRunButton = nullptr;
};

#endif // MAINDIALOG_H
