#version 410 core
out vec4 FragColor;

in vec3 myColor;
in vec2 TexCoord;

uniform sampler2D containerTexture;
uniform sampler2D smileyTexture;

void main() {
  vec4 smileyColor = texture(smileyTexture, TexCoord);
  if (smileyColor.w < 0.1) {
    FragColor = texture(containerTexture, TexCoord) * vec4(myColor, 1.0);
  } else {
    FragColor = mix(texture(containerTexture, TexCoord), smileyColor, 0.2) * vec4(myColor, 1.0);
  }
}
