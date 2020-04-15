#version 330

// Take in our texture coordinate from our vertex shader
in vec2 texCoords;
// And our normal
in vec3 norm;
// And our fragment position for lighting
in vec3 fragPos;



// We always define a fragment color that we output.
out vec4 fragColor;

// Define our light(s)
struct PointLight {
    vec3 color;
    vec3 position;
    float ambientIntensity;
    float specularIntensity;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Maintain our uniforms.
uniform sampler2D tex;              // our primary texture


uniform mat4 view;                  // we need the view matrix for highlights
uniform PointLight pointLights[4];  // Our lights




void main() {
  // Set our output fragment color to whatever we pull from our input texture (Note, change 'tex' to whatever the sampler is named)
  vec4 colortexture = texture(tex, texCoords);

  // TODO:  Implement some form of lighting.
  // compute the normal direction



  vec3 ourNormal = normalize(norm);

  vec3 viewPos = vec3(0.5, 0.5, -2.0);
  vec3 viewDir = normalize(viewPos - fragPos);



  // texture color
  vec3 diffuseColor;
  diffuseColor = texture(tex, texCoords).rgb;
  






    // Final color + "how dark or light to make fragment"
    if(gl_FrontFacing){
       fragColor = vec4(diffuseColor,1.0);
   }else{
        // Additionally color the back side the same color
    fragColor = vec4(diffuseColor ,1.0);
    }

    //fragColor = vec4(ourNormal, 1.0);
    

}