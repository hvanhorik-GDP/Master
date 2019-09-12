#version 110

uniform mat4 MVP;

attribute vec3 vColour;
attribute vec3 vPosition;
varying vec3 color;

void main()
{
    vec3 vertPosition = vPosition;
    gl_Position = MVP * vec4(vertPosition, 1.0);
    color = vColour;
}
