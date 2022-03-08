#ifndef PREVIEWWALLPAPERWIDGET_H
#define PREVIEWWALLPAPERWIDGET_H

#include <QDialog>

class QPushButton;
class QLabel;
class FramelessWidget;

class PreviewWallpaperDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PreviewWallpaperDialog(QWidget *parent = nullptr);

    void setWallpaper(const QString &imagePath);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void initUI();
    void initConnect();

    QPushButton *closeButton = nullptr;
    QLabel *wallpaperQLabel = nullptr;
    FramelessWidget *framelessWidget = nullptr;
};

#endif // PREVIEWWALLPAPERWIDGET_H
