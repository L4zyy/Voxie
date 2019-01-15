#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 24) out;

in VS_OUT {
	vec3 color;
} gs_in[];

uniform mat4 view;
uniform mat4 projection;

out vec3 fColor;
out vec2 faceCoords;

void createVertex (vec3 offset, vec2 facePos) {
	vec4 actualOffset = vec4(offset, 0.0f);
	vec4 worldPosition = gl_in[0].gl_Position + actualOffset;
	gl_Position = projection * view * worldPosition;
	fColor = gs_in[0].color;
	faceCoords = facePos;
	EmitVertex();
}

void main() {
	// BACKWARD
	createVertex(vec3(-0.5, 0.5, 0.5), vec2(-0.5, 0.5));
	createVertex(vec3(-0.5, -0.5, 0.5), vec2(-0.5, -0.5));
	createVertex(vec3(0.5, 0.5, 0.5), vec2(0.5, 0.5));
	createVertex(vec3(0.5, -0.5, 0.5), vec2(0.5, -0.5));
	
	EndPrimitive();
	
	// RIGHT
	createVertex(vec3(0.5, 0.5, 0.5), vec2(0.5, 0.5));
	createVertex(vec3(0.5, -0.5, 0.5), vec2(-0.5, 0.5));
	createVertex(vec3(0.5, 0.5, -0.5), vec2(0.5, -0.5));
	createVertex(vec3(0.5, -0.5, -0.5), vec2(-0.5, -0.5));
	
	EndPrimitive();
	
	// FRONT
	createVertex(vec3(0.5, 0.5, -0.5), vec2(0.5, 0.5));
	createVertex(vec3(0.5, -0.5, -0.5), vec2(0.5, -0.5));
	createVertex(vec3(-0.5, 0.5, -0.5), vec2(-0.5, 0.5));
	createVertex(vec3(-0.5, -0.5, -0.5), vec2(-0.5, -0.5));
	
	EndPrimitive();
	
	// LEFT
	createVertex(vec3(-0.5, 0.5, -0.5), vec2(0.5, -0.5));
	createVertex(vec3(-0.5, -0.5, -0.5), vec2(-0.5, -0.5));
	createVertex(vec3(-0.5, 0.5, 0.5), vec2(0.5, 0.5));
	createVertex(vec3(-0.5, -0.5, 0.5), vec2(-0.5, 0.5));
	
	EndPrimitive();
	
	// UP
	createVertex(vec3(0.5, 0.5, 0.5), vec2(0.5, 0.5));
	createVertex(vec3(0.5, 0.5, -0.5), vec2(0.5, -0.5));
	createVertex(vec3(-0.5, 0.5, 0.5), vec2(-0.5, 0.5));
	createVertex(vec3(-0.5, 0.5, -0.5), vec2(-0.5, -0.5));
	
	EndPrimitive();
	
	// DOWN
	createVertex(vec3(-0.5, -0.5, 0.5), vec2(-0.5, 0.5));
	createVertex(vec3(-0.5, -0.5, -0.5), vec2(-0.5, -0.5));
	createVertex(vec3(0.5, -0.5, 0.5), vec2(0.5, 0.5));
	createVertex(vec3(0.5, -0.5, -0.5), vec2(0.5, -0.5));
	
	EndPrimitive();
}