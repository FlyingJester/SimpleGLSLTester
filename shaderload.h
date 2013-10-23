#ifndef SHADERLOAD_HEAD
#define SHADERLOAD_HEAD

const char * loadTextFile(const char * path);
GLuint createShader(const char *text, GLenum type);
GLuint createProgram(GLuint frag, GLuint vert);

#endif  //SHADERLOAD_HEAD
