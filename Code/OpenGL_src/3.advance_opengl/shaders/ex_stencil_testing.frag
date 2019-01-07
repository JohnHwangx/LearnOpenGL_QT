#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texKitten;
uniform sampler2D texPuppy;

void main()
{
	FragColor = vec4(ourColor, 1.0) * mix(texture(texKitten, TexCoord),texture(texPuppy,TexCoord),0.5);
	//FragColor = texture(texture1, TexCoord);
}