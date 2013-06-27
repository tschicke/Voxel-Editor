#version 330

in vec3 color;
smooth in vec3 vNormal;

uniform vec3 lightDir;

out vec3 outColor;

void main(){
	float diffuseIntensity = clamp(dot(normalize(vNormal), -normalize(vec3(1, -5, -9))), 0.0, 0.8);
	outColor = color * (diffuseIntensity + 0.2);
}