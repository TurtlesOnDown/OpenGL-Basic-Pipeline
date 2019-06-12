#version 330 core
out vec4 FragColor;

struct DirectLight {
	int active;

	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define DIRECTLIGHT_COUNT 4

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in mat3 TBN;

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;
uniform sampler2D texture_normal0;

uniform DirectLight dirLights[DIRECTLIGHT_COUNT];

uniform vec3 camPos;
uniform float shininess;

vec3 calcDirectLight(DirectLight light, vec3 normal, vec3 viewDirection);

void main()
{    
	vec3 norm = texture(texture_normal0, TexCoord).rgb;
	norm = normalize((norm * 2.0) - 1.0);
	norm = normalize(TBN * norm);
	//norm = normalize(Normal);
	vec3 viewDir = normalize(camPos - FragPos);

	vec3 result = vec3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < DIRECTLIGHT_COUNT; i++) {
		result += calcDirectLight(dirLights[i], norm, viewDir);
	}

	result = result * texture(texture_diffuse0, TexCoord).rgb;
    FragColor = vec4(result, 1.0f);
}

vec3 calcDirectLight(DirectLight light, vec3 normal, vec3 viewDirection) {
	vec3 lightDirection = normalize(-light.direction);
	// diffuse
	float diff = max(dot(normal, lightDirection), 0.0);
	// specular
	vec3 reflectDirection = reflect(lightDirection, normal);
	vec3 halfwayVector = normalize(lightDirection + viewDirection);
	float spec = pow(max(dot(normal, halfwayVector), 0.0), shininess);
	//combine
	vec3 ambient = light.ambient;
	vec3 diffuse = light.diffuse * diff;
	vec3 specular = light.specular * spec * texture(texture_specular0, TexCoord).rgb;
	return (ambient + diffuse + specular);
}