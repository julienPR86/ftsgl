#version 460 core

layout(location = 0) in vec2	position;
layout(location = 1) in vec4	in_color;

out vec4	color;

uniform vec2	resolution;

vec2 to_screen(vec2 pos)
{
	return (pos / resolution) * 2;
}

void main()
{
	color = in_color;
	gl_Position = vec4(to_screen(position * resolution * 0.5), 0.0, 1.0);
}
