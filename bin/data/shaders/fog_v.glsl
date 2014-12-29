#version 420

in vec3 vertex_position;
in vec3 vertex_normal;
in vec2 uv0;

uniform mat4 view, proj;

out vec3 normal;
out vec3 pos_eye;
out vec2 texcoord;

void main()
{
  texcoord = uv0;

  pos_eye = (view * vec4 (vertex_position, 1.0)).xyz;
  normal = vertex_normal;
  gl_Position = proj * vec4 (pos_eye, 1.0);
}