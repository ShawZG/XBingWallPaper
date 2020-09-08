#ifndef PREVIEWWALLPAPERWIDGET_H
#define PREVIEWWALLPAPERWIDGET_H

#include <QDialog>

class QPushButton;
class QLabel;

class PreviewWallpaperDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PreviewWallpaperDialog(QWidget *parent = nullptr);

    void setWallpaper(const QImage &image);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void initUI();
    void initConnect();

    QPushButton *closeButton = nullptr;
    QLabel *wallpaperQLabel = nullptr;
};

#endif // PREVIEWWALLPAPERWIDGET_H
