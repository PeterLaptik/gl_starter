#version 330 core

out vec4 frag_colour;

in vec2 text_coord;

uniform vec4 current_colour;
uniform sampler2D out_texture;

void main()
{
    frag_colour = texture(out_texture, text_coord);
    //frag_colour = vec4(current_colour.x, current_colour.y, current_colour.z, 1.0f);
};
