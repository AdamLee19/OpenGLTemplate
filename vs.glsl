#version 410
layout (location = 0) in vec3 vp;
uniform mat4 proj_mat, view_mat, model_mat;
void main () {

     gl_Position = vec4 (vp, 1.0);
}