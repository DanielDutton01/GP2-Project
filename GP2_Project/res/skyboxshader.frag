#version 420 core

layout (binding = 0) uniform sampler3D tex_cubemap;

in VS_OUT
{
vec3 normal;
vec3 view;
}fs_in;

out vec4 color;

void main(void)
{
//Reflect view vector about the plane defined by the normal at the fragment
vec3 r = reflect(fs_in.view, normalize(fs_in.normal));

//Sample from scaled using reflection vector
color = texture(tex_cubemap, r);
}
