#version 330 core
out vec4 FragColor;

uniform float borderWidth;
uniform vec3 borderColor;

in vec3 fColor;
in vec2 faceCoords;

void main() {
	float minX = -0.5f + borderWidth;
	float maxX = 0.5f - borderWidth;
	float minY = -0.5f + borderWidth;
	float maxY = 0.5f - borderWidth;

	if (faceCoords.x < minX || faceCoords.x > maxX || faceCoords.y < minY || faceCoords.y > maxY)
		FragColor = vec4(borderColor, 1.0f);
	else
		FragColor = vec4(fColor, 1.0f);
}
