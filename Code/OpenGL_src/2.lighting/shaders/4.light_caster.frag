#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

struct Material{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Lighting{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 direction;
	vec3 position;
	float cutOff;
	float outerCutOff;
	
	float constant;
	float linear;
	float quadratic;
};

uniform Material material;
uniform Lighting lighting;
uniform vec3 viewPos;

void main(){
//	float distance = length(lighting.position - FragPos);
//	float attenuation = 1.0 / (lighting.constant + 
//		lighting.linear * distance +
//		lighting.quadratic * (distance * distance));
//		
//	vec3 lightDir = normalize(lighting.position - FragPos);
////	vec3 lightDir = normalize(-lighting.direction);
//	float theta = dot(lightDir, normalize(-lighting.direction));
//	if(theta > lighting.cutOff)
//	{
//		//ambient
//		vec3 ambient = texture(material.diffuse, TexCoords).rgb * lighting.ambient;
//		//diffuse
//		vec3 norm = normalize(Normal);
//		float diff = max(dot(norm, lightDir), 0.0);
//		vec3 diffuse = texture(material.diffuse, TexCoords).rgb * diff * lighting.diffuse;
//		//specular
//		vec3 reflectDir = normalize(reflect(-lightDir, norm));
//		vec3 viewDir = normalize(viewPos - FragPos);
//		float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
//		vec3 specular = texture(material.specular, TexCoords).rgb * spec * lighting.specular;
//
//		vec3 result = ambient + diffuse * attenuation + specular * attenuation;
//		FragColor = vec4(result, 1.0);
//	}
//	else{
//		FragColor = vec4(lighting.ambient * texture(material.diffuse, TexCoords).rgb, 1.0);
//	}

	//ambient
	vec3 ambient = lighting.ambient * texture(material.diffuse, TexCoords).rgb;
	//diffuse
	vec3 lightDir = normalize(lighting.position - FragPos);
	vec3 norm = normalize(Normal);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = lighting.diffuse * texture(material.diffuse, TexCoords).rgb * diff;
	//specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = lighting.specular * spec * texture(material.specular, TexCoords).rgb;

	float theta = dot(lightDir, normalize(-lighting.direction));
	float epsilon = (lighting.cutOff - lighting.outerCutOff);
	float intensity = clamp((theta - lighting.outerCutOff)/epsilon, 0.0, 1.0);
	diffuse *= intensity;
	specular *= intensity;

	float distance = length(lighting.position - FragPos);
	float attenuation = 1.0 / (lighting.constant + 
		lighting.linear * distance + 
		lighting.quadratic *(distance * distance));
	
	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result * attenuation, 1.0);
}