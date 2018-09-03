#version 410

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vn;

uniform mat4 proj_mat, view_mat, model_mat; 
uniform vec3 uKeyLightPos, uFillLightPos, uBackLightPos;



float specularStrength = 0.5;

out vec3 vNorm;
out vec3 vKeyLightNorm;
out vec3 vFillLightNorm;
out vec3 vBackLightNorm;
out vec3 vPos;


void main () {

    gl_Position = proj_mat * view_mat * model_mat * vec4 (vp, 1.0);
 	
    vNorm = normalize( vn );
    
    
    vec3 p = vec3( model_mat * vec4( vp, 1.0) );

    vec3 klight = vec3( model_mat * vec4( uKeyLightPos, 1.0) );
    vKeyLightNorm = normalize( klight - p );

	vec3 flight = vec3( model_mat * vec4( uFillLightPos, 1.0) );
	vFillLightNorm = normalize( flight - p );
	
    vec3 blight = vec3( model_mat * vec4( uBackLightPos, 1.0) );
    vBackLightNorm = normalize( blight - p );

	vPos = p;
 		
}