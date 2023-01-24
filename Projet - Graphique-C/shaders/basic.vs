#version 330

uniform mat4 matrice_m;
uniform mat4 matrice_v;
uniform mat4 matrice_p;
uniform float Texture;
layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 v;
layout (location = 2) in vec2 Coord;
 
out vec2 TextureCoord;

void main(void) {
  gl_Position = matrice_p * matrice_v * matrice_m * vec4(Pos.xyz, 1.0);
  TextureCoord = Texture * Coord;
}
