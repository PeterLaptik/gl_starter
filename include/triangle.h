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
        virtual void SetColour(const Colour &c1, const Colour &c2, const Colour &c3);
        virtual void SetTextureCoordinates(const Point &p1, const Point &p2, const Point &p3);
        virtual void Refresh(void);

    private:
        Point m_points[3];
        Colour m_colour_points[3];
        Point m_texture_points[3];
        // Vertice format:
        // x, y, z, R, G, B, text_x, text_y
        float m_vertices[24];
        unsigned int m_vertex_array_id;
        unsigned int m_vertex_buffer_id;
};

#endif // TRIANGLE_H
