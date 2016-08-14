#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "myheader.h"
#include <unistd.h>
void show_fps(void *c){
  while(1) {
    *(int *)c = 0;
    sleep(1);
    printf("FPS(Frames per second): %d\n", *(int *)c);
  }
}

const int width = 600, height = 600;
int main(int argc, char *argv) {
  if(glfwInit() == GL_FALSE) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    exit(-1);
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow *window = glfwCreateWindow(width, height, "Learn OpenGL", NULL, NULL);
  if(window == NULL) {
    fprintf(stderr, "Failed to create window\n");
    glfwTerminate();
    exit(-1);
  }
  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if(err != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(err));
    glfwTerminate();
    exit(-1);
  }

  GLuint vertexShader = CompileShader("vertexShader.glsl", GL_VERTEX_SHADER);
  GLuint fragmentShader = CompileShader("fragmentShader.glsl", GL_FRAGMENT_SHADER);
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  GLfloat vertices[] = {
    //       Position  |       Color
    0.0f,   1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.866f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
   -0.866f,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f
  };
  
  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);
 
  glViewport(0, 0, width, height);
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  int count = 0;
  pthread_t fps;
  pthread_create(&fps, NULL, (void *)show_fps, (void*)&count);
  
  glUseProgram(shaderProgram);
  while(glfwWindowShouldClose(window) != GL_TRUE) {
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwPollEvents();
    
    glBindVertexArray(VAO);
    vertices[0] += 0.001;
    vertices[6] += 0.001;
    vertices[12] += 0.001;
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glfwSwapBuffers(window);
    ++count;
  }
  return 0;
}
