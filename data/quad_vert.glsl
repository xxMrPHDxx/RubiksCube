#version 300 es

in vec3 a_pos;

uniform mat4 u_view;
uniform mat4 u_cam;
uniform mat4 u_obj;

void main(){
	gl_Position = u_view * u_cam * u_obj * vec4(a_pos, 1.0);
}
