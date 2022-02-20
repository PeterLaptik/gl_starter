#ifndef LINE_H
#define LINE_H

#include "point.h"

class Line
{
    public:
        Line(const Point &p1, const Point &p2);
        virtual ~Line();

        virtual void Draw(void);
        virtual void CreateGeometry(void);
        virtual void Refresh(void);

    private:
        Point m_points[2];
        float m_vertices[6];
        unsigned int m_vertex_array_id;
        unsigned int m_vertex_buffer_id;
};

#endif // LINE_H
