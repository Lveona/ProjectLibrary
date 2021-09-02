#ifndef PopupScreen_H
#define PopupScreen_H

#include <QObject>
#include "BaseScreen.h"
#include "Singleton.h"
#include <QString>
#include "popupFaultQuery.h"


class DataObject;
class QQuickView;
class Popup;
class UniqPopAddInfo;

class DataObject: public QObject
{
    Q_OBJECT

    // for CarDoors
    Q_PROPERTY(bool hood READ hood WRITE sethood NOTIFY hoodChanged)
    Q_PROPERTY(bool flDoor READ flDoor WRITE setflDoor NOTIFY flDoorChanged)
    Q_PROPERTY(bool frDoor READ frDoor WRITE setfrDoor NOTIFY frDoorChanged)
    Q_PROPERTY(bool rlDoor READ rlDoor WRITE setrlDoor NOTIFY rlDoorChanged)
    Q_PROPERTY(bool rrDoor READ rrDoor WRITE setrrDoor NOTIFY rrDoorChanged)
    Q_PROPERTY(bool tail READ tail WRITE settail NOTIFY tailChanged)
    Q_PROPERTY(bool isWarning READ isWarning WRITE setIsWarning NOTIFY isWarningChanged)
    // for Tyres
    Q_PROPERTY(int fLTyreSts READ fLTyreSts WRITE setFLTyreSts NOTIFY fLTyreStsChanged)
    Q_PROPERTY(int fRTyreSts READ fRTyreSts WRITE setFRTyreSts NOTIFY fRTyreStsChanged)
    Q_PROPERTY(int rLTyreSts READ rLTyreSts WRITE setRLTyreSts NOTIFY rLTyreStsChanged)
    Q_PROPERTY(int rRTyreSts READ rRTyreSts WRITE setRRTyreSts NOTIFY rRTyreStsChanged)
    Q_PROPERTY(QString    fLPRESSURE READ fLPRESSURE WRITE setFLPRESSURE NOTIFY fLPRESSUREChanged)
    Q_PROPERTY(QString    fRPRESSURE READ fRPRESSURE WRITE setFRPRESSURE NOTIFY fRPRESSUREChanged)
    Q_PROPERTY(QString    rLPRESSURE READ rLPRESSURE WRITE setRLPRESSURE NOTIFY rLPRESSUREChanged)
    Q_PROPERTY(QString    rRPRESSURE READ rRPRESSURE WRITE setRRPRESSURE NOTIFY rRPRESSUREChanged)
    Q_PROPERTY(QString    fLTEMP READ fLTEMP WRITE setFLTEMP NOTIFY fLTEMPChanged)
    Q_PROPERTY(QString    fRTEMP READ fRTEMP WRITE setFRTEMP NOTIFY fRTEMPChanged)
    Q_PROPERTY(QString    rLTEMP READ rLTEMP WRITE setRLTEMP NOTIFY rLTEMPChanged)
    Q_PROPERTY(QString    rRTEMP READ rRTEMP WRITE setRRTEMP NOTIFY rRTEMPChanged)
    Q_PROPERTY(bool       tyreWarnningLine_FL READ tyreWarnningLine_FL WRITE settyreWarnningLine_FL NOTIFY tyreWarnningLine_FLChanged)
    Q_PROPERTY(bool       tyreWarnningLine_FR READ tyreWarnningLine_FR WRITE settyreWarnningLine_FR NOTIFY tyreWarnningLine_FRChanged)
    Q_PROPERTY(bool       tyreWarnningLine_RL READ tyreWarnningLine_RL WRITE settyreWarnningLine_RL NOTIFY tyreWarnningLine_RLChanged)
    Q_PROPERTY(bool       tyreWarnningLine_RR READ tyreWarnningLine_RR WRITE settyreWarnningLine_RR NOTIFY tyreWarnningLine_RRChanged)
    Q_PROPERTY(QString    tyreUnit READ tyreUnit WRITE settyreUnit NOTIFY tyreUnitChanged)
//    Q_PROPERTY(QString    rRTEMP READ rRTEMP WRITE setRRTEMP NOTIFY rRTEMPChanged)
    Q_PROPERTY(int        tyreWarnningIcon READ tyreWarnningIcon WRITE settyreWarnningIcon NOTIFY tyreWarnningIconChanged)

