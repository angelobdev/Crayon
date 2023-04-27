// VERTEX
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textureCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 v_Color;
out vec2 v_TextureCoord;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0);
    v_Color = color;
    v_TextureCoord = textureCoord;
}
// END

// FRAGMENT
#version 330 core

layout (location = 0) out vec4 f_Color;

in vec3 v_Color;
in vec2 v_TextureCoord;

uniform sampler2D u_Texture;

void main()
{
    //   f_Color = vec4(v_Color, 1.0);
    f_Color = texture(u_Texture, v_TextureCoord) * vec4(v_Color, 1.0);
}
// END