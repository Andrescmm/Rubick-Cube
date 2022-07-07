#version 330 core
out vec4 FragColor;

in vec3 Color;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
	vec3 ResultColor = Color;
	FragColor = texture(ourTexture, TexCoord);
	//FragColor = texture(ourTexture, TexCoord) * vec4(ResultColor, 1.0f);
}