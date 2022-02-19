#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"

class Triangle
{
    public:
        Triangle(const Point &p1, const Point &p2, const Point &p3);
        virtual ~Triangle();

        virtual void Draw(void);
        virtual void CreateGeometry(void);
        virtual void Refresh(void);

    private:
        Point m_points[3];
        float m_vertices[9];
        unsigned int m_vertex_array_id;
        unsigned int m_vertex_buffer_id;
};

#endif // TRIANGLE_H
