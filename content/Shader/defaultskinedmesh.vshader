#version 330 core

const int vertex_bone = 4;

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textCoord;
layout (location = 3) in ivec4 ids;
layout (location = 4) in vec4 weights;

out vec2 TextCoord;

const int MAX_BONES = 200;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 gbones[MAX_BONES];

void main()
{
	mat4 BoneTransform = mat4(0.0);

	for(int i = 0; i < 4; i++)
	{
		BoneTransform += gbones[ids[i]] * weights[i];
	}

    vec4 posL = BoneTransform * vec4(pos, 1.0);
	TextCoord = textCoord;
	gl_Position =  projection * view * model * posL;
}