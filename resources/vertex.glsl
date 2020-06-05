#version 430 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

layout(location = 2) uniform vec3 u_CameraPosition;
layout(location = 3) uniform mat4 u_mvpMatrix;

out vec2 vs_TexCoord;

out vec3 vs_CameraDirection;
out vec3 vs_ObjectPosition;

void main() {
	gl_Position = u_mvpMatrix * vec4(a_Position.xyz, 1.0);
	
	vs_TexCoord = a_TexCoord;

	vs_CameraDirection = a_Position - u_CameraPosition;
	vs_ObjectPosition = a_Position.xyz;
}