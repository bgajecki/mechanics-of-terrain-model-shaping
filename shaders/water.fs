#version 460 core

layout(location = 0) out vec4 color;

uniform vec3 lightPosition[2];
uniform vec3 viewPosition;
uniform sampler2D textureSampler;

in vec2 textureCoords;
in vec3 FragPosition;
in vec3 FragNormal;

const vec3 yellow = vec3(1.0f, 0.8392f, 0.3019f); // Yellow
const vec3 white = vec3(1.0f, 1.0f, 1.0f); // White

void main()
{
	color = texture(textureSampler, textureCoords);
	color.r = 0.0;
	color.g = 0.0;
	color.b += 0.5;
	color.a = 0.8;

	vec3 lightColor[2];
	float ambientStrength = 0.3;
	float diffuseStrength[2];
	float specularStrength[2];

	lightColor[0] = yellow;
	diffuseStrength[0] = 0.6;
	specularStrength[0] = 0.5;

	lightColor[1] = white;
	diffuseStrength[1] = 0.3;
	specularStrength[1] = 0.2;

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
			color.rgb = (ambient + clamp(diffuse, 0, 1) + specular) * color.rgb;
		}
		else
		{
			color.rgb = (ambient + clamp(diffuse, 0, 1) + specular) * color.rgb;
		}
	}
}