#include "../include/line.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Line::Line(const Point &p1, const Point &p2)
{
    m_points[0] = p1;
    m_points[1] = p2;
}

Line::~Line()
{
    glDeleteVertexArrays(1, &m_vertex_array_id);
    glDeleteBuffers(1, &m_vertex_buffer_id);
}

void Line::CreateGeometry()
{
    Refresh();
}

void Line::Draw()
{
    glBindVertexArray(m_vertex_array_id);
    glDrawArrays(GL_LINES, 0, 2);
}

void Line::Refresh()
{
    glDeleteVertexArrays(1, &m_vertex_array_id);
    glDeleteBuffers(1, &m_vertex_buffer_id);

    for(int i=0; i<2; i++)
    {
        m_vertices[i*3 + 0] = m_points[i].GetX();
        m_vertices[i*3 + 1] = m_points[i].GetY();
        m_vertices[i*3 + 2] = m_points[i].GetZ();
    }

    glGenVertexArrays(1, &m_vertex_array_id);
    glGenBuffers(1, &m_vertex_buffer_id);
    glBindVertexArray(m_vertex_array_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
