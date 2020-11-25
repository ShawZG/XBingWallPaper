#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

class FramelessWidget;
class QListView;
class QLabel;
class QCheckBox;
class WallpaperListView;
class TitleWidget;

class MainDialog : public QDialog
{
    Q_OBJECT
public:
    MainDialog(QWidget *parent = nullptr);
    ~MainDialog();

protected:
    void paintEvent(QPaintEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    void initUI();
    void initTitleWidget();
    void initMainWidget();
    void adjustDialogSize();
    void restoreAppGeometry();

    TitleWidget         *titleWidget = nullptr;
    FramelessWidget     *framelessWidget = nullptr;
    QWidget             *mainWidget = nullptr;
    WallpaperListView   *wallpaperList = nullptr;

    QWidget     *bottomWidget = nullptr;
    QCheckBox   *autoRunButton = nullptr;
};

#endif // MAINDIALOG_H
