#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textCoord;
layout (location = 3) in ivec4 ids;
layout (location = 4) in vec4 weights;

out vec2 TextCoord;

const int MAX_BONES = 100;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 gbones[MAX_BONES];

void main()
{
	mat4 BoneTransform = gbones[ids[0]] * weights[0];
    BoneTransform += gbones[ids[1]] * weights[1];
    BoneTransform += gbones[ids[2]] * weights[2];
    BoneTransform += gbones[ids[3]] * weights[3];

    vec4 posL = BoneTransform * vec4(pos, 1.0);
	TextCoord = textCoord;
	gl_Position =  projection * view * model * posL;
}