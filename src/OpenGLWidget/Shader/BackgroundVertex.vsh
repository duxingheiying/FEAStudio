#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;

out vec3 outFragpos;
out vec3 outNormal;
out vec3 outColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    outColor = color;

    gl_Position = projection * view *  model * vec4(position, 1.0f);
    outFragpos = vec3( model * vec4( position, 1.0f));
    outNormal = mat3( transpose ( inverse( model ) )) * normal;
}
