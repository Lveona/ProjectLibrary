#include "skinmanager.h"
#include <QDebug>
#include <QDir>

static int g_lastSkin = 0;
static bool init = true;
#ifdef DESKTOP

static QStringList g_skinsPath = {
    QDir::currentPath()+"/../../hmi_gauge_skins/skins/comfort/comfort_point_main.rcc",
    QDir::currentPath()+"/../../hmi_gauge_skins/skins/eco/eco_point_main.rcc",
    QDir::currentPath()+"/../../hmi_gauge_skins/skins/sport/sport_point_main.rcc",
    QDir::currentPath()+"/../../hmi_gauge_skins/skins/individual/individual_point_main.rcc"
};

static QStringList g_imagePath = {
    QDir::currentPath()+"/../../hmi_gauge_skins/skins/comfort/comfort_point_image.rcc",
    QDir::currentPath()+"/../../hmi_gauge_skins/skins/eco/eco_point_image.rcc",
    QDir::currentPath()+"/../../hmi_gauge_skins/skins/sport/sport_point_image.rcc",
    QDir::currentPath()+"/../../hmi_gauge_skins/skins/individual/individual_point_image.rcc"
};

#else
static QStringList g_skinsPath = {
    "/usr/share/skins/comfort/comfort_point_main.rcc",
    "/usr/share/skins/eco/eco_point_main.rcc",
    "/usr/share/skins/sport/sport_point_main.rcc",
    "/usr/share/skins/individual/individual_point_main.rcc"
};

static QStringList g_imagePath = {
    "/usr/share/skins/comfort/comfort_point_image.rcc",
    "/usr/share/skins/eco/eco_point_image.rcc",
    "/usr/share/skins/sport/sport_point_image.rcc",
    "/usr/share/skins/individual/individual_point_image.rcc"
};

#endif
//static QStringList g_qmlPath = {
//    "skin1/main.qml",
//    "skin2/main.qml"
//};

static QStringList g_qmlPath = {
    "comfort/main.qml",
    "eco/main.qml",
    "sport/main.qml",
    "individual/main.qml"
};

SkinManager::SkinManager(QQuickView* view, QObject *parent)
    : QObject(parent)
{
    m_currentSkin = "";
    _view = view;
    _view->rootContext()->setContextProperty("SkinManager", this);
}

void SkinManager::changeskin(int skin)
{
    --skin;
    qInfo()<<"SkinManager changeskin Point"<<skin;
    //qInfo()<<QDir::currentPath()<<g_skinsPath.at(skin);
    //D:/shangqi/Trunk/SK83_Cluster_SOC/Cluster/build-NeusoftCluster-Desktop_Qt_5_10_1_MinGW_32bit-Debugbox/debug

    if(skin < 0 || skin >= g_skinsPath.size() )
        return ;


    if(init){
        init = false;
        bool r = QResource::registerResource(g_skinsPath.at(skin));
        r = QResource::registerResource(g_imagePath.at(skin));
        if(r){
            setCurrentSkin(g_qmlPath.at(skin));
        }
        g_lastSkin = skin;
        return;
    }

    if(g_lastSkin == skin) return;

    QResource::unregisterResource(g_skinsPath.at(g_lastSkin));
    QResource::unregisterResource(g_imagePath.at(g_lastSkin));
    bool r = QResource::registerResource(g_skinsPath.at(skin));
    r = QResource::registerResource(g_imagePath.at(skin));
    if(r){
        setCurrentSkin(g_qmlPath.at(skin));
    }

    g_lastSkin = skin;
}

