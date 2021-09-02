#ifdef TEMPFUNC
#include "libaudio.h"
#include <QObject>

//#include <QMediaPlayer>
#include <stdio.h>
//#include <QSound>
//#include <QApplication>

#else
#endif

#ifdef TEMPFUNC

//QSound gPopWarningSound("E:/test/A1.wav");

int audio_client_Init(void)
{
//    qDebug()<<"libaudio_Init";

//    gPopWarningSound.setLoops(10000);
//    gPopWarningSound.loops();

//    //return AUDIO_INIT_NG;
    return AUDIO_INIT_OK;
}


//void libaudio_AudioPlay(Audio_ID_Index audio_id,Audio_ReqCmd audio_Cmd)
//{
//    Q_UNUSED(audio_id);
//    Q_UNUSED(audio_Cmd);

////    if(AUDIO_PLAY == audio_Cmd){QSound::play("E:/test/chord.wav");}

//}

void audio_client_Play(Audio_ID_Index audio_id,Audio_ReqCmd audio_Cmd)
{
    Q_UNUSED(audio_id);
    Q_UNUSED(audio_Cmd);

//    if(AUDIO_PLAY == audio_Cmd){
//        if(AUDIO_INDEX_DOORUNCLOSED == audio_id){
//            if(gPopWarningSound.isFinished() == true){
//                //gPopWarningSound.play();
//                qDebug()<<"Play长鸣！";
//            }
//            else{
//                qDebug()<<"Bug! Play前忘了Stop前一个音效！";
//            }
//        }
//        else{
//            if(gPopWarningSound.isFinished() == true){
//                QSound::play("E:/test/chord.wav");
//                qDebug()<<"Play短鸣！";
//            }
//            else{
//                qDebug()<<"Bug! Play前忘了Stop前一个音效！";
//            }
//        }
//    }
//    else{
//        if(AUDIO_INDEX_DOORUNCLOSED == audio_id){
//            if(gPopWarningSound.isFinished() == false){
//                gPopWarningSound.stop();
//                qDebug()<<"Stop长鸣！1";
//            }
//        }
//    }
//    if(AUDIO_PLAY == audio_Cmd){
//        if(AUDIO_INDEX_DOORUNCLOSED_NOTICE == audio_id){
//            if(gPopWarningSound.isFinished() == true){
//                //gPopWarningSound.play();
//                qDebug()<<"Play长鸣！";
//            }
//            else{
//                qDebug()<<"Bug! Play前忘了Stop前一个音效！";
//            }
//        }
//        else{
//            if(gPopWarningSound.isFinished() == true){
//                QSound::play("E:/test/chord.wav");
//                qDebug()<<"Play短鸣！";
//            }
//            else{
//                qDebug()<<"Bug! Play前忘了Stop前一个音效！";
//            }
//        }
//    }
//    else{
//        if(AUDIO_INDEX_DOORUNCLOSED_NOTICE == audio_id){
//            if(gPopWarningSound.isFinished() == false){
//                gPopWarningSound.stop();
//                qDebug()<<"Stop长鸣！1";
//            }
//        }
//    }
////    if(AUDIO_PLAY == audio_Cmd){
////        if(AUDIO_INDEX_DOORUNCLOSED_NOTICE == audio_id){
////            if(gPopWarningSound.isFinished() == true){
////                //gPopWarningSound.play();
////                qDebug()<<"Play长鸣！";
////            }
////            else{
////                qDebug()<<"Bug! Play前忘了Stop前一个音效！";
////            }
////        }
////        else{
////            if(gPopWarningSound.isFinished() == true){
////                QSound::play("E:/test/chord.wav");
////                qDebug()<<"Play短鸣！";
////            }
////            else{
////                qDebug()<<"Bug! Play前忘了Stop前一个音效！";
////            }
////        }
////    }
////    else{
////        if(AUDIO_INDEX_DOORUNCLOSED_NOTICE == audio_id){
////            if(gPopWarningSound.isFinished() == false){
////                gPopWarningSound.stop();
////                qDebug()<<"Stop长鸣！1";
////            }
////        }
////    }
}

//void libaudio_AudioAllStop(void)
//{
////    qDebug()<<"libaudio_AudioAllStop";
//}

void audio_client_AllStop(void)
{
//    qDebug()<<"audio_client_AllStop";
}

#else
#endif
