#include "../include/triangle.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

Triangle::Triangle(const Point &p1, const Point &p2, const Point &p3)
{
    m_points[0] = p1;
    m_points[1] = p2;
    m_points[2] = p3;
}

Triangle::~Triangle()
{
    glDeleteVertexArrays(1, &m_vertex_array_id);
    glDeleteBuffers(1, &m_vertex_buffer_id);
}

void Triangle::CreateGeometry()
{
    Refresh();
}

void Triangle::SetColour(const Colour &c1, const Colour &c2, const Colour &c3)
{
    m_colour_points[0] = c1;
    m_colour_points[1] = c2;
    m_colour_points[2] = c3;
}

void Triangle::SetTextureCoordinates(const Point &p1, const Point &p2, const Point &p3)
{
    m_texture_points[0] = p1;
    m_texture_points[1] = p2;
    m_texture_points[2] = p3;
}

void Triangle::Draw()
{
    glBindVertexArray(m_vertex_array_id);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::Refresh()
{
    glDeleteVertexArrays(1, &m_vertex_array_id);
    glDeleteBuffers(1, &m_vertex_buffer_id);

    for(int i=0; i<3; i++)
    {
        m_vertices[i*8 + 0] = m_points[i].GetX();
        m_vertices[i*8 + 1] = m_points[i].GetY();
        m_vertices[i*8 + 2] = m_points[i].GetZ();
        m_vertices[i*8 + 6] = m_texture_points[i].GetX();
        m_vertices[i*8 + 7] = m_texture_points[i].GetY();
    }

    glGenVertexArrays(1, &m_vertex_array_id);
    glGenBuffers(1, &m_vertex_buffer_id);
    glBindVertexArray(m_vertex_array_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
