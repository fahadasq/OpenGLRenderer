#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the position variable has attribute position 0
layout (location = 2) in vec2 aUV; // the position variable has attribute position 0

layout (std140) uniform ViewProjection
{
    uniform mat4 view;
    uniform mat4 projection;
} viewProjection;

out vec2 fUV;


uniform mat4 model;


void main()
{
    gl_Position = viewProjection.projection * viewProjection.view * model * vec4(aPos, 1.0);
    fUV = aUV;
}