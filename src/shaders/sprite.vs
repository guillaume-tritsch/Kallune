#version 410 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTex;

uniform vec2 position;
uniform vec2 spriteOffset;
uniform vec2 spriteScale;

out vec2 TexCoord;

void main() {
    vec2 scaledPos = aPos * spriteScale * vec2(800.0 / 100.0, 600.0 / 100.0); // normalize sprite size to screen
    gl_Position = vec4((scaledPos + position) / vec2(400.0, 300.0) - 1.0, 0.0, 1.0);
    TexCoord = aTex * spriteScale + spriteOffset;
}