    Q_PROPERTY(QString    displayFLValue READ displayFLValue WRITE setdisplayFLValue NOTIFY displayFLValueChanged)
    Q_PROPERTY(QString    displayFRValue READ displayFRValue WRITE setdisplayFRValue NOTIFY displayFRValueChanged)
    Q_PROPERTY(QString    displayRLValue READ displayRLValue WRITE setdisplayRLValue NOTIFY displayRLValueChanged)
    Q_PROPERTY(QString    displayRRValue READ displayRRValue WRITE setdisplayRRValue NOTIFY displayRRValueChanged)

    // for SeatBelt
    Q_PROPERTY(bool mainSeat       READ mainSeat       WRITE setmainSeat       NOTIFY mainSeatChanged)
    Q_PROPERTY(bool copilotSeat    READ copilotSeat    WRITE setcopilotSeat    NOTIFY copilotSeatChanged)
    Q_PROPERTY(bool rearLeftSeat   READ rearLeftSeat   WRITE setrearLeftSeat   NOTIFY rearLeftSeatChanged)
    Q_PROPERTY(bool rearMiddleSeat READ rearMiddleSeat WRITE setrearMiddleSeat NOTIFY rearMiddleSeatChanged)
    Q_PROPERTY(bool rearRightSeat  READ rearRightSeat  WRITE setrearRightSeat  NOTIFY rearRightSeatChanged)
    Q_PROPERTY(bool vertical_View  READ vertical_View  WRITE setVertical_View  NOTIFY vertical_ViewChanged)

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString text READ text WRITE settext NOTIFY textChanged)
    Q_PROPERTY(QString iconname READ iconname WRITE seticonname NOTIFY iconnameChanged)
    Q_PROPERTY(int priorityvalue READ priorityvalue WRITE setPriorityvalue NOTIFY priorityvalueChanged)

