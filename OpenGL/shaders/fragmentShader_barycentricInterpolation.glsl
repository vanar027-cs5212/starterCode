#version 330 core

in vec3 vertexColor;
layout(location=0) out vec4 fragmentColor; //[cite: 1]

void main(void) {
  fragmentColor = vec4(vertexColor, 1.0);
}