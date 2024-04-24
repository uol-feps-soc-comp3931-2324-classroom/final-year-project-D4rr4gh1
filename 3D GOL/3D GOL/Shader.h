#ifndef SHADER_H
#define SHADER_H

const char* vertexShaderSource = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)glsl";

const char* fragmentShaderSource = R"glsl(
#version 330 core
out vec4 FragColor;
uniform vec3 objectColor; // Added uniform for color
void main() {
    FragColor = vec4(objectColor, 0.5);
}
)glsl";


#endif // !SHADER_H
