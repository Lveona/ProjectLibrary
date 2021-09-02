#include <QQmlApplicationEngine>
#include <QSurfaceFormat>
#include <QMatrix4x4>
#include <QQmlContext>
#include <cachesetter.h>
#include "control/manager/manager.h"
#include "control/home/HomeScreen.h"
#include <QStandardPaths>
#ifdef TESTFUNC
#include "control/hmitest.h"
#endif

#include "skinmanager.h"
#include <QDir>
#include <QGuiApplication>
#include <QQuickView>
#include "hmi_share.h"

#ifdef DESKTOP
#else
#include <sched.h>
#endif

#ifdef HMIBOX
    #include "bin/mainwindow.h"
#endif

/*
2020/5/26
*/
int main(int argc, char *argv[])
{
#ifdef DESKTOP
#else
    struct sched_param param;

    sched_getparam(0,&param );

    param.sched_priority = 20;

    sched_setparam(0,&param );
#endif
    QString pattern("%{time boot} %{time yyyy-MM-dd h:mm:ss.zzz t} %{file}:%{line}:%{function} %{message}");
    qSetMessagePattern(pattern);
    LOGPRINT("gauge process start!!!");
#ifdef DESKTOP
#else
//    libclsmgr_init((char*)CLS_MGR_HMI_GAUGE_NAME);
#endif
//    qputenv("QT_QPA_UPDATE_IDLE_TIME", "33");
    qputenv("QSG_RENDER_LOOP", "threaded");
//    qputenv("QT_LOGGING_RULES", "qt.scenegraph.*=true");
//    QLoggingCategory::setFilterRules("sceneChangingFramework=true");
    QGuiApplication app(argc, argv);

    QQuickView view;

    SkinManager skinManager(&view);

    Q_UNUSED(skinManager);

    Manager::instance()->createCtrl(&view);

    qmlRegisterType<Manager>("qmlEnums", 1, 0, "ManagerEnums");
    qmlRegisterType<HomeScreen>("qmlEnums", 1, 0, "COLORTYPEEnums");
    qputenv("QT_SCREEN_ZORDER", "8");
    qputenv("QT_SCREEN_PIPELINE", "14");
	 qmlRegisterType<CacheSetter>("CacheSetter", 1, 0, "CacheSetter");
#ifdef DESKTOP
    view.rootContext()->setContextProperty("fontPath", "file:///"+QDir::currentPath()+"/../../hmi_gauge_skins/fonts/");
    view.rootContext()->setContextProperty("platform", "win");
#else
    view.rootContext()->setContextProperty("fontPath", "file:////usr/share/neusoft/fonts/");
    view.rootContext()->setContextProperty("platform", "linux");
#endif
    view.setSource(QUrl(QStringLiteral("qrc:///Main.qml")));

    QSurfaceFormat surfaceFormat = view.requestedFormat();
    surfaceFormat.setAlphaBufferSize(8);
    view.setClearBeforeRendering(true);
    view.setColor(QColor(Qt::transparent));
    view.setFlag(Qt::FramelessWindowHint);
    view.setFormat(surfaceFormat);
    view.setX(0);
    view.setY(0);
    surfaceFormat.setVersion(3,20);

#ifdef TESTFUNC
    //
    HMITest hmitest;
    QTest::qExec(&hmitest);
#else
//    LOGPRINT(QStandardPaths::standardLocations(QStandardPaths::CacheLocation)[0]);
    LOGPRINT("gauge process view start show!!!");
    view.show();

#ifdef HMIBOX
    QQuickView view2;
    view2.rootContext()->setContextProperty("Hmibox", HMIBox::instance());
    view2.rootContext()->setContextProperty("View", &view2);
    HMIBox::instance()->init(&view2);
    view2.setSource(QUrl(QStringLiteral("qrc:/hmibox/BoxMain.qml")));
    view2.setTitle("HMIBox3.0");
    view2.setWidth(800);
    view2.setHeight(600);
    view2.show();
#endif
    return app.exec();
#endif
}
