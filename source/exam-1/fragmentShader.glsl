#version 330
in vec3 mycolor;
out vec4 color;
void main(void) {
     color = vec4(mycolor, 1.0);
}
