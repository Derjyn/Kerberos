#version 420

in vec3 p_eye;
in vec3 n_eye;

layout (location = 0) out vec3 def_p;
layout (location = 1) out vec3 def_n;

void main ()
{
  def_p = p_eye;
  def_n = n_eye;
}