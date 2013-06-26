#version 330

uniform mat4 modelMatrix, viewMatrix, projectionMatrix;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexNormal;

out vec3 color;
smooth out vec3 vNormal;

void main(){
	color = vertexColor;
		
	vec4 transformedNormal = transpose(inverse(modelMatrix)) * vec4(vertexNormal, 0);
	vNormal = transformedNormal.xyz;
	
	vec4 position = vec4(vertexPosition, 1);
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * position;
}