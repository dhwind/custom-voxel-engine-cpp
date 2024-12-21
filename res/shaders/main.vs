#version 330 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_texCoord;

out vec2 a_texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	a_texCoord = v_texCoord;
	gl_Position =  projection * view * model * vec4(v_position, 1.0);
}