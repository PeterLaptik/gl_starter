#ifndef POINT_H
#define POINT_H

class Point
{
    public:
        Point(float x, float y, float z = 0)
            : m_x(x), m_y(y), m_z(z)
        { }

        Point()
            : m_x(0), m_y(0), m_z(0)
        { }

        virtual ~Point()
        { }

        float GetX(void) const
        {
            return m_x;
        }

        float GetY(void) const
        {
            return m_y;
        }

        float GetZ(void) const
        {
            return m_z;
        }

    private:
        float m_x;
        float m_y;
        float m_z;
};

#endif // POINT_H
