#version 330 core

in vec3 vertexColor; // Matches the 'out' name and type from the vertex shader
layout(location=0) out vec4 fragmentColor; //[cite: 1]

void main(void) {
  fragmentColor = vec4(vertexColor, 1.0);
}