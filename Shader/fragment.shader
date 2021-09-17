#version 330 core
//uniform vec3 u_color;
in vec3 u_color;
out vec4 FragColor;
in vec2 UV;

uniform sampler2D texture_diffuse;
//out vec2 UV;
uniform vec3 uniformColor;

void main()
{
	FragColor = texture(texture_diffuse, UV);
	//FragColor = vec3(u_color);
}