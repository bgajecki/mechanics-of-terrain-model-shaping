#version 460 core

layout(location = 0) out vec4 color;

uniform vec3 lightPosition[2];
uniform vec3 viewPosition;

in vec3 FragPosition;
in vec3 FragNormal;
in vec4 FragColor;

const vec3 yellow = vec3(1.0f, 0.8392f, 0.3019f); // Yellow
const vec3 white = vec3(1.0f, 1.0f, 1.0f); // White

void main()
{
	vec3 lightColor[2];
	float ambientStrength = 0.1;
	float diffuseStrength[2];
	float specularStrength[2];

	lightColor[0] = yellow;
	diffuseStrength[0] = 0.5;
	specularStrength[0] = 0.4;

	lightColor[1] = white;
	diffuseStrength[1] = 0.4;
	specularStrength[1] = 0.3;

    vec3 ambient = ambientStrength * white;
	vec3 normal = normalize(FragNormal);

	for(uint i = 0; i < 2; i++)
	{
		vec3 lightDiretion = normalize(lightPosition[i] - FragPosition);
		float diff = max(dot(normal, lightDiretion), 0.0);
		vec3 diffuse = diffuseStrength[i] * diff * lightColor[i];

		vec3 viewDirection = normalize(viewPosition - FragPosition);
		vec3 reflectDirection = reflect(-lightDiretion, normal);  
		float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
		vec3 specular = specularStrength[i] * spec * lightColor[i];  

		if(i == 0)
		{
			color.rgb = (ambient + clamp(diffuse, 0, 1) + clamp(specular, 0, 1)) * FragColor.rgb;
			color.a = FragColor.a;
		}
		else
		{
			color.rgb += (ambient + clamp(diffuse, 0, 1) + clamp(specular, 0, 1)) * FragColor.rgb;
		}
	}
}