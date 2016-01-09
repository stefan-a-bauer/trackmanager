#ifndef BOX_H
#define BOX_H

#include "Position.h"

class Box
{
public:
    Box(const Position &p0, const Position &p1);

    Position getP0() const
    {
        return m_p0;
    }

    Position getP1() const
    {
        return m_p1;
    }

private:
    Position m_p0;
    Position m_p1;
};

#endif
