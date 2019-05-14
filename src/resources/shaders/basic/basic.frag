#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Color;

// texture sampler
uniform sampler2D texture1;

void main()
{
	FragColor = vec4(Color, 1.0f) * texture(texture1, TexCoord);
}