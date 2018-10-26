#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Material
{
//	vec3 ambient;
//	vec3 diffuse;
//	vec3 specular;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 position;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
	//ambient
	vec3 ambient = texture(material.diffuse, TexCoords).rgb * light.ambient;
	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(FragPos - light.position);
	float diff = max(dot(norm, -lightDir), 0.0);
	vec3 diffuse = texture(material.diffuse, TexCoords).rgb * diff *light.diffuse;
	//specular
	vec3 reflectDir = normalize(reflect(lightDir, norm));
	vec3 viewDir = normalize(viewPos - FragPos);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
	vec3 specular = texture(material.specular, TexCoords).rgb * spec * light.specular;

	vec3 result = ambient + diffuse + specular;
	FragColor =vec4(result, 1.0);
}
