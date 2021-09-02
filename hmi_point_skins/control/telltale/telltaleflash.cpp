#include "telltaleflash.h"
#include "telltale.h"
#include <QDebug>

/*
闪烁灯的管理类
控制灯的闪烁频率 1HZ 2HZ 3HZ等
*/
TelltaleFlash::TelltaleFlash(Telltale *tell)
    :m_timerCounter(-1)
    ,m_visible(false)
    ,m_flashType(0)
{
    if(0 != tell)
        addTell(tell);
}

void TelltaleFlash::update()
{
    switch (m_flashType) {
    case FLASHTYPE_1HZ:
        handleTellState(50, FLASHTYPE_1HZ);
        break;
    case FLASHTYPE_2HZ:
        handleTellState(25, FLASHTYPE_2HZ);
        break;
    case FLASHTYPE_3HZ:
        handleTellState(16, FLASHTYPE_3HZ);
        break;
    case FLASHTYPE_4HZ:
        handleTellState(12, FLASHTYPE_4HZ);
        break;
    case FLASHTYPE_05HZ:
        handleTellState(100, FLASHTYPE_05HZ);
        break;
    case FLASHTYPE_033HZ:
        handleTellState(151, FLASHTYPE_033HZ);
        break;
    }
}

void TelltaleFlash::addTell(Telltale *tell)
{
    m_tellList.insert(tell->propertyIndex, tell);
    m_flashType = tell->spangleType;
}

//如果灯需要从一种频率变为另一种频率,需要先移除,再添加
void TelltaleFlash::removeTell(Telltale *tell)
{
    m_tellList.take(tell->propertyIndex);
}

void TelltaleFlash::stop()
{
    m_timerCounter = -1;
    m_visible = false;
}

void TelltaleFlash::handleTellState(int max, int flashType)
{
    m_timerCounter++;
    if(m_timerCounter >= max) m_timerCounter = 0;
    if(m_timerCounter == 0)
    {
        m_visible = !m_visible;

        foreach(Telltale* tell, m_tellList.values()){
            if(tell->targetValue == VISIBLE_spangle){
                if(tell->spangleType == flashType){
                    int target = m_visible?static_cast<int>(VISIBLE_true):static_cast<int>(VISIBLE_false);
                    emit stateChange(tell->propertyIndex, TellData(target, tell->colorType));

                }
            }
        }
    }
}
