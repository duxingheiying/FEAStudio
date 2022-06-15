#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec3 outColor;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

vec3 amb_strength = vec3(0.3);
vec3 diff_strength = vec3(0.7);
vec3 spec_strength = vec3(0.9);

void main()
{
    // Ambient
//    vec3 ambient = light.ambient * material.ambient;
    vec3 ambient = amb_strength * outColor * outColor;

    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), -dot(norm, lightDir));
    vec3 diffuse = diff_strength * outColor * (diff * outColor);
    
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);
    vec3 specular = spec_strength * light.specular * (spec * material.specular);

    // calculate color
    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0f);
} 
