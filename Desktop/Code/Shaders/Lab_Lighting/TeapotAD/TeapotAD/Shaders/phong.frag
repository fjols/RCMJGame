#version 430

in vec3 vertPos;
in vec3 N;
in vec3 lightPos;
/*TODO:: Complete your shader code for a full Phong shading*/ 

// complete to a full phong shading
layout( location = 0 ) out vec4 FragColour;


uniform struct MaterialInfo
{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	vec3 La;
	vec3 Ld;
	vec3 Ls;
	vec3 camPos;
	float shininess;
	float constant;
	float linear;
	float quad;
} mat;

float Attenuation()
{
	float distance = length(lightPos - vertPos); // Distance from the object.
	float attenuation = 1.0f / (mat.constant + (mat.linear * distance) + (mat.quad * (distance * distance)));
	return attenuation;
}


void main() {

   //Calculate the light vector
   vec3 L = normalize(lightPos - vertPos);  // Direction of the light vector for each vertex.
   vec3 V = normalize(2 * N * max(dot(-N, L), 0.0));
   vec3 R = normalize(L + V);
    
   //calculate Diffuse Light Intensity making sure it is not negative and is clamped 0 to 1  
   vec4 Id = vec4(mat.Ld,1.0) * max(dot(N,L), 0.0);// Why do we need vec4(vec3)?
   Id = clamp(Id, 0.0, 1.0); 

   vec4 Ia = vec4(mat.La, 1.0);
   Ia = clamp(Ia, 0.0, 1.0);

   // Specular

   vec3 lightToPositionVector = normalize(lightPos - vertPos); // The direction of the light to the position.
   vec3 reflectDirectionVector = normalize(reflect(lightToPositionVector, normalize(N))); // The reflection direction.
   vec3 positionToViewVector = normalize(vertPos - mat.camPos); // The position to the view vector.
   float specConstant = pow(max(dot(positionToViewVector, reflectDirectionVector), 0), 30); // The specular constant.
   vec3 specFinal = vec3(1.0f, 1.0f, 1.0f) * specConstant; // The final output.

   //Multiply the Reflectivity by the Diffuse intensity
   FragColour = vec4(mat.Ka, 1.0) * Ia + vec4(mat.Kd,1.0) * Id + vec4(specFinal, 1.0f); // Component wise multiplication.
   FragColour = FragColour * Attenuation();


   //Phong

}
