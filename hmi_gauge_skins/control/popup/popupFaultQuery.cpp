#include "popupFaultQuery.h"

PopupFaultQuery::PopupFaultQuery(const PopupFaultQuery& pop, QObject* parent)
    :QObject(parent)
{
    m_name = pop.m_name;
}
