#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D none;
uniform vec3 viewPos;

void main()
{


	vec3 ourColor =vec3(0.6353, 0.8314, 0.8627);
	vec3 ambient = vec3(0.2392, 0.2353, 0.2235);
	vec3 lightPos = vec3(5., 5., 5.);
	vec3 lightColor = vec3(1., 1., 1.);
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	// float diff = max(distance(FragPos, lightDir) * 0.5, 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 32;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec4 specular_map = texture(texture_specular1, TexCoord);
	vec3 specular = specularStrength * spec * lightColor * specular_map.xyz;

	vec3 result = (ambient + diffuse + specular) * ourColor;
	FragColor = texture(texture_diffuse1, TexCoord) * vec4(result, 1.0);
	// FragColor = vec4(result, 1.0);
}
