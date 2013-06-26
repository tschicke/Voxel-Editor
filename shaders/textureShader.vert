#version 330

uniform mat4 modelMatrix, viewMatrix, projectionMatrix;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

out vec2 UV;
smooth out vec3 vNormal;
out float vertexYPos;

void main(){
	UV = vertexUV;//TODO flip texture to OGL coords
		
	vec4 transformedNormal = transpose(inverse(modelMatrix)) * vec4(vertexNormal, 0);
	vNormal = transformedNormal.xyz;
	
	vec4 positionWorldSpace = modelMatrix * vec4(vertexPosition, 1);
	vec4 positionWindowSpace = projectionMatrix * viewMatrix * positionWorldSpace;
	vertexYPos = positionWorldSpace.y;
	gl_Position = positionWindowSpace;
}