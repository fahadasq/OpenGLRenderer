#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out int EntityID;
  
in vec2 fUV;
in vec3 fNormal;

uniform struct Material { 

    vec3 Color;
    vec3 SecColor;
    sampler2D tex;
    sampler2D wall;

} u_Material;

uniform int u_ID;

void main()
{
    //FragColor = vec4((fNormal + u_Material.Color) * u_Material.SecColor, 1.0f);
    FragColor = texture(u_Material.tex, fUV) * vec4(u_Material.Color, 1.0f);
    EntityID = u_ID;
}