#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoords;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 v_FragPos;
out vec3 v_Normal;
out vec2 v_TextureCoords;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0);
    
    v_FragPos = vec3(u_Model * vec4(position, 1.0));

    mat3 normalMatrix = transpose(inverse(mat3(u_Model)));
    v_Normal = normalize(normalMatrix * normal);
    
    v_TextureCoords = textureCoords;
}