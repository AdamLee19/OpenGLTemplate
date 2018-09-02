#version 410

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vn;

uniform mat4 proj_mat, view_mat, model_mat;

vec3 lightPos = vec3(0.0f, 0.0f, 5.0f);
float specularStrength = 0.5;

out vec3 vNorm;
out vec3 vLightvec;
out vec3 vPos;


void main () {

    gl_Position = proj_mat * view_mat * model_mat * vec4 (vp, 1.0);
 	
    vNorm = normalize( vn );
    
    vec3 vLight = lightPos - vn;
	vLightvec = normalize(vec3(model_mat * vec4(vLight, 1.0)));
	
	
	vPos = vec3( model_mat * vec4 (vp, 1.0) );
 		
}