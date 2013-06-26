#version 330

in vec3 color;
smooth in vec3 vNormal;

out vec3 outColor;

void main(){
	float diffuseIntensity = clamp(dot(normalize(vNormal), -normalize(vec3(3, -4, -2))), 0.2, 0.8);
	outColor = color * (diffuseIntensity + 0.2);
}