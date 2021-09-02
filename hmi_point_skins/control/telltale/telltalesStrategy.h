#ifndef TELLTALESSTRATEGY_H
#define TELLTALESSTRATEGY_H

#include <QObject>
#include <QMap>
#include <QVariant>
#include "telltale.h"

class Telltale;
class QMutex;
class TelltaleFlash;
class TelltalesControl;

enum TTMATCHPOWERMODE
{
    TTPOWERMODE_D1 = 0,
    TTPOWERMODE_D2,
    TTPOWERMODE_D3,
    TTPOWERMODE_D1_D2,
};

struct AUTOCHECKTELL{
  Telltale* tell;
  char colorType;
};

class TelltalesStrategy: public QObject
{
    Q_OBJECT

public:
    TelltalesStrategy();
    ~TelltalesStrategy(){}

    void setAutoCheckState(int value);
    void addAutoCheckTell(QList<Telltale*> list);
    int getAutoCheckState();
    int m_autoCheckState;
//    void iC_Can_Info_Send(TELLTALE_IC_CAN_INFO_SEND_ID reqSendID);

signals:
    void PropertyChange(int index, const TellData tell);
    void sendToOtherProcess(QString message_key, QVariant message_value);


public slots:
    void handleTellStrategy(Telltale*);
    void triggerPowerMode(int value);
    void get_timeout500ms();
    void get_timeout10ms();

private:
    QMutex* m_mutex;
    int m_powerMode;

    QMap<int, Telltale*> m_tells;
    QList<AUTOCHECKTELL> m_autoCheckList;
    TelltaleFlash* m_telltaleFlash1HZ;
    TelltaleFlash* m_telltaleFlash2HZ;
    TelltaleFlash* m_telltaleFlash3HZ;
    TelltaleFlash* m_telltaleFlash4HZ;
    TelltalesControl* _TelltalesControl;

    bool setPropertyTell(int id, Telltale* tell);
    void handle(Telltale*);
    bool isMatchPower(Telltale *datamessage);
};

#endif // TELLTALESSTRATEGY_H
