#version 330
uniform sampler2D tex;
uniform int bordure;

in  vec2 TextureCoord;
out vec4 Color;

void main(void) {
  if( bordure != 0 && (TextureCoord.s < 0.03 || 
          TextureCoord.t < 0.03 ||
		      (1 - TextureCoord.s) < 0.03 || 
		      (1 - TextureCoord.t) < 0.03 ) )
    Color = vec4(0, 1, 2, 3);
  else
    Color = texture(tex, TextureCoord);
}
