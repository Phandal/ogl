#version 410 core
out vec4 FragColor;

in vec3 myColor;
in vec2 TexCoord;

uniform sampler2D containerTexture;
uniform sampler2D smileyTexture;

void main() {
 FragColor = mix(texture(containerTexture, TexCoord), texture(smileyTexture, TexCoord), 0.2) * vec4(myColor, 1.0);
}
