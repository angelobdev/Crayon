// VERTEX
#version 330 core
layout (location = 0) in vec3 position;

void main()
{
    gl_Position = vec4(position, 1.0f);
}
//END

// FRAGMENT
#version 330 core
layout (location = 0) out vec4 f_Color;

void main()
{
    f_Color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
//END