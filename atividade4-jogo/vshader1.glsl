#version 400

layout ( location = 0) in vec4 vPosition;
layout ( location = 1) in vec4 vColors;

out vec4 v2fcolor;

uniform float scaling;
uniform vec4 translation;

void main ()
{
    gl_Position = vPosition*vec4(scaling, scaling, scaling, 1) + translation;
//    gl_Position = vPosition*.5;
//    gl_Position.x = vPosition.x*1.5;
//    vPosition.y = vPosition.y*1.2;
//    gl_Position.xy = vPosition.yx;
    gl_Position.w = 1;

    v2fcolor = vColors;

//    v2fcolor.grba = vColors.rgba;
}
