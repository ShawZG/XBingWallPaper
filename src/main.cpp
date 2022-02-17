#include <QObject>
#include <QTextCodec>
#include <QStandardPaths>
#include <QTranslator>

#include "singleapplication.h"
#include "CommonHelper.h"
#include "DarkStyle.h"
#include "MainDialog.h"
#include "AppConfig.h"

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    SingleApplication app(argc, argv,  true, SingleApplication::User, 100 );
    app.setAttribute(Qt::AA_UseHighDpiPixmaps);
    app.setStyle(new DarkStyle);
    app.setOrganizationName("xzg");
    app.setApplicationDisplayName(QObject::tr("xBingWallpaper"));
    app.setApplicationName("xBingWallpaper");
    app.setApplicationVersion(AppConfig::getAppVersion());
    app.setWindowIcon(QIcon(":/app_images/app_images/logo.svg"));

#ifdef Q_OS_LINUX
    QTranslator translator;
    if (translator.load(QLocale(), QLatin1String("xbingwallpaper"), QLatin1String("_"), "/opt/apps/org.xzg.xbingwallpaper/files/translations")) {
        app.installTranslator(&translator);
    }
#endif
    CommonHelper::setStyle(QString(":/dark_style/dark_style/darkstyle.qss"));

    MainDialog w;
    QObject::connect(&app, &SingleApplication::instanceStarted, &w, &MainDialog::raise);
    if (app.isPrimary()) {
        w.show();
    } else {
        emit app.instanceStarted();
        app.exit((0));
    }

    return app.exec();
}
