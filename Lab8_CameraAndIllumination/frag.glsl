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



// calculate lighting stuff
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 ambient = light.ambientIntensity * light.color;

  // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuseLight = diff * light.color;


    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec3 specular = pointLights[0].specularIntensity * spec * pointLights[0].color;

    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance)); 

ambient *= attenuation;
specular *= attenuation;
diffuseLight *= attenuation;


    return diffuseLight + ambient + specular;

}

void main() {
  // Set our output fragment color to whatever we pull from our input texture (Note, change 'tex' to whatever the sampler is named)
  fragColor = texture(tex, texCoords);

  // TODO:  Implement some form of lighting.
  // compute the normal direction
  vec3 ourNormal = normalize(norm);

  vec3 viewPos = vec3(0.0,0.0,0.0);
  vec3 viewDir = normalize(viewPos - fragPos);




  // texture color
  vec3 diffuseColor;
  diffuseColor = texture(tex, texCoords).rgb;
vec3 result;

for(int i = 0; i < 3; i++) {
  result += CalcPointLight(pointLights[i], ourNormal, fragPos, viewDir);

}


    // Final color + "how dark or light to make fragment"
    if(gl_FrontFacing){
        fragColor = vec4(diffuseColor * result,1.0);
    }else{
        // Additionally color the back side the same color
         fragColor = vec4(diffuseColor * result,1.0);
    }

}