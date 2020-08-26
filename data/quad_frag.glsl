#version 300 es
precision highp float;

uniform vec4 u_color;

out vec4 finalColor;

void main(){
	finalColor = u_color;
}
