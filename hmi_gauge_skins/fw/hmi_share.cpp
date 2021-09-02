#include "./include/hmi_share.h"


#include <QDebug>
#include "Singleton.h"
#include "BaseControl.h"
#include "BaseScreen.h"
#include "mysharememory.h"
#include <QTime>

int g_hmiPowerMode = 0;
QMap<RpcMsgValueId,SingleMessage> gMapMsgValues;
bool getMsgValue(const RpcMsgValueId& msgId,SingleMessage& message){
    QMap<RpcMsgValueId,SingleMessage>::iterator i = gMapMsgValues.find(msgId);
    if (i != gMapMsgValues.end() && i.key() == msgId) {
        message = i.value();
        return true;
    }
    return false;
}

//max: 周期数
//type: 单次/循环
HMICustomTimer::HMICustomTimer(int _max, bool _single)
    :m_Max(_max),m_timercnt(-1),m_single(_single){}

void HMICustomTimer::update(){
    if(m_timercnt >= 0)
    {
        m_timercnt++;
        if(m_timercnt >= m_Max)
        {
            m_timercnt = m_single?-1:0;
            emit timeout();
        }
    }
}

void HMICustomTimer::reset(){m_timercnt = 0;}

void HMICustomTimer::stop(){m_timercnt = -1;}

void HMICustomTimer::start(){m_timercnt = 0;}

bool HMICustomTimer::running(){
    if(m_timercnt > -1) return true;
    return false;
}

int HMICustomTimer::getTimerCnt()
{
    return m_timercnt;
}

static QList<Audio_ReqCmd> _list_state;
static QList<int> _list_id_counter;

HMIAudioCtrl::HMIAudioCtrl()
{
    //init
    int len = (int)WARNING_STATE_MAX;
    for(int i=0;i<=len;i++){
        _list_state.append(AUDIO_STOP);
    }

    int len2 = (int)AUDIO_INDEX_MAX;
    for(int i=0;i<=len2;i++){
        _list_id_counter.append(0);
    }
}

void HMIAudioCtrl::setAudioStatByPower(WARNING_STATE state, int audio_id, Audio_ReqCmd audio_Cmd)
{
    if(g_hmiPowerMode == POWERMODE_ANIMATION){
        setAudioState( state,  audio_id,  AUDIO_STOP);
    }
    else{
        setAudioState( state,  audio_id,  audio_Cmd);
    }
}

void HMIAudioCtrl::setAudioState(WARNING_STATE state, int audio_id, Audio_ReqCmd audio_Cmd)
{
    //play(根据情况)->libaudio
    //stop(根据计数)->libaudio
    Audio_ReqCmd c_state = _list_state.at((int)state);
    _list_state[(int)state] = audio_Cmd;

    if(AUDIO_STOP == c_state &&  AUDIO_PLAY == audio_Cmd){
        //0->1
        _list_id_counter[audio_id] = _list_id_counter[audio_id] + 1;
        audio_client_Play(static_cast<Audio_ID_Index>(audio_id), audio_Cmd);
    }
    else if(AUDIO_PLAY == c_state &&  AUDIO_STOP == audio_Cmd){
        //1->0
        _list_id_counter[audio_id] = max(_list_id_counter[audio_id] - 1, 0);
        if(0 == _list_id_counter[audio_id]){
            audio_client_Play(static_cast<Audio_ID_Index>(audio_id), audio_Cmd);
        }
    }
    else{}
}

static QMap<QString, QString> _map;

void HMIProcessTime::process(QString tag)
{
    QString last = _map.value(tag, QString());
    if(QString() == last){
        //add
        _map.insert(tag, QTime::currentTime().toString("h.mm.s.zzz"));
    }
    else{
        //calc
        QTime lastTime = QTime::fromString(last, "h.mm.s.zzz");
        int delay = lastTime.msecsTo(QTime::currentTime());
        (void)delay;

//#define HMIProcessTimeMACRO
#ifdef HMIProcessTimeMACRO
        LOGPRINT( QString("Tag: %1, Delay: %2ms").arg(tag).arg(delay) );
#endif
        _map.insert(tag, QString());
    }
}
