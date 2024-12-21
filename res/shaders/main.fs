#version 330 core

in vec2 a_texCoord;
out vec4 f_color;

uniform sampler2D u_texture0;

void main(){
	f_color = texture(u_texture0, a_texCoord);
}