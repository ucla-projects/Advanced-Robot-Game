#include <string>
#include <iostream>
#include <cstdlib>
#include "Robot.h"
#include "Valley.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////
//  Robot implementation
///////////////////////////////////////////////////////////////////////////

// Constructor:  Create a Robot in the Valley pointed to by vp, with
//    name nm, location (r,c), and direction d.



Robot::Robot(string nm, Valley* vp, int r, int c, int d): m_name(nm), m_energy(FULL_ENERGY), m_row(r), m_col(c), m_dir(d), m_valley(vp), m_battery(12)
{
    // Since the first character of the Robot's name shows up in the
    // display, there had better be a first character.
    if (nm.size() == 0)
    {
        cout << "***** A robot must have a non-empty name!" << endl;
        exit(1);
    }
    if (vp == NULL)
    {
        cout << "***** A robot must be in some Valley!" << endl;
        exit(1);
    }
    if (r < 0  ||  r >= vp->rows()  ||  c < 0  ||  c >= vp->cols())
    {
        cout << "***** Robot created with invalid coordinates (" << r << ","
        << c << ") in valley of size " << vp->rows() << "x"
        << vp->cols() << "!" << endl;
        exit(1);
    }
    switch (d)
    {
        case NORTH: case EAST: case SOUTH: case WEST:
            break;
        default:
            cout << "**** Robot created with invalid direction code " << d
            << "!" << endl;
            exit(1);
    }
}

string Robot::name() const
{
    return m_name;
}

int Robot::energy() const
{
    return m_energy;
}

int Robot::row() const
{
    return m_row;
}

int Robot::col() const
{
    return m_col;
}

int Robot::dir() const
{
    return m_dir;
}

int Robot::batteryLevel() const
{
    return m_battery.level();
}

bool Robot::step()
{
    if (m_energy == 0 && this->batteryLevel()>0)
    {
        m_battery.decrease();
        m_energy++;
    }
    // If the robot has no energy and no battery left, return false
    else if (m_energy == 0 && this->batteryLevel()==0)
        return false;
    
    // Randomly change direction with probability 1/3
    if (rand() % 3 == 0)     // 1/3 probability to pick a direction
        m_dir = rand() % 4;  // pick a random direction (0 through 3)
    
    // Attempt to move one step in the direction we're currently facing.
    // If we can't move in that direction, go in the opposite direction.
    switch (m_dir)
    {
        case NORTH:
            if (m_row > 0)
                m_row--;
            else
                m_row++;
            break;
        case SOUTH:
            if (m_row < m_valley->rows()-1)
                m_row++;
            else
                m_row--;
            break;
        case WEST:
            if (m_col > 0)
                m_col--;
            else
                m_col++;
            break;
        case EAST:
            if (m_col < m_valley->cols()-1)
                m_col++;
            else
                m_col--;
            break;
    }
    
    // The attempt to move consumes one unit of energy.
    m_energy--;
    
    // If as a result of the attempt to move, the robot is at an energy
    // source, it's recharged to the FULL_ENERGY level.
    if (m_valley->energySourceAt(m_row, m_col))
        m_energy = FULL_ENERGY;
    
    // If at this spot there's another robot whose energy level is 0,
    // and we have at least SHARE_THRESHOLD units of energy,
    // transfer SHARE_AMOUNT units to that other robot.
    if (m_energy >= SHARE_THRESHOLD)
    {
        Robot* rp = m_valley->otherRobotAt(this);
        if (rp != NULL  &&  rp->energy() == 0)
        {
            m_energy -= SHARE_AMOUNT;
            rp->m_energy += SHARE_AMOUNT;
        }
    }
    
    return true;
}
