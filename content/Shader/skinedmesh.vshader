#version 330 core

const int vertex_bone = 16;

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textCoord;
layout (location = 3) in ivec4 ids;
layout (location = 4) in ivec4 ids1;
layout (location = 5) in ivec4 ids2;
layout (location = 6) in ivec4 ids3;
layout (location = 7) in vec4 weights;
layout (location = 8) in vec4 weights1;
layout (location = 9) in vec4 weights2;
layout (location = 10) in vec4 weights3;

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

	mat4 BoneTransform1 = mat4(0.0);
	for(int i = 0; i < 4; i++)
	{
		BoneTransform1 += gbones[ids1[i]] * weights1[i];
	}

	mat4 BoneTransform2 = mat4(0.0);
	for(int i = 0; i < 4; i++)
	{
		BoneTransform2 += gbones[ids2[i]] * weights2[i];
	}

	mat4 BoneTransform3 = mat4(0.0);
	for(int i = 0; i < 4; i++)
	{
		BoneTransform3 += gbones[ids3[i]] * weights3[i];
	}

    vec4 posL = (BoneTransform+BoneTransform1+BoneTransform2+BoneTransform3) * vec4(pos, 1.0);
	TextCoord = textCoord;
	gl_Position =  projection * view * model * posL;
}