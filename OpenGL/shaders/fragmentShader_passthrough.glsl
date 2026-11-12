#version 330 core

in vec3 vertexColor; // Matches the 'out' name and type from the vertex shader

layout(location=0) out vec4 fragmentColor;

void main(void) {
  fragmentColor = vec4(0.49, 0.87, 0.99, 1.0);
}
