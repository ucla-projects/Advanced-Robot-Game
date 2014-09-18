#ifndef ENERGYSOURCE_H
#define ENERGYSOURCE_H

#include <iostream>

class EnergySource
{
public:
    // Constructor
    EnergySource(int r, int c);
    
    // Accessors
    int row() const;
    int col() const;
    
private:
    int m_row;
    int m_col;
};


#endif
