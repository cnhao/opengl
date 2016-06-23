#version 330 core
in vec2 Texcoord;

out vec4 color;
uniform vec4 myColor;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
void main()
{
//color = vec4(1.0f, 0.5f, 0.2f, 1.0);
//    color = texture(ourTexture, Texcoord);
    color = mix(texture(ourTexture1, Texcoord), texture(ourTexture2, Texcoord), 0.2);
//    color = myColor;
}