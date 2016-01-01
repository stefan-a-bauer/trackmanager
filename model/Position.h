#ifndef POSITION_H
#define POSITION_H

class Position
{
public:
    Position(double lat, double lon);
    ~Position();

    double getLat() const
    {
        return m_lat;
    }

    double getLon() const
    {
        return m_lon;
    }

private:
    double m_lat;
    double m_lon;
};

#endif
