#version 420

uniform sampler2D tex_diffuse;

in vec3 normal;
in vec3 pos_eye;
in vec2 texcoord;

uniform vec3 fog_color;
uniform vec4 fog_props;

out vec4 frag_color;

#define FOG_START 100
#define FOG_END 500
#define FOG_DENSITY 0.008

float fogFactorLinear(const float dist, const float start, const float end)
{
  return 1.0 - clamp((end - dist) / (end - start), 0.0, 1.0);
}

float fogFactorExp(const float dist, const float density)
{
  return 1.0 - clamp(exp(-density * dist), 0.0, 1.0);
}
float fogFactorExp2(const float dist, const float density)
{
  const float LOG2 = -1.442695;
  float d = density * dist;
  return 1.0 - clamp(exp2(d * d * LOG2), 0.0, 1.0);
}

void main()
{
  vec4 texel = texture(tex_diffuse, texcoord);
  frag_color = texel;

  float dist = length(-pos_eye);

  // get a fog factor (thickness of fog) based on the distance
  //float fog_fac = (dist - fog_props.y) / (fog_props.z - fog_props.y);
  float fog_fac = fogFactorExp2(dist, FOG_DENSITY);
  // constrain the fog factor between 0 and 1
  //fog_fac = clamp(fog_fac, 0.0, 1.0);

  // blend the fog colour with the lighting colour, based on the fog factor
  frag_color.rgb = mix(frag_color.rgb, fog_color, fog_fac);
}