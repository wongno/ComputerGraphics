#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoords;

layout (location = 2) in vec3 normals;
layout (location = 3) in vec3 tangents;
layout (location = 4) in vec3 bitangents; 

// We now have our camera system set up.
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// We define a new output vec2 for our texture coorinates.
out vec2 texCoords;
out vec3 norm;
out vec3 fragPos;
out mat3 TBNOut;

void main()
{

    // make TBN
    vec3 T = normalize(vec3(modelMatrix * vec4(tangents,   0.0)));
   vec3 B = normalize(vec3(modelMatrix * vec4(bitangents, 0.0)));
   vec3 N = normalize(vec3(modelMatrix * vec4(normals,    0.0)));
    mat3 TBN = mat3(T, B, N);

    TBNOut = TBN;



    // We have our transformed position set properly now
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(position, 1.0);

    // Our fragment pos for lighting.
    fragPos = (viewMatrix * modelMatrix*vec4(position, 1.0)).xyz;

    // Make sure to transform the normal
    vec4 tmpnorm = modelMatrix*vec4(normals, 0.0);
    norm = normals;

    // And we map our texture coordinates as appropriate
    texCoords = textureCoords;
}