public:

    DataObject(){}
    DataObject(const QString &name,
               const QString &text,
               const QString &iconname,
               const int &priorityvalue):
                m_FLTyreSts(0x00),
                m_FRTyreSts(0x00),
                m_RLTyreSts(0x00),
                m_RRTyreSts(0x00),
                m_tyreWarnningIcon(0x00),
                m_name(name),
                m_text(text),
                m_iconname(iconname),
                m_priorityvalue(priorityvalue),
                m_FLPRESSURE("-.-"),
                m_FRPRESSURE("-.-"),
                m_RLPRESSURE("-.-"),
                m_RRPRESSURE("-.-"),
                m_FLTEMP("--"),
                m_FRTEMP("--"),
                m_RLTEMP("--"),
                m_RRTEMP("--"),
                m_tyreUnit("bar"),
                m_DisplayFLValue("-.-"),
                m_DisplayFRValue("-.-"),
                m_DisplayRLValue("-.-"),
                m_DisplayRRValue("-.-"),
                m_hood(false),
                m_flDoor(false),
                m_frDoor(false),
                m_rlDoor(false),
                m_rrDoor(false),
                m_tail(false),
                m_tyreWarnningLine_FL(false),
                m_tyreWarnningLine_FR(false),
                m_tyreWarnningLine_RL(false),
                m_tyreWarnningLine_RR(false),
                m_mainSeat(false),
                m_copilotSeat(false),
                m_rearLeftSeat(false),
                m_rearMiddleSeat(false),
                m_rearRightSeat(false),
                m_isWarning(false),
                m_vertical_View(false){}
    ~DataObject(){}
    enum COLORTYPEQML
    {
        COLORTYPEQML_NONE = 0,
        COLORTYPEQML_GREEN,
        COLORTYPEQML_WHITE,
        COLORTYPEQML_RED,
        COLORTYPEQML_YELLOW,
        COLORTYPEQML_GRAY,
    };
    QString name() const{return m_name;}
    void setName(const QString &name);

    QString text() const{return m_text;}
    void settext(const QString &text);

    QString iconname() const{return m_iconname;}
    void seticonname(const QString &iconname);

    int priorityvalue() const{return m_priorityvalue;}
    void setPriorityvalue(const int &priorityvalue);

    bool hood() const{return m_hood;}
    void sethood(const bool &hood);

    bool flDoor() const{return m_flDoor;}
    void setflDoor(const bool &flDoor);

    bool frDoor() const{return m_frDoor;}
    void setfrDoor(const bool &frDoor);

    bool rlDoor() const{return m_rlDoor;}
    void setrlDoor(const bool &rlDoor);

    bool rrDoor() const{return m_rrDoor;}
    void setrrDoor(const bool &rrDoor);

    bool tail() const{return m_tail;}
    void settail(const bool &tail);

    int fLTyreSts() const{return m_FLTyreSts;}
    void setFLTyreSts(const int &fLTyreSts);

    int fRTyreSts() const{return m_FRTyreSts;}
    void setFRTyreSts(const int &fRTyreSts);

    int rLTyreSts() const{return m_RLTyreSts;}
    void setRLTyreSts(const int &rLTyreSts);

    int rRTyreSts() const{return m_RRTyreSts;}
    void setRRTyreSts(const int &rRTyreSts);

    QString fLPRESSURE() const{return m_FLPRESSURE;}
    void setFLPRESSURE(const QString  &fLPRESSURE);

    QString fRPRESSURE() const{return m_FRPRESSURE;}
    void setFRPRESSURE(const QString  &fRPRESSURE);

    QString  rLPRESSURE() const{return m_RLPRESSURE;}
    void setRLPRESSURE(const QString  &rLPRESSURE);

    QString  rRPRESSURE() const{return m_RRPRESSURE;}
    void setRRPRESSURE(const QString  &rRPRESSURE);

    QString fLTEMP() const{return m_FLTEMP;}
    void setFLTEMP(const QString  &fLTEMP);

    QString fRTEMP() const{return m_FRTEMP;}
    void setFRTEMP(const QString  &fRTEMP);

    QString rLTEMP() const{return m_RLTEMP;}
    void setRLTEMP(const QString  &rLTEMP);

    QString  rRTEMP() const{return m_RRTEMP;}
    void setRRTEMP(const QString  &rRTEMP);

    bool tyreWarnningLine_FL() const{return m_tyreWarnningLine_FL;}
    void settyreWarnningLine_FL(const bool   &tyreWarnningLine_FL);

    bool tyreWarnningLine_FR() const{return m_tyreWarnningLine_FR;}
    void settyreWarnningLine_FR(const bool  &tyreWarnningLine_FR);

    bool tyreWarnningLine_RL() const{return m_tyreWarnningLine_RL;}
    void settyreWarnningLine_RL(const bool   &tyreWarnningLine_RL);

    bool tyreWarnningLine_RR() const{return m_tyreWarnningLine_RR;}
    void settyreWarnningLine_RR(const bool    &tyreWarnningLine_RR);

    int tyreWarnningIcon() const{return m_tyreWarnningIcon;}
    void settyreWarnningIcon(const int &tyreWarnningIcon);

    QString  tyreUnit() const{return m_tyreUnit;}
    void settyreUnit(const QString  &tyreUnit);

    QString  displayFLValue() const{return m_DisplayFLValue;}
    void setdisplayFLValue(const QString  &displayFLValue);

    QString  displayFRValue() const{return m_DisplayFRValue;}
    void setdisplayFRValue(const QString  &displayFRValue);

    QString  displayRLValue() const{return m_DisplayRLValue;}
    void setdisplayRLValue(const QString  &displayRLValue);

    QString  displayRRValue() const{return m_DisplayRRValue;}
    void setdisplayRRValue(const QString  &displayRRValue);

    bool mainSeat() const{return m_mainSeat;}
    void setmainSeat(const bool   &_mainSeat);

    bool copilotSeat() const{return m_copilotSeat;}
    void setcopilotSeat(const bool   &_copilotSeat);

    bool rearLeftSeat() const{return m_rearLeftSeat;}
    void setrearLeftSeat(const bool   &_rearLeftSeat);

    bool rearMiddleSeat() const{return m_rearMiddleSeat;}
    void setrearMiddleSeat(const bool   &_rearMiddleSeat);

    bool rearRightSeat() const{return m_rearRightSeat;}
    void setrearRightSeat(const bool   &_rearRightSeat);

