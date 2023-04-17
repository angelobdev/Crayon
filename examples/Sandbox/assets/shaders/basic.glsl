// VERTEX
#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0);
}
// END

// FRAGMENT
#version 330 core

out vec4 f_Color;

void main()
{
    f_Color = vec4(1.0, 1.0, 1.0, 1.0);
}
// END