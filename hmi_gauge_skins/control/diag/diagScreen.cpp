#include "diagScreen.h"
#include <QTimer>
#include <math.h>
#include <qstringlist.h>
static QStringList enterDiagList;

static int g_isDiagScreenSelectIndexMax = 4;

//[0]
DiagScreen::DiagScreen()
{
    //init
    m_selectedItem        = 0;
    m_currentChild1Page   = 0;
    m_monitorCheckDisplay = DIAG_MONICHK_BLACK;
    m_popType             = 0;
    m_itemMileageClearDisble = 0;
    m_popBottonOKSlecte = true;
    isDiagScreen = false;
}

DiagScreen::~DiagScreen()
{
    delete DiagScreen::instance();
}

void DiagScreen::startControl()
{
    qRegisterMetaType<DIAGRECEIVEMSGID>("DIAGRECEIVEMSGID");

    connect(DiagControl::instance(), SIGNAL(PropertyChange(QString , QVariant )), this, SLOT(SetProperty(QString , QVariant )), Qt::QueuedConnection);

}

//[1]
void DiagScreen::createCtrl(QQuickView *view)
{
    createAppControl(view->rootContext(), "DiagScreen");
}

void DiagScreen::SetProperty(QString name, QVariant value){
    if("clearTotalMile" == name)
    {
        setitemMileageClearDisble(value.toInt());
    }
}

bool DiagScreen::diag_key_pressed_released(int key, int type)
{
    if(!isDiagScreen) return false;

    if(m_currentChild1Page == DIAGCHILEDSCREEN_MENU)
    {

    }
    //电检菜单画面,上下键,列表循环
    if(m_currentChild1Page == DIAGCHILEDSCREEN_MENU)
    {
        //确认pop画面显示中
        if(m_popType != DIAGPOP_EXIT)
        {
            if(HDKEY_UP == key && KEY_OFF == type)
            {
                setPopBottonOKSlecte(false);
            }
            else if(HDKEY_DOWN == key && KEY_OFF == type)
            {
                setPopBottonOKSlecte(true);
            }
            else if(HDKEY_UP == key && KEY_OUT_OFF == type)
            {
                if(m_popBottonOKSlecte == true)
                {
                    if(m_selectedItem == DIAGSELECTITEM_CLEARTOTALMILE)   //里程清零
                    {
                        DiagControl::instance()->clearTotalMile();
                        setPopType(DIAGPOP_EXIT);
                    }
                    else if(m_selectedItem == DIAGSELECTITEM_RESET)   //恢复出厂设置
                    {
                        DiagControl::instance()->diagReset();
                        setcurrentChild1Page(DIAGCHILEDSCREEN_RESET);
                        setPopType(DIAGPOP_EXIT);
                    }
                }
                else
                {
                    setPopType(DIAGPOP_EXIT);
                }
            }
        }
        //电检菜单显示中
        else
        {
            if(HDKEY_UP == key && KEY_OFF == type)
            {
                if(m_selectedItem > DIAGSELECTITEM_MONITORCHECK)
                {
                    setselectedItem(m_selectedItem-1);
                }
                else
                {
                    setselectedItem(g_isDiagScreenSelectIndexMax-1);
                }
            }
            else if(HDKEY_DOWN == key && KEY_OFF == type)
            {
                if(m_selectedItem < g_isDiagScreenSelectIndexMax-1)
                {
                    setselectedItem(m_selectedItem+1);
                }
                else
                {
                    setselectedItem(DIAGSELECTITEM_MONITORCHECK);
                }
            }
            else if(HDKEY_UP == key && KEY_OUT_OFF == type)
            {if(m_selectedItem == DIAGSELECTITEM_MONITORCHECK)   //monitor检查
                {
                    setmonitorCheckDisplay(DIAG_MONICHK_BLACK);
                    setcurrentChild1Page(DIAGCHILEDSCREEN_MONITORCHECK);
                }
                else if(m_selectedItem == DIAGSELECTITEM_CLEARTOTALMILE)   //里程清零
                {
                    if(m_itemMileageClearDisble <= 0)
                    {
                        return true;
                    }
                    setPopBottonOKSlecte(true);
                    setPopType(DIAGPOP_CLEARTOTALMILE);
                }
                else if(m_selectedItem == DIAGSELECTITEM_RESET)   //恢复出厂设置
                {
                    setPopBottonOKSlecte(true);
                    setPopType(DIAGPOP_RESET);
                }
                else if(m_selectedItem == DIAGSELECTITEM_EXIT)    //退出电检
                {
                    diag_ExitDiagScreen();
                }
            }
        }
    }
    //Monitor检查画面，上下切换图片，不循环，OK退出
    else if(m_currentChild1Page == DIAGCHILEDSCREEN_MONITORCHECK)
    {
        if(HDKEY_UP == key && KEY_OFF == type)
        {
            if(m_monitorCheckDisplay > DIAG_MONICHK_BLACK)
            {
                setmonitorCheckDisplay(m_monitorCheckDisplay-1);
            }
        }
        else if(HDKEY_DOWN == key && KEY_OFF == type)
        {
            if(m_monitorCheckDisplay < DIAG_MONICHK_BLUE)
            {
                setmonitorCheckDisplay(m_monitorCheckDisplay+1);
            }
        }
        else if(HDKEY_UP == key && KEY_OUT_OFF == type)
        {
            setcurrentChild1Page(DIAGCHILEDSCREEN_MENU);
        }
    }
    return true;
}

