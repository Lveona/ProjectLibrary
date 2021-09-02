#ifndef UNIQPOPADDINFO_H
#define UNIQPOPADDINFO_H

class PopCarDoor
{
public:
    PopCarDoor():m_HoodSts(0x00),m_FLDoorSts(0x00),m_FRDoorSts(0x00), m_RLDoorSts(0x00),m_RRDoorSts(0x00),m_TailSts(0x00),m_isWarning(false){}
    ~PopCarDoor() {}
    int m_HoodSts;     // 0x01:Open 0x00:Close
    int m_FLDoorSts;   // 0x01:Open 0x00:Close
    int m_FRDoorSts;   // 0x01:Open 0x00:Close
    int m_RLDoorSts;   // 0x01:Open 0x00:Close
    int m_RRDoorSts;   // 0x01:Open 0x00:Close
    int m_TailSts;     // 0x01:Open 0x00:Close
    bool m_isWarning;
};

class PopSeatBelt
{
public:
    PopSeatBelt():m_Vertical_View(false),m_FrontLeftSeat(false),m_FrontRightSeat(false),m_RearLeftSeat(false), m_RearMiddleSeat(false),m_RearRightSeat(false){}
    ~PopSeatBelt() {}
    bool m_Vertical_View;   //是否是俯视图
    bool m_FrontLeftSeat;
    bool m_FrontRightSeat;
    bool m_RearLeftSeat;
    bool m_RearMiddleSeat;
    bool m_RearRightSeat;
};

class PopTyre
{
public:
    PopTyre():m_popupTyreLFWarning(false),m_popupTyreRFWarning(false),m_popupTyreLRWarning(false),m_popupTyreRRWarning(false){}
    ~PopTyre() {}
    bool  m_popupTyreLFWarning ;
    bool  m_popupTyreRFWarning ;
    bool  m_popupTyreLRWarning ;
    bool  m_popupTyreRRWarning ;
};

//胎压在carinfo实现了
class UniqPopAddInfo
{
public:
    UniqPopAddInfo( PopCarDoor  * _ptPopCarDoor,
                    PopSeatBelt * _ptPopSeatBelt,
                    PopTyre * _ptPopTyre):
        ptPopCarDoor(_ptPopCarDoor),
        ptPopSeatBelt(_ptPopSeatBelt),
        ptPopTyre(_ptPopTyre){}
    ~UniqPopAddInfo(){}
    PopCarDoor *  ptPopCarDoor;
    PopSeatBelt * ptPopSeatBelt;
    PopTyre * ptPopTyre;
};

class PopupSound
{
public:
    PopupSound(int _soundType,
               int     _soundPowerMode):
        soundType(_soundType),
        soundPowerMode(_soundPowerMode){}
    PopupSound(){}
    PopupSound & operator =(const PopupSound&);
    int   soundType;
    int       soundPowerMode;
};

#endif // UNIQPOPADDINFO_H
