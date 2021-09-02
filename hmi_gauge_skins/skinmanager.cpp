#include "skinmanager.h"
#include <QDebug>
#include <QDir>

static int g_lastSkin = 0;
static bool init = true;
#ifdef DESKTOP
static QStringList g_skinsPath = {
    QDir::currentPath()+"/../../hmi_gauge_skins/skins/comfort/comfort_main.rcc",
    QDir::currentPath()+"/../../hmi_gauge_skins/skins/eco/eco_main.rcc",
    QDir::currentPath()+"/../../hmi_gauge_skins/skins/sport/sport_main.rcc",
    QDir::currentPath()+"/../../hmi_gauge_skins/skins/individual/individual_main.rcc"
};
static QStringList g_imagePath = {
    QDir::currentPath()+"/../../hmi_gauge_skins/skins/comfort/comfort_image.rcc",
    QDir::currentPath()+"/../../hmi_gauge_skins/skins/eco/eco_image.rcc",
    QDir::currentPath()+"/../../hmi_gauge_skins/skins/sport/sport_image.rcc",
    QDir::currentPath()+"/../../hmi_gauge_skins/skins/individual/individual_image.rcc"
};
#else
static QStringList g_skinsPath = {
    "/usr/share/skins/comfort/comfort_main.rcc",
    "/usr/share/skins/eco/eco_main.rcc",
    "/usr/share/skins/sport/sport_main.rcc",
    "/usr/share/skins/individual/individual_main.rcc"
};

static QStringList g_imagePath = {
    "/usr/share/skins/comfort/comfort_image.rcc",
    "/usr/share/skins/eco/eco_image.rcc",
    "/usr/share/skins/sport/sport_image.rcc",
    "/usr/share/skins/individual/individual_image.rcc"
};

#endif
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
    //对应数组从0 开始
    --skin;
    qInfo()<<"SkinManager changeskin "<<skin;

    if(skin < 0 || skin >= g_skinsPath.size() )
        return ;
    if(init){ //第一次加载
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
        g_lastSkin = skin;
    }
}