bool DiagScreen::canEnterDiagScreen(int key, int type)
{
    bool canEnter =  handleEnterDiagScreen(key, type);
    if(canEnter){
        diag_EnterDiagScreen();
    }
    return canEnter;
}

bool DiagScreen::handleEnterDiagScreen(int key, int type)
{
    if(KEY_ON == type || KEY_OUT == type){
        return false;
    }
    else if(KEY_OFF == type){
        enterDiagList.clear();
        return false;
    }
    else if(KEY_OUT_OFF == type && HDKEY_UP == key){
        enterDiagList << QString::number(1);

    }
    else if(KEY_OUT_OFF == type && HDKEY_DOWN == key){
        enterDiagList << QString::number(2);

    }
    else{
        enterDiagList.clear();
        return false;
    }
    QString enterDiagStr = enterDiagList.join("");
    if(QString::number(1212).startsWith(enterDiagStr))
    {
        if(/*QString(KEY_BUILDUP)*/"1212" == enterDiagStr)
        {
            isDiagScreen = true;
            diag_EnterDiagScreen();
            emit exitDiagScreen();
            enterDiagList.clear();
            return true;
        }
        else{
            return false;
        }
    }
    else{
        enterDiagList.clear();
        return false;
    }
}

bool DiagScreen::getIsDiagScreen()
{
    return isDiagScreen;
}

void DiagScreen::diag_EnterDiagScreen()
{
    isDiagScreen = true;
    setselectedItem(DIAGSELECTITEM_MONITORCHECK);
    setcurrentChild1Page(DIAGCHILEDSCREEN_MENU);
}

void DiagScreen::diag_ExitDiagScreen()
{
    isDiagScreen = false;
    setcurrentChild1Page(DIAGCHILEDSCREEN_NONE);
    emit exitDiagScreen();
}
//class DiagPage
//{
//    DiagPage(){
//        _currentIndex = 0;
//    }

//    void handleKey(int key, int type)
//    {
//        if(HDKEY_UP == key && KEY_OFF == type)
//        {
////            _currentIndex = _currentIndex + 1 > _itemTypeList.length() - 1 ? _itemTypeList.length() - 1 : _currentIndex + 1;
//            notifyItem(_currentIndex);
//        }
//        else if(HDKEY_DOWN == key && KEY_OFF == type)
//        {
////             _currentIndex = _currentIndex - 1 < 0 ? 0 : _currentIndex - 1;
//             notifyItem(_currentIndex);
//        }
//        else if(HDKEY_UP == key && KEY_OUT_OFF == type)
//        {
//            emit notifyPage(_itemTypeList.at(_currentIndex));
//        }
//    }

//    void updatePageList(QList<ITEMTYPE> itemTypeList)
//    {
//        foreach (ITEMTYPE item, itemTypeList) {
//            _itemTypeList.append(item);
//        }
//    }
//};

