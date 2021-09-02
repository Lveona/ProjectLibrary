#ifndef DiagSCREEN_H
#define DiagSCREEN_H

#include "diagControl.h"
#include <QTime>

#define DIAG_POPUP_ACTION_CMD(pageID, popType, msgID)  (pageID*100+popType*10+msgID)

class QQuickView;

enum DIAGCHILEDSCREEN{
    DIAGCHILEDSCREEN_NONE = 0,              //非电检画面
    DIAGCHILEDSCREEN_MENU,                  //电检菜单画面
    DIAGCHILEDSCREEN_MONITORCHECK,          //monitor检查画面
    DIAGCHILEDSCREEN_RESET,                 //恢复出厂设置画面
};

enum DIAGSELECTITEM{
    DIAGSELECTITEM_MONITORCHECK = 0,        //monitor检查
    DIAGSELECTITEM_CLEARTOTALMILE,          //里程清零
    DIAGSELECTITEM_RESET,                   //恢复出厂设置
    DIAGSELECTITEM_EXIT,                    //退出电检
};

enum DIAGMONITORCHECK{
    DIAG_MONICHK_BLACK    = 0x00,
    DIAG_MONICHK_WHITE    = 0x01,
    DIAG_MONICHK_GRAY     = 0x02,
    DIAG_MONICHK_COLORBAR = 0x03,
    DIAG_MONICHK_RED      = 0x04,
    DIAG_MONICHK_GREEN    = 0x05,
    DIAG_MONICHK_BLUE     = 0x06,
    DIAG_MONICHK_NUM
};

enum DIAGPOP{
    DIAGPOP_EXIT = 0,               //退出POP
    DIAGPOP_CLEARTOTALMILE,   //确认清除保养里程POP画面
    DIAGPOP_RESET,            //确认恢复出厂设置POP画面
};

class DiagScreen:  public CBaseScreen, public CSingleton<DiagScreen>
{
    Q_OBJECT
    friend class CSingleton<DiagScreen>;
    // connect to QML
    Q_PROPERTY(int selectedItem             READ selectedItem               WRITE setselectedItem               NOTIFY selectedItemChanged)
    Q_PROPERTY(int currentChild1Page        READ currentChild1Page          WRITE setcurrentChild1Page          NOTIFY currentChild1PageChanged)
    Q_PROPERTY(int popType                  READ getPopType                 WRITE setPopType                    NOTIFY popTypeChanged)
    Q_PROPERTY(int monitorCheckDisplay      READ monitorCheckDisplay        WRITE setmonitorCheckDisplay        NOTIFY monitorCheckDisplayChanged)
    Q_PROPERTY(bool popBottonOKSlecte       READ popBottonOKSlecte          WRITE setPopBottonOKSlecte          NOTIFY popBottonOKSlecteChanged)
    Q_PROPERTY(int itemMileageClearDisble   READ itemMileageClearDisble     WRITE setitemMileageClearDisble     NOTIFY itemMileageClearDisbleChanged)



public:
    DiagScreen();
    ~DiagScreen();
    int m_selectedItem;
    int m_currentChild1Page;
    int m_popType;
    int m_monitorCheckDisplay;
    bool m_popBottonOKSlecte;
    int m_itemMileageClearDisble;

    virtual void startControl();
    void createCtrl(QQuickView *view);

    bool canEnterDiagScreen(int _key,int _type);
    bool handleEnterDiagScreen(int _key, int _type);
    bool diag_key_pressed_released(int key, int type);
    void diag_EnterDiagScreen();
    void diag_ExitDiagScreen();
    bool getIsDiagScreen();

    bool isDiagScreen;

    int selectedItem() const
    {
        return m_selectedItem;
    }
    int currentChild1Page() const
    {
        return m_currentChild1Page;
    }

    int getPopType() const
    {
        return m_popType;
    }

    int monitorCheckDisplay() const
    {
        return m_monitorCheckDisplay;
    }

    bool popBottonOKSlecte() const
    {
        return m_popBottonOKSlecte;
    }

    int itemMileageClearDisble() const
    {
        return m_itemMileageClearDisble;
    }

public slots:
    void SetProperty(QString name, QVariant value);

    void setselectedItem(int selectedItem)
    {
        if (m_selectedItem == selectedItem)
            return;

        m_selectedItem = selectedItem;
        emit selectedItemChanged(m_selectedItem);
    }
    void setcurrentChild1Page(int currentChild1Page)
    {
        if (m_currentChild1Page == currentChild1Page)
            return;

        m_currentChild1Page = currentChild1Page;
        emit currentChild1PageChanged(m_currentChild1Page);
    }

    void setPopType(int popType)
    {
        if (m_popType == popType)
            return;

        m_popType = popType;
        emit popTypeChanged(m_popType);
    }

    void setmonitorCheckDisplay(int monitorCheckDisplay)
    {
        if (m_monitorCheckDisplay == monitorCheckDisplay)
            return;

        m_monitorCheckDisplay = monitorCheckDisplay;
        emit monitorCheckDisplayChanged(m_monitorCheckDisplay);
    }

    void setPopBottonOKSlecte(bool popBottonOKSlecte)
    {
        if (m_popBottonOKSlecte == popBottonOKSlecte)
            return;

        m_popBottonOKSlecte = popBottonOKSlecte;
        emit popBottonOKSlecteChanged(m_popBottonOKSlecte);
    }

    void setitemMileageClearDisble(int itemMileageClearDisble)
    {
        if (m_itemMileageClearDisble == itemMileageClearDisble)
            return;

        m_itemMileageClearDisble = itemMileageClearDisble;
        emit itemMileageClearDisbleChanged(m_itemMileageClearDisble);
    }

signals:
    void exitDiagScreen();

    void selectedItemChanged(int selectedItem);
    void currentChild1PageChanged(int currentChild1Page);
    void popTypeChanged(int popType);
    void monitorCheckDisplayChanged(int monitorCheckDisplay);
    void popBottonOKSlecteChanged(bool popBottonOKSlecte);
    void itemMileageClearDisbleChanged(int itemMileageClearDisble);
};
//class DiagPage: QObject
//{
//    Q_OBJECT
//public:
//    void handleKey(int key, int type);
//    void handlePop();
//    void updatePageList();

//signals:
//    void notifyItem(int itemIndex);
//    void notifyPage(ITEMTYPE item);

//private:
//    int _currentIndex;
//    QList<ITEMTYPE> _itemTypeList;
//private:
//    DiagPage(){}
//    ~DiagPage(){}
//};

#endif // DiagSCREEN_H
