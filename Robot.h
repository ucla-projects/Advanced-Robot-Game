#ifndef ROBOT_H
#define ROBOT_H

#include "Battery.h"
#include <string>

class Valley;

class Robot
{
public:
    // Constructor
    Robot(std::string nm, Valley* vp, int r, int c, int d);
    
    // Accessors
    std::string name() const;
    int         energy() const;
    int         row() const;
    int         col() const;
    int         dir() const;
    int         batteryLevel() const;
    
    // Mutators
    bool        step();
    
private:
    std::string  m_name;
    int          m_energy;
    int          m_row;
    int          m_col;
    int          m_dir;
    Valley*      m_valley;
    Battery      m_battery;
};

#endif
