#ifndef TELLTALEFLASH_H
#define TELLTALEFLASH_H

#include <QObject>
#include <QMap>
#include "telltale.h"

class Telltale;

enum FlashType
{
    FLASHTYPE_NONE=0,
    FLASHTYPE_1HZ,
    FLASHTYPE_2HZ,
    FLASHTYPE_033HZ,
    FLASHTYPE_05HZ,
    FLASHTYPE_3HZ,
    FLASHTYPE_4HZ
};

enum TargetValue
{
    VISIBLE_false=0,
    VISIBLE_true,
    VISIBLE_spangle
};

enum COLORTYPE
{
    COLORTYPE_NONE=0,
    COLORTYPE_GREEN,
    COLORTYPE_WHITE,
    COLORTYPE_RED,
    COLORTYPE_YELLOW,
    COLORTYPE_GRAY,
    COLORTYPE_BLUE,
};

class TelltaleFlash: public QObject
{
    Q_OBJECT
public:
    TelltaleFlash(Telltale * tell = 0);

    ~TelltaleFlash(){}
    void update();

    void addTell(Telltale *tell);
    void removeTell(Telltale *tell);

signals:
    void stateChange(int index, const TellData tell);

private:
    QMap<int, Telltale*> m_tellList;
    int m_timerCounter;
    bool m_visible;
    int m_flashType;

    void stop();
    void handleTellState(int max, int flashType);
};

#endif // TELLTALEFLASH_H
