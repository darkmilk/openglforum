#include "myheader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

GLuint CompileShader(char *path, GLuint type) {
  GLuint shader = glCreateShader(type);
  FILE *sourcefile = fopen(path, "r");
  if(sourcefile == NULL) {
    printf("No such file \"%s\"\n", path);
    return 0;
  }
  char *source = (char *)malloc(sizeof(char) * 512);
  memset(source, 0, 512);
  unsigned i = 0;
  char ch;
  while((ch = getc(sourcefile)) != EOF) {
    source[i] = ch;
    if(( ++i % 512) == 0) {
      source = (char *)realloc(source, sizeof(char) * 512);
      memset(&source[i], 0, sizeof(char) * 512);
    }
  }
  const char *const_source = source;
  glShaderSource(shader, 1, &const_source, NULL);
  glCompileShader(shader);

  GLuint success;
  char info[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(shader, 512, NULL, info);
    fprintf(stderr, "%s\n", info);
  }
  free(source);
  return shader;
}
