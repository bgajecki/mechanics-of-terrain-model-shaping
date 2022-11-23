#version 460 core

layout(location = 0) out vec4 color;

uniform vec3 viewPosition;

in vec3 FragPosition;
in vec3 FragNormal;
in vec4 FragColor;

const vec3 lightPosition = vec3(0.0f, 3.0f, 0.0f);
const vec3 lightColor = vec3(1.0f, 0.8392f, 0.3019f);

void main()
{
	float ambientStrength = 0.1;
	float diffuseStrength = 0.8;
	float specularStrength = 0.5;

    vec3 ambient = ambientStrength * lightColor;

	vec3 normal = normalize(FragNormal);

	vec3 lightDiretion = normalize(lightPosition - FragPosition);
	float diff = max(dot(normal, lightDiretion), 0.0);
	vec3 diffuse = diffuseStrength * diff * lightColor;

	vec3 viewDirection = normalize(viewPosition - FragPosition);
	vec3 reflectDirection = reflect(-lightDiretion, normal);  
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;  

	color.rgb = (ambient + diffuse + specular) * FragColor.rgb;
	color.a = FragColor.a;
}