signals:
    void nameChanged();
    void iconnameChanged();
    void priorityvalueChanged();
    void textChanged();
    void hoodChanged();
    void flDoorChanged();
    void frDoorChanged();
    void rlDoorChanged();
    void rrDoorChanged();
    void tailChanged();

    void fLTyreStsChanged(void);
    void fRTyreStsChanged(void);
    void rLTyreStsChanged(void);
    void rRTyreStsChanged(void);
    void fLPRESSUREChanged(void);
    void fRPRESSUREChanged(void);
    void rLPRESSUREChanged(void);
    void rRPRESSUREChanged(void);
    void fLTEMPChanged(void);
    void fRTEMPChanged(void);
    void rLTEMPChanged(void);
    void rRTEMPChanged(void);
    void tyreWarnningLine_FLChanged(void);
    void tyreWarnningLine_FRChanged(void);
    void tyreWarnningLine_RLChanged(void);
    void tyreWarnningLine_RRChanged(void);
    void tyreWarnningIconChanged(void);
    void tyreUnitChanged(void);
    void displayFLValueChanged(void);
    void displayFRValueChanged(void);
    void displayRLValueChanged(void);
    void displayRRValueChanged(void);

    void mainSeatChanged(void);
    void copilotSeatChanged(void);
    void rearLeftSeatChanged(void);
    void rearMiddleSeatChanged(void);
    void rearRightSeatChanged(void);

    void isWarningChanged(bool isWarning);

    void vertical_ViewChanged(bool vertical_View);

public:
    int m_FLTyreSts;
    int m_FRTyreSts;
    int m_RLTyreSts;
    int m_RRTyreSts;
    int m_tyreWarnningIcon;     // 0x00:三角感叹警示 0x01:电池电量低
    QString m_name;
    QString m_text;
    QString m_iconname;
    int m_priorityvalue;
    QString m_FLPRESSURE;
    QString m_FRPRESSURE;
    QString m_RLPRESSURE;
    QString m_RRPRESSURE;
    QString m_FLTEMP;
    QString m_FRTEMP;
    QString m_RLTEMP;
    QString m_RRTEMP;
    QString m_tyreUnit;
    QString m_DisplayFLValue;
    QString m_DisplayFRValue;
    QString m_DisplayRLValue;
    QString m_DisplayRRValue;
    bool m_hood;
    bool m_flDoor;
    bool m_frDoor;
    bool m_rlDoor;
    bool m_rrDoor;
    bool m_tail;
    bool m_tyreWarnningLine_FL;
    bool m_tyreWarnningLine_FR;
    bool m_tyreWarnningLine_RL;
    bool m_tyreWarnningLine_RR;
    bool m_mainSeat;
    bool m_copilotSeat;
    bool m_rearLeftSeat;
    bool m_rearMiddleSeat;
    bool m_rearRightSeat;
    bool m_isWarning;
    bool m_vertical_View;

    bool isWarning() const
    {
        return m_isWarning;
    }
    bool vertical_View() const
    {
        return m_vertical_View;
    }

