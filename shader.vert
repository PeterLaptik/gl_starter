#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_colour;
layout (location = 2) in vec2 a_texture;

out vec4 gl_Position;
out vec2 text_coord;

uniform float shift;

void main()
{
    gl_Position = vec4(a_pos.x, a_pos.y + shift, a_pos.z, 1.0);
    text_coord = a_texture;
};
