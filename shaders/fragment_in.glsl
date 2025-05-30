#version 410 core
out vec4 FragColor;

in vec3 myColor;

void main() {
 FragColor = vec4(myColor, 0.0);
}
