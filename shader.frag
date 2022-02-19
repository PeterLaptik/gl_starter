#version 330 core

out vec4 frag_colour;
uniform vec4 current_colour;

void main()
{
    frag_colour = vec4(current_colour.x, current_colour.y, current_colour.z, 1.0f);
};
