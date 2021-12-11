#version 330 core
out vec4 FragColor;
  
in vec2 fUV;
in vec3 fNormal;

uniform struct Material { 

    vec3 color;
    vec3 secColor;
    sampler2D tex;
    sampler2D wall;

} u_Material;

uniform sampler2D testTex;
uniform sampler2D container;

void main()
{
    //FragColor = vec4((fNormal + u_Material.color) * u_Material.secColor, 1.0f);
    FragColor = texture(u_Material.tex, fUV);
} 