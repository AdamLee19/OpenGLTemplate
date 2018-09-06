#version 410



uniform vec4 model_color;
uniform vec4 uKeyLightColor, uFillLightColor, uBackLightColor ;
uniform vec3 uCamPos;

in vec3 vNorm;
in vec3 vKeyLightNorm;
in vec3 vFillLightNorm;
in vec3 vBackLightNorm;
in vec3 vPos;


out vec4 frag_color;

float ambientStren = 0.1;
float diffuseSten = 0.8;
float specularSten = 0.5;

vec4 phong( vec4 lightColor, vec3 lightVector, vec3 point, vec3 pointNorm, vec4 modelC, vec3 camPos );
vec4 blinn_phong( vec4 lightColor, vec3 lightVector, vec3 point, vec3 pointNorm, vec4 modelC, vec3 camPos );
void main () {


     vec4 keyPhong = blinn_phong( uKeyLightColor, vKeyLightNorm, vPos, vNorm, model_color, uCamPos );
     vec4 fillPhong = blinn_phong( uFillLightColor, vFillLightNorm, vPos, vNorm, model_color, uCamPos );
     vec4 backPhong = blinn_phong( uBackLightColor, vBackLightNorm, vPos, vNorm, model_color, uCamPos );

     frag_color = keyPhong + fillPhong + backPhong;
}



vec4 blinn_phong( vec4 lightColor, vec3 lightVector, vec3 point, vec3 pointNorm, vec4 modelC, vec3 camPos )
{
  
  vec4 Ka = ambientStren * lightColor;

  normalize( pointNorm );
  normalize( lightVector );
  float diffuse = max(dot(pointNorm, lightVector), 0.0);
  vec4 Kd = lightColor * diffuse * diffuseSten;

  vec3 halfway = normalize(camPos + lightVector);
  vec3 reflectDir = normalize( reflect(-lightVector, pointNorm) );
  float spec = pow(max(dot(halfway, pointNorm), 0.0), 10);
  vec4 Ks =  specularSten * spec * lightColor;  

  return ( ( Ka + Kd + Ks ) * modelC ); //need change for multi light

}

vec4 phong( vec4 lightColor, vec3 lightVector, vec3 point, vec3 pointNorm, vec4 modelC, vec3 camPos  )
{

  vec4 Ka = ambientStren * lightColor;

  normalize( pointNorm );
  normalize( lightVector );
  float diffuse = max(dot(pointNorm, lightVector), 0.0);
  vec4 Kd = lightColor * diffuse * diffuseSten;
  

  vec3 viewDir = normalize(camPos - vPos);
  vec3 reflectDir = normalize( reflect(-lightVector, pointNorm) );
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 100);
  vec4 Ks =  specularSten * spec * lightColor;  

  return ( ( Ka + Kd + Ks ) * modelC ); //need change for multi light

}



