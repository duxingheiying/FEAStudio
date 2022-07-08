#version 330 core

in  vec3 outColor;
in  vec3 outFragpos;
in  vec3 outNormal;

out vec4 color;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // Ambient
    float ambientStrength = 1.0f;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(outNormal);
    vec3 lightDir = normalize(lightPos - outFragpos);
    // translate minus to positive
//    float diff = max(dot(norm, lightDir), 0);
    float diff = max(abs(dot(norm, lightDir)), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.8f;
    vec3 viewDir = normalize(viewPos - outFragpos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    vec3 result = (ambient + diffuse + specular) * objectColor;
    color = vec4(objectColor, 1.0f);

//    // Ambient
//    float ambientStrength = 0.2f;
//    vec3 ambient = ambientStrength * lightColor;

//    // Diffuse
//    vec3 norm = normalize(outNormal);
//    vec3 lightDir = normalize(lightPos - outFragpos);
//    float diff = max(abs(dot(norm, lightDir)), 0.0);
//    vec3 diffuse = diff * lightColor;

//    // Specular
//    float specularStrength = 0.8f;
//    vec3 viewDir = normalize(viewPos - outFragpos);
//    vec3 reflectDir = reflect(-lightDir, norm);
//    float spec = pow(max(abs(dot(viewDir, reflectDir)), 0.0), 32);
//    vec3 specular = specularStrength * spec * lightColor;

//    vec3 result = (ambient + diffuse + specular) * objectColor;
//    color = vec4(result, 1.0f);
}

