#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textureCoords;

// We now have our camera system set up.
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// We define a new output vec2 for our texture coorinates.
out vec2 texCoords;
out vec3 norm;
out vec3 fragPos;

void main()
{
    // We have our transformed position set properly now
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(position, 1.0);
    // Our fragment pos for lighting.
    fragPos = (modelMatrix*vec4(position, 1.0)).xyz;
    // Make sure to transform the normal
    vec4 tmpnorm = modelMatrix*vec4(normal, 0.0);
    norm = normalize(tmpnorm.xyz);
    // And we map our texture coordinates as appropriate
    texCoords = textureCoords;
}