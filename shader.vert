#version 330 core

layout (location = 0) in vec3 a_pos;
out vec4 gl_Position;
uniform float shift;

void main()
{
    gl_Position = vec4(a_pos.x, a_pos.y + shift, a_pos.z, 1.0);
};
