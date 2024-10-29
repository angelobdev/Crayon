// VERTEX
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 v_Normal;
out vec3 v_FragPos;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0);
    
    mat3 normalMatrix = transpose(inverse(mat3(u_Model)));
    v_Normal = normalize(normalMatrix * normal);
    
    v_FragPos = vec3(u_Model * vec4(position, 1.0));
}
// END

// FRAGMENT
#version 330 core

layout (location = 0) out vec4 f_Color;

uniform vec3 u_LightColor;
uniform vec3 u_LightPosition;

uniform vec3 u_BaseColor;

uniform float u_Ambient;
uniform float u_Diffuse;
uniform float u_Specular;

in vec3 v_Normal;
in vec3 v_FragPos;

void main()
{
    // Ambient
    vec3 ambient = u_Ambient * u_LightColor;

    // Diffuse
    vec3 lightDir = normalize(u_LightPosition - v_FragPos);
    float diff = max(dot(v_Normal, lightDir), 0.0) * u_Diffuse;
    vec3 diffuse = diff * u_LightColor;

    // Specular
    vec3 viewPos = vec3(0.0, 0.0, 0.0);  // Camera position in view space
    vec3 viewDir = normalize(-v_FragPos);
    vec3 reflectDir = reflect(-lightDir, v_Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = u_Specular * spec * u_LightColor;

    // Result...
    vec3 result = (ambient + diffuse + specular) * u_BaseColor; // TODO: Add textures
    f_Color = vec4(result, 1.0);
}
// END