public slots:
    void setIsWarning(bool isWarning)
    {
        if (m_isWarning == isWarning)
            return;

        m_isWarning = isWarning;
        emit isWarningChanged(m_isWarning);
    }
    void setVertical_View(bool vertical_View)
    {
        if (m_vertical_View == vertical_View)
            return;

        m_vertical_View = vertical_View;
        emit vertical_ViewChanged(m_vertical_View);
    }
};


class PopupScreen:  public CBaseScreen, public CSingleton<PopupScreen>
{
    Q_OBJECT
    friend class CSingleton<PopupScreen>;

    // connect to QML
    Q_PROPERTY(DataObject* popupDataObject READ getpopupDataObject WRITE setpopupDataObject NOTIFY popupDataObjectChanged)
    // for singleTheme Pop BG
    Q_PROPERTY(bool isGlobalNaviSource  READ isGlobalNaviSource  WRITE setisGlobalNaviSource  NOTIFY isGlobalNaviSourceChanged)
    Q_PROPERTY(QVariant kdrvStblt READ kdrvStblt WRITE setKdrvStblte NOTIFY kdrvStbltChanged)
    Q_PROPERTY(QVariant kdrvVisible READ kdrvVisible WRITE setKdrvVisible NOTIFY kdrvVisibleChanged)
    Q_PROPERTY(QVariant kpasStblt READ kpasStblt WRITE setKpasStblte NOTIFY kpasStbltChanged)
    Q_PROPERTY(QVariant kpasVisible READ kpasVisible WRITE setKpasVisible NOTIFY kpasVisibleChanged)
    Q_PROPERTY(QVariant krlStblt READ krlStblt WRITE setKrlStblte NOTIFY krlStbltChanged)
    Q_PROPERTY(QVariant krlVisible READ krlVisible WRITE setKrlVisible NOTIFY krlVisibleChanged)
    Q_PROPERTY(QVariant krrStblt READ krrStblt WRITE setKrrStblte NOTIFY krrStbltChanged)
    Q_PROPERTY(QVariant krrVisible READ krrVisible WRITE setKrrVisible NOTIFY krrVisibleChanged)
    Q_PROPERTY(QVariant krmStblt READ krmStblt WRITE setKrmStblte NOTIFY krmStbltChanged)
    Q_PROPERTY(QVariant krmVisible READ krmVisible WRITE setKrmVisible NOTIFY krmVisibleChanged)

    Q_PROPERTY(QVariant  limitSpeed READ limitSpeed WRITE setLimitSpeed NOTIFY limitSpeedChanged)

    Q_PROPERTY(QVariant  redCardNumber READ redCardNumber WRITE setRedCardNumber NOTIFY redCardNumberChanged)
    Q_PROPERTY(QVariant  yellowCardNumber READ yellowCardNumber WRITE setYellowCardNumber NOTIFY yellowCardNumberChanged)

    Q_PROPERTY(QVariant  redCardCurrentIndex READ redCardCurrentIndex WRITE setRedCardCurrentIndex NOTIFY redCardCurrentIndexChanged)
    Q_PROPERTY(QVariant  yellowCardCurrentIndex READ yellowCardCurrentIndex WRITE setYellowCardCurrentIndex NOTIFY yellowCardCurrentIndexChanged)

    Q_PROPERTY(QVariant  yellowCardListHide READ yellowCardListHide WRITE setYellowCardListHide NOTIFY yellowCardListHideChanged)

