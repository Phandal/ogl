#version 410 core
out vec4 FragColor;

in vec3 myColor;
in vec2 TexCoord;

uniform sampler2D myTexture;

void main() {
 FragColor = texture(myTexture, TexCoord);
 // FragColor = vec4(myColor, 0.0);
}
