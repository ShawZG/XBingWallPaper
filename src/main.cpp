#include <QObject>
#include <QTextCodec>
#include <QStandardPaths>
#include <QTranslator>
#include "singleapplication.h"
#include "CommonHelper.h"
#include "DarkStyle.h"
#include "MainDialog.h"
#include "AppConfig.h"
#include "AutoUpdateWallpaperAgent.h"

int main(int argc, char *argv[])
{
    qputenv("QT_LOGGING_RULES", "*.debug=true; qt.*.debug=false");

    if ((2 == argc) && (QString(argv[1]) == "--update-today")) {
        // 每日更新壁纸后端业务入口
        QGuiApplication app(argc, argv);

        AutoUpdateWallpaperAgent agent;
        agent.tryUpdateWallpaper(QDate::currentDate());
        QObject::connect(&agent, &AutoUpdateWallpaperAgent::sigUpdateWallpaperFinished, &app, &QGuiApplication::quit, Qt::QueuedConnection);

        return app.exec();
    } else {
        // 前端GUI业务入口
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
}
