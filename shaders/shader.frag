#version 430 core
out vec4 FragColor;

in vec3 Color;
in vec2 TexCoord;
flat in int isTexture;

// texture samplers
uniform sampler2D texture1;

void main()
{
	if (isTexture == 1)
	{
		FragColor = texture(texture1, TexCoord);
	}
	else
	{
		FragColor = vec4(Color, 1.0);
	}
}