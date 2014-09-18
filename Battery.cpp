#include "Battery.h"

Battery::Battery(int initialLevel)
{
    m_level = initialLevel;
}

int Battery::level() const
{
    return m_level;
}

void Battery::decrease()
{
    if (m_level>0)
        m_level -= 1;
}