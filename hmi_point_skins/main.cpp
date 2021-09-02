
#include "control/manager/manager.h"
#include "skinmanager.h"
#include <QGuiApplication>
#include <QDir>
#ifdef HMIBOX
    #include "bin/mainwindow.h"
#endif
int main(int argc, char *argv[])
{
    QString pattern("%{time boot} %{time yyyy-MM-dd h:mm:ss.zzz t} %{if-debug} %{file}:%{line}:%{function} --%{endif} %{message}");
    qSetMessagePattern(pattern);
    LOGPRINT("point process start!!!");
#ifdef DESKTOP
#else
//    libclsmgr_init((char*)CLS_MGR_HMI_POINT_NAME);
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
    qmlRegisterType<Manager>("qmlEnums", 1, 0, "AutoCheckEnums");
    qmlRegisterType<TelltalesScreen>("qmlEnums", 1, 0, "COLORTYPEEnums");
    qmlRegisterType<TelltalesScreen>("qmlEnums", 1, 0, "TELLTALESIDEnums");

    qputenv("QT_SCREEN_ZORDER", "9");
    qputenv("QT_SCREEN_PIPELINE", "9");

#ifdef DESKTOP
    view.rootContext()->setContextProperty("fontPath", "file:///"+QDir::currentPath()+"/../../hmi_point_skins/fonts/");
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
}
