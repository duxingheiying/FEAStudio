#version 420 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
//layout (location = 3) in vec2 map1;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

//uniform float aspect;
out gl_PerVertex
{
    vec4 gl_Position;
};

out vec4 surface_color;
out vec3 frag_position;
out vec3 frag_normal;

void main(void)
{
    surface_color = vec4(color, 0.7);

//    vec4 object_pos = (position + offset);
//    vec4 world_pos = model_matrix * object_pos;
//    frag_position = world_pos.xyz;
    frag_position = vec3(model_matrix * vec4(position, 1.0f));

//    frag_normal = mat3(model_matrix * view_matrix) * normal;
    frag_normal = mat3(transpose(inverse(model_matrix))) * normal;

//    gl_Position = (projection_matrix * view_matrix) * world_pos;
    gl_Position = projection_matrix * view_matrix *  model_matrix * vec4(position, 1.0f);
}
