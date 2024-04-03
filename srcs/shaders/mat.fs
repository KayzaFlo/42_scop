#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
	vec3 ambient = vec3(0.2863, 0.2667, 0.1804);
	vec3 lightPos = vec3(5., 5., 5.);
	vec3 lightColor = vec3(1., 1., 1.);
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(FragPos - lightPos);  
	// float diff = max(dot(norm, lightDir), 0.0);
	float diff = max(distance(FragPos, lightDir) * 0.5, 0.0);
	vec3 diffuse = diff * lightColor;
	vec3 result = (ambient + diffuse) * ourColor;
	FragColor = vec4(result, 1.0);


//    FragColor = vec4(FragPos, 1.0);
//    FragColor = vec4(ourColor, 1.0);
}
