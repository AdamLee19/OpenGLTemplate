#version 410


out vec4 frag_colour;
uniform  vec3 color;

in vec3 vNorm;
in vec3 vLightvec;
in vec3 vPos;

vec4 lightColor = vec4(1.0,0.8,0.7, 1.0);
float ai = 0.1;
void main () {

  	vec4 Ka = ai * lightColor;


  	
  	float diffuse = max(dot(vNorm, vLightvec), 0.0);;
  	
  	vec4 Kd = lightColor * diffuse;

  	vec3 viewDir = normalize(vLightvec - vPos);
	  vec3 reflectDir = reflect(-vLightvec, vNorm);
	  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	  vec4 specular =  0.8 * spec * lightColor;  

  	frag_colour = ( Ka + Kd +specular ) * vec4(color, 1.0);
   

}
