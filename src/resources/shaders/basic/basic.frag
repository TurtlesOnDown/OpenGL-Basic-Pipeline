#version 330 core
out vec4 FragColor;

struct DirectLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {    
    float constant;
    float linear;
    float quadratic;

	vec3 position;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
	float constant;
	float linear;
	float quadratic;

	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float cutOff;
	float outerCutOff;
};

struct Material {
	float shininess;
	float shininessStrength;

	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;

	sampler2D textureDiffuse;
	sampler2D textureSpecular;
	sampler2D textureNormal;
	sampler2D textureHeight;
};

#define DIRECT_LIGHT_COUNT 4
#define POINT_LIGHT_COUNT 4
#define SPOT_LIGHT_COUNT 4

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in mat3 TBN;

layout (std140) uniform testUniformBlock {
	float test;
} testBlock;

uniform DirectLight dirLights[DIRECT_LIGHT_COUNT];
uniform PointLight pointLights[POINT_LIGHT_COUNT];
uniform SpotLight spotLights[SPOT_LIGHT_COUNT];

uniform vec3 camPos;
uniform Material material;

vec3 calcDirectLight(DirectLight light, vec3 normal, vec3 viewDirection);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDirection);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDirection);

void main()
{    
	vec3 norm = texture(material.textureNormal, TexCoord).rgb;
	norm = normalize((norm * 2.0) - 1.0);
	norm = normalize(TBN * norm);
	norm = normalize(Normal);
	vec3 viewDir = normalize(camPos - FragPos);

	float testFloat = testBlock.test;

	vec3 result = vec3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < DIRECT_LIGHT_COUNT; i++) {
		result += calcDirectLight(dirLights[i], norm, viewDir);
	}

	for (int i = 0; i < POINT_LIGHT_COUNT; i++) {
		result += max(calcPointLight(pointLights[i], norm, viewDir), 0.0f);
	}

	for (int i = 0; i < SPOT_LIGHT_COUNT; i++) {
		result += max(calcSpotLight(spotLights[i], norm, viewDir), 0.0f);
	}

	//result = result * texture(material.textureDiffuse, TexCoord).rgb * material.diffuseColor;
    FragColor = vec4(result, 1.0f);
}

vec3 calcDirectLight(DirectLight light, vec3 normal, vec3 viewDirection) {
	vec3 lightDirection = -normalize(FragPos - light.position);
	// diffuse
	float diff = max(dot(normal, lightDirection), 0.0);
	// specular
	vec3 halfwayVector = normalize(lightDirection + viewDirection);
	float spec = pow(max(dot(normal, halfwayVector), 0.0), material.shininess);
	//combine
	vec3 ambient = light.ambient * vec3(texture(material.textureDiffuse, TexCoord)) * material.diffuseColor;
	vec3 diffuse = diff * (light.diffuse * vec3(texture(material.textureDiffuse, TexCoord)) * material.diffuseColor);
	vec3 specular = (material.shininessStrength * spec) * (light.specular * vec3(texture(material.textureSpecular, TexCoord)));
	return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDirection)
{
    vec3 lightDirection = -normalize(FragPos - light.position);
    // diffuse shading
    float diff = max(dot(normal, lightDirection), 0.0);
    // specular shading
	vec3 halfwayVector = normalize(lightDirection + viewDirection);
    float spec = max(pow(max(dot(normal, halfwayVector), 0.0), material.shininess), 0.0f);
    // attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
	vec3 ambient = light.ambient * vec3(texture(material.textureDiffuse, TexCoord)) * material.diffuseColor;
    vec3 diffuse = diff * (light.diffuse * vec3(texture(material.textureDiffuse, TexCoord)) * material.diffuseColor);
    vec3 specular = (material.shininessStrength * spec) * (light.specular * vec3(texture(material.textureSpecular, TexCoord)));
    return (ambient + diffuse + specular) * attenuation;
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDirection) {
	vec3 lightDirection = -normalize(FragPos - light.position);

	// diffuse
	float diff = max(dot(normal, lightDirection), 0.0);

	// specular
	vec3 halfwayVector = normalize(lightDirection + viewDirection);
	float spec = max(pow(max(dot(normal, halfwayVector), 0.0f), material.shininess), 0.0f);
	// attenuation
	float distance = length(light.position - FragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	// combine
	vec3 ambient = light.ambient * vec3(texture(material.textureDiffuse, TexCoord)) * material.diffuseColor;
	vec3 diffuse = diff * (light.diffuse * vec3(texture(material.textureDiffuse, TexCoord)) * material.diffuseColor);
	vec3 specular = (material.shininessStrength * spec) * (light.specular * vec3(texture(material.textureSpecular, TexCoord)));

	//spot light
	float theta = dot(lightDirection, normalize(-light.direction)); 
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	return (ambient + ((diffuse + specular) * intensity)) * attenuation;
}
