#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
	FragColor = vec4(ourColor, 1.0);
	FragColor = vec4(ourColor.xxx, 1.0);
}
