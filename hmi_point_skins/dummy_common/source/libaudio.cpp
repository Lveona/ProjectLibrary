#ifdef TEMPFUNC
#include "libaudio.h"
#include <QObject>

#include <stdio.h>
#else
#endif

#ifdef TEMPFUNC

int audio_client_Init(void)
{
    return 0;
}

void audio_client_Play(Audio_ID_Index audio_id,Audio_ReqCmd audio_Cmd)
{
    Q_UNUSED(audio_id);
    Q_UNUSED(audio_Cmd);

}

void audio_client_AllStop(void)
{
}
#else
#endif