    Q_PROPERTY(QVariant tempwarning_LF READ tempwarning_LF WRITE setTempwarning_LF NOTIFY tempwarning_LFChanged)
    Q_PROPERTY(QVariant tempwarning_RF READ tempwarning_RF WRITE setTempwarning_RF NOTIFY tempwarning_RFChanged)
    Q_PROPERTY(QVariant tempwarning_RR READ tempwarning_RR WRITE setTempwarning_RR NOTIFY tempwarning_RRChanged)
    Q_PROPERTY(QVariant tempwarning_LR READ tempwarning_LR WRITE setTempwarning_LR NOTIFY tempwarning_LRChanged)

public:
    PopupScreen();
    ~PopupScreen();
    typedef void ( PopupScreen::* FunctionParser )(QVariant value);
    virtual void startControl();
    void createCtrl(QQuickView *view);

#ifdef _WIN64_DEBUG_SW_POP
    Q_INVOKABLE QString _DEBUG_GET_SYSTIME(void);
    Q_INVOKABLE void _DEBUG_NEXT_POP(void);
    Q_INVOKABLE void _DEBUG_PREV_POP(void);
    //Q_INVOKABLE void _DEBUG_CANCELKEY(int);
    void _DEBUG_NEXTPREV_POP(int type);

    QString  getCATEGORY() const{return m_CATEGORY;}
    void setCATEGORY(const QString  &CATEGORY){  m_CATEGORY = CATEGORY; emit CATEGORYChanged();}

    QString  getlevelID() const{return m_levelID;}
    void setlevelID(const QString  &levelID){  m_levelID = levelID; emit levelIDChanged();}
#endif

    QVariant kdrvStblt() const
    {
        return m_kdrvStblt;
    }

    QVariant kdrvVisible() const
    {
        return m_kdrvVisible;
    }

    QVariant kpasStblt() const
    {
        return m_kpasStblt;
    }

    QVariant kpasVisible() const
    {
        return m_kpasVisible;
    }

    QVariant krlStblt() const
    {
        return m_krlStblt;
    }

    QVariant krlVisible() const
    {
        return m_krlVisible;
    }

    QVariant krrStblt() const
    {
        return m_krrStblt;
    }

    QVariant krrVisible() const
    {
        return m_krrVisible;
    }

    QVariant krmStblt() const
    {
        return m_krmStblt;
    }

    QVariant krmVisible() const
    {
        return m_krmVisible;
    }

    QVariant tempwarning_LF() const
    {
        return m_tempwarning_LF;
    }

    QVariant tempwarning_RF() const
    {
        return m_tempwarning_RF;
    }

    QVariant tempwarning_RR() const
    {
        return m_tempwarning_RR;
    }

    QVariant tempwarning_LR() const
    {
        return m_tempwarning_LR;
    }

    QVariant limitSpeed() const
    {
        return m_limitSpeed;
    }

    QVariant redCardNumber() const
    {
        return m_redCardNumber;
    }

    QVariant yellowCardNumber() const
    {
        return m_yellowCardNumber;
    }

    QVariant redCardCurrentIndex() const
    {
        return m_redCardCurrentIndex;
    }

    QVariant yellowCardCurrentIndex() const
    {
        return m_yellowCardCurrentIndex;
    }

    QVariant yellowCardListHide() const
    {
        return m_yellowCardListHide;
    }

public slots:
    void SetProperty(int name,QVariant value);
    void SetProperty(Popup * ptPop);
    void SetProperty(QList<PopupFaultQuery> pop);
    void SetProperty(const UniqPopAddInfo*);
    void SetProperty_show_toast(QString name , QString iconname, int category);
    void SetProperty_hide_toast(QString name , QString iconname, int category);
    void SetProperty_show_adas_toast(QString name , QString iconname, int category);
    void SetProperty_hide_adas_toast(QString name , QString iconname, int category);
    void SetPropertyGlobalNaviSource(bool _isGlobalNaviSource);

    DataObject* getpopupDataObject(){return m_popupDataObject;}
    void setpopupDataObject(DataObject* popupDataObject){
        Q_UNUSED(popupDataObject);
        emit popupDataObjectChanged();
    }

    bool isGlobalNaviSource() const{return m_isGlobalNaviSource;}
    void setisGlobalNaviSource(const bool   &_isGlobalNaviSource);

    void setKdrvStblte(QVariant kdrvStblt)
    {
        if (m_kdrvStblt == kdrvStblt)
            return;

        m_kdrvStblt = kdrvStblt;
        emit kdrvStbltChanged(m_kdrvStblt);
    }

