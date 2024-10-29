#version 330 core

layout (location = 0) out vec4 f_Color;

// Light
uniform vec3 u_LightColor;
uniform vec3 u_LightPosition;

// Material
uniform vec3 u_BaseColor;
uniform vec3 u_Ambient;
uniform vec3 u_Diffuse;
uniform vec3 u_Specular;
uniform float u_Shininess;

// Texture
uniform sampler2D u_Texture;

in vec3 v_FragPos;
in vec3 v_Normal;
in vec2 v_TextureCoords;

void main()
{
    // Ambient
    vec3 ambient = u_LightColor * u_Ambient;

    // Diffuse
    vec3 lightDir = normalize(u_LightPosition - v_FragPos);
    float diff = max(dot(v_Normal, lightDir), 0.0);
    vec3 diffuse = u_LightColor * (diff * u_Diffuse);

    // Specular
    vec3 viewPos = vec3(0.0, 0.0, 0.0);  // Camera position in view space
    vec3 viewDir = normalize(-v_FragPos);
    vec3 reflectDir = reflect(-lightDir, v_Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Shininess);
    vec3 specular = u_LightColor * (u_Specular * spec);

    vec3 finalColor = (ambient + diffuse + specular) * u_BaseColor;

    // Checking if texture is bound
    vec4 testPixel = texture(u_Texture, vec2(0.0, 0.0));
    if (testPixel.a < 0.01) {
        f_Color = vec4(finalColor, 1.0) * texture(u_Texture, v_TextureCoords);
    }else{
        f_Color = vec4(finalColor, 1.0);
    }    
}