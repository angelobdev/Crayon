// VERTEX
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;  // Changed from location 2 to 1 to match layout

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 v_Normal;
out vec3 v_FragPos;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0);
    
    // Transform normal using normal matrix
    mat3 normalMatrix = transpose(inverse(mat3(u_Model)));
    v_Normal = normalMatrix * normal;
    
    v_FragPos = vec3(u_Model * vec4(position, 1.0));
}
// END

// FRAGMENT
#version 330 core

layout (location = 0) out vec4 f_Color;

in vec3 v_Normal;
in vec3 v_FragPos;

void main()
{
    // Light (Point)
    vec3 lightPos = vec3(20.0, 30.0, -20.0);
    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    // Object
    vec3 objectColor = vec3(0.7, 0.7, 0.7);  // Slightly darker to see shading better

    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(lightPos - v_FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5;
    vec3 viewPos = vec3(0.0, 0.0, 0.0);  // Camera position in view space
    vec3 viewDir = normalize(-v_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;

    f_Color = vec4(result, 1.0);
}
// END