    void setKdrvVisible(QVariant kdrvVisible)
    {
        if (m_kdrvVisible == kdrvVisible)
            return;

        m_kdrvVisible = kdrvVisible;
        emit kdrvVisibleChanged(m_kdrvVisible);
    }

    void setKpasStblte(QVariant kpasStblt)
    {
        if (m_kpasStblt == kpasStblt)
            return;
        m_kpasStblt = kpasStblt;
        emit kpasStbltChanged(m_kpasStblt);
    }

    void setKpasVisible(QVariant kpasVisible)
    {
        if (m_kpasVisible == kpasVisible)
            return;

        m_kpasVisible = kpasVisible;
        emit kpasVisibleChanged(m_kpasVisible);
    }

    void setKrlStblte(QVariant krlStblt)
    {
        if (m_krlStblt == krlStblt)
            return;

        m_krlStblt = krlStblt;
        emit krlStbltChanged(m_krlStblt);
    }

    void setKrlVisible(QVariant krlVisible)
    {
        if (m_krlVisible == krlVisible)
            return;

        m_krlVisible = krlVisible;
        emit krlVisibleChanged(m_krlVisible);
    }

    void setKrrStblte(QVariant krrStblt)
    {
        if (m_krrStblt == krrStblt)
            return;

        m_krrStblt = krrStblt;
        emit krrStbltChanged(m_krrStblt);
    }

    void setKrrVisible(QVariant krrVisible)
    {
        if (m_krrVisible == krrVisible)
            return;

        m_krrVisible = krrVisible;
        emit krrVisibleChanged(m_krrVisible);
    }

    void setKrmStblte(QVariant krmStblt)
    {
        if (m_krmStblt == krmStblt)
            return;

        m_krmStblt = krmStblt;
        emit krmStbltChanged(m_krmStblt);
    }

    void setKrmVisible(QVariant krmVisible)
    {
        if (m_krmVisible == krmVisible)
            return;

        m_krmVisible = krmVisible;
        emit krmVisibleChanged(m_krmVisible);
    }

    void setTempwarning_LF(QVariant tempwarning_LF)
    {
        if (m_tempwarning_LF == tempwarning_LF)
            return;

        m_tempwarning_LF = tempwarning_LF;
        emit tempwarning_LFChanged(m_tempwarning_LF);
    }

    void setTempwarning_RF(QVariant tempwarning_RF)
    {
        if (m_tempwarning_RF == tempwarning_RF)
            return;

        m_tempwarning_RF = tempwarning_RF;
        emit tempwarning_RFChanged(m_tempwarning_RF);
    }

    void setTempwarning_RR(QVariant tempwarning_RR)
    {
        if (m_tempwarning_RR == tempwarning_RR)
            return;

        m_tempwarning_RR = tempwarning_RR;
        emit tempwarning_RRChanged(m_tempwarning_RR);
    }

    void setTempwarning_LR(QVariant tempwarning_LR)
    {
        if (m_tempwarning_LR == tempwarning_LR)
            return;

        m_tempwarning_LR = tempwarning_LR;
        emit tempwarning_LRChanged(m_tempwarning_LR);
    }

    void setLimitSpeed(QVariant limitSpeed)
    {
        if (m_limitSpeed == limitSpeed)
            return;

        m_limitSpeed = limitSpeed;
        emit limitSpeedChanged(m_limitSpeed);
    }

    void setRedCardNumber(QVariant redCardNumber)
    {
        if (m_redCardNumber == redCardNumber)
            return;

        m_redCardNumber = redCardNumber;
        emit redCardNumberChanged(m_redCardNumber);
    }

    void setYellowCardNumber(QVariant yellowCardNumber)
    {
        if (m_yellowCardNumber == yellowCardNumber)
            return;

        m_yellowCardNumber = yellowCardNumber;
        emit yellowCardNumberChanged(m_yellowCardNumber);
    }

