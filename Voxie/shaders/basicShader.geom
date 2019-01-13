#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 24) out;

in VS_OUT {
	vec3 color;
} gs_in[];

uniform mat4 view;
uniform mat4 projection;

out vec3 fColor;

void createVertex (vec3 offset) {
	vec4 actualOffset = vec4(offset, 0.0f);
	vec4 worldPosition = gl_in[0].gl_Position + actualOffset;
	gl_Position = projection * view * worldPosition;
	fColor = gs_in[0].color;
	EmitVertex();
}

void main() {
	createVertex(vec3(-0.5, 0.5, 0.5));
	createVertex(vec3(-0.5, -0.5, 0.5));
	createVertex(vec3(0.5, 0.5, 0.5));
	createVertex(vec3(0.5, -0.5, 0.5));
	
	EndPrimitive();
	
	createVertex(vec3(0.5, 0.5, 0.5));
	createVertex(vec3(0.5, -0.5, 0.5));
	createVertex(vec3(0.5, 0.5, -0.5));
	createVertex(vec3(0.5, -0.5, -0.5));
	
	EndPrimitive();
	
	createVertex(vec3(0.5, 0.5, -0.5));
	createVertex(vec3(0.5, -0.5, -0.5));
	createVertex(vec3(-0.5, 0.5, -0.5));
	createVertex(vec3(-0.5, -0.5, -0.5));
	
	EndPrimitive();
	
	createVertex(vec3(-0.5, 0.5, -0.5));
	createVertex(vec3(-0.5, -0.5, -0.5));
	createVertex(vec3(-0.5, 0.5, 0.5));
	createVertex(vec3(-0.5, -0.5, 0.5));
	
	EndPrimitive();
	
	createVertex(vec3(0.5, 0.5, 0.5));
	createVertex(vec3(0.5, 0.5, -0.5));
	createVertex(vec3(-0.5, 0.5, 0.5));
	createVertex(vec3(-0.5, 0.5, -0.5));
	
	EndPrimitive();
	
	createVertex(vec3(-0.5, -0.5, 0.5));
	createVertex(vec3(-0.5, -0.5, -0.5));
	createVertex(vec3(0.5, -0.5, 0.5));
	createVertex(vec3(0.5, -0.5, -0.5));
	
	EndPrimitive();
}