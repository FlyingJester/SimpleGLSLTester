#ifndef SHADER_HEAD
#define SHADER_HEAD
#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL_opengl.h>

enum shader_status {NOTHING, ERROR_COMPILING, COMPILED};

struct shader {
    GLuint vert_shader;
    GLuint frag_shader;

    shader_status status;

};

#endif
