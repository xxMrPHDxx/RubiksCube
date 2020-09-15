#version 300 es
#include <stdio.h>
in vec3 a_pos;

uniform mat4 u_view;
uniform mat4 u_cam;
uniform mat4 u_obj;

void main(){
	printf(a_pos.x);
	gl_Position = u_view * vec4(a_pos, 1.0);
}