    void setRedCardCurrentIndex(QVariant redCardCurrentIndex)
    {
        if (m_redCardCurrentIndex == redCardCurrentIndex)
            return;

        m_redCardCurrentIndex = redCardCurrentIndex;
        emit redCardCurrentIndexChanged(m_redCardCurrentIndex);
    }

    void setYellowCardCurrentIndex(QVariant yellowCardCurrentIndex)
    {
        if (m_yellowCardCurrentIndex == yellowCardCurrentIndex)
            return;

        m_yellowCardCurrentIndex = yellowCardCurrentIndex;
        emit yellowCardCurrentIndexChanged(m_yellowCardCurrentIndex);
    }

    void setYellowCardListHide(QVariant yellowCardListHide)
    {
        if (m_yellowCardListHide == yellowCardListHide)
            return;

        m_yellowCardListHide = yellowCardListHide;
        emit yellowCardListHideChanged(m_yellowCardListHide);
    }

signals:
    void addToast(QString name, QString iconname, char category);
    void delToast(QString name, QString iconname, char category);
    void addAdasToast(QString name, QString iconname, char category);
    void delAdasToast(QString name, QString iconname, char category);
    void popupDataObjectChanged();
    void isGlobalNaviSourceChanged(void);
#ifdef _WIN64_DEBUG_SW_POP
    void CATEGORYChanged();
    void levelIDChanged();
#endif

    void kdrvStbltChanged(QVariant kdrvStblt);

    void kdrvVisibleChanged(QVariant kdrvVisible);

    void kpasStbltChanged(QVariant kpasStblt);

    void kpasVisibleChanged(QVariant kpasVisible);

    void krlStbltChanged(QVariant krlStblt);

    void krlVisibleChanged(QVariant krlVisible);

    void krrStbltChanged(QVariant krrStblt);

    void krrVisibleChanged(QVariant krrVisible);

    void krmStbltChanged(QVariant krmStblt);

    void krmVisibleChanged(QVariant krmVisible);

    void tempwarning_LFChanged(QVariant tempwarning_LF);

    void tempwarning_RFChanged(QVariant tempwarning_RF);

    void tempwarning_RRChanged(QVariant tempwarning_RR);

    void tempwarning_LRChanged(QVariant tempwarning_LR);

    void limitSpeedChanged(QVariant limitSpeed);

    void redCardNumberChanged(QVariant redCardNumber);

    void yellowCardNumberChanged(QVariant yellowCardNumber);

    void redCardCurrentIndexChanged(QVariant redCardCurrentIndex);

    void yellowCardCurrentIndexChanged(QVariant yellowCardCurrentIndex);

    void yellowCardListHideChanged(QVariant yellowCardListHide);

private:
//    void changeTroubleElementforTyrePop(PopTyreSts * info);

private:
//    PopTyreSts * m_popupTyreSts;
    QQuickView* m_view;
    QList<QObject*> m_popupFaultQueryList;
    DataObject * m_popupDataObject;
    QString m_driveModeWarningImagePath;
    QString m_driveModeWarningMsgText;
    bool m_isGlobalNaviSource;
    QVariant m_kdrvStblt;
    QVariant m_kdrvVisible;
    QVariant m_kpasStblt;
    QVariant m_kpasVisible;
    QVariant m_krlStblt;
    QVariant m_krlVisible;
    QVariant m_krrStblt;
    QVariant m_krrVisible;
    QVariant m_krmStblt;
    QVariant m_krmVisible;
    QVariant m_tempwarning_LF;
    QVariant m_tempwarning_RF;
    QVariant m_tempwarning_RR;
    QVariant m_tempwarning_LR;
    QVariant m_limitSpeed;
    QVariant m_redCardNumber;
    QVariant m_yellowCardNumber;
    QVariant m_redCardCurrentIndex;
    QVariant m_yellowCardCurrentIndex;
    QVariant m_yellowCardListHide;
};


#endif // PopupScreen_H
