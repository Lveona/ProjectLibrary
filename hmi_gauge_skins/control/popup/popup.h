#ifndef POPUP_H
#define POPUP_H

#include <QString>
class PopupSound;

class Popup
{
public:
    Popup(int 		_priorityvalue,
          char 		_category,
          char 		_dispPowerMode,
          QString 			_symbol,
          QString 			_name,
          const PopupSound* _ptSoundInc,
          const int _audio_flag,    //帮助pop声音应用声音策略
          char           _from = 0,    //0:显示队列,1:循环队列
          bool              _store = false):         //是否存故障查询界面
        priorityvalue(_priorityvalue),
        category(_category),
        dispPowerMode(_dispPowerMode),
        symbol(_symbol),
        name(_name),
        ptSoundInc(_ptSoundInc),
        audio_flag(_audio_flag),
        from(_from),
        store(_store){}
    Popup & operator =(const Popup&);
    int       priorityvalue;
    char      category;
    char       dispPowerMode;
    QString          symbol;
    QString          name;
    const PopupSound* ptSoundInc;
    const int audio_flag;
    char       from;
    bool          store;
};

#endif // POPUP_H
