#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Material{
	sampler2D diffuse;
	sampler2D specular;

	float shininess;
};
//定向光
struct DirLight{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
//点光源
struct PointLight{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
//聚光
struct SpotLight{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	float contant;
	float linear;
	float quadratic;
};

#define NR_POINT_LIGHTS 4

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLight[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform vec3 viewPos;

vec3 CaleDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CaleSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main(){
	//ambient
	vec3 ambient = spotLight.ambient * texture(material.diffuse, TexCoords).rgb;
	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(spotLight.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = spotLight.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
	//specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0),material.shininess);
	vec3 specular = spotLight.specular * spec * texture(material.specular, TexCoords).rgb;

	float theta = dot(normalize(spotLight.direction), -lightDir);
	float epsilon = spotLight.cutOff - spotLight.outerCutOff;
	float intensity = clamp((theta - spotLight.outerCutOff)/epsilon, 0.0, 1.0);
	diffuse *= intensity;
	specular *= intensity;

	float distance = length(spotLight.position - FragPos);
	float attenuation = 1.0 / (spotLight.contant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result * attenuation , 1.0);
}

vec3 CaleDirLight(DirLight light, vec3 normal, vec3 viewDir){
	//ambient
	vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
	//diffuse
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
	//specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

	return ambient + diffuse + specular;
}