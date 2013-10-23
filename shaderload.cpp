#include "shader.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
//Shamelessly stolen.
#include <sys/stat.h>

bool T5_IsFile(const char *path){
    struct stat buf;
    stat(path, &buf);
    return S_ISREG(buf.st_mode);
}

bool T5_IsDir(const char *path){
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

const char * loadTextFile(const char * path){

    if(!T5_IsFile(path)){
        printf("File %s does not exist.\n");
        return NULL;
    }

    FILE *textfile = fopen(path, "r");

    fseek(textfile, 0, SEEK_END);
    size_t filesize = ftell(textfile);
    fseek(textfile, 0, SEEK_SET);

    char *text = (char *)malloc(filesize+1);
    fread(text, 1, filesize, textfile);
    text[filesize] = '\0';

    fclose(textfile);
    return text;
}

GLuint createShader(const char *text, GLenum type){
    if(text==NULL){
        printf("Emtpy string given.\n");
        return 0;
    }
    GLuint shader = glCreateShader(type);
    if(shader==0){
        printf("Something went terribly wrong, the shader index was 0.\n");
    }
    printf("Source:\n%s\n", text);
    GLint tsize = strlen(text)+2;

    glShaderSource(shader, 1, &text, &tsize);

    glCompileShader(shader);

    GLint shader_status;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_status);

    if (shader_status==GL_FALSE) {
        printf("Failed to compile shader.\n");

        GLint log_size;
        GLint written = 0;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
        char *log_text = (char *)malloc(log_size);
        glGetShaderInfoLog(shader, log_size, &written, log_text);
        if(written==0)
            printf("No log was written.\n");
        if(written>log_size)
            printf("Your OpenGL driver just wrote past the end of my buffer. I told it not to, really!\n");
        printf("%s\n", log_text);
        free(log_text);
        glDeleteShader(shader);

        return 0;
    }
    printf("Shader compiled ok. ID number %i.\n", shader);
    return shader;

}

GLuint createProgram(GLuint frag, GLuint vert){
    if((glIsShader(frag)==GL_FALSE)||(glIsShader(vert)==GL_FALSE)){
        printf("One or more shader was invalid\n\tFrag %s\tVert %s\n", (glIsShader(frag)==GL_TRUE)?"good":"bad", (glIsShader(vert)==GL_TRUE)?"good":"bad");
        //return 0;
    }

    GLint program_status;

    GLint fragstat, vertstat;

    glGetShaderiv(frag, GL_SHADER_TYPE, &fragstat);

    if(fragstat!=GL_FRAGMENT_SHADER)
        printf("Invalid fragment shader.\n");

    glGetShaderiv(vert, GL_SHADER_TYPE, &vertstat);

    if(vertstat!=GL_VERTEX_SHADER)
        printf("Invalid vertex shader.\n");

    if((fragstat!=GL_FRAGMENT_SHADER)||(vertstat!=GL_VERTEX_SHADER)){
        printf("Bad shader(s). Exiting.\n");
        //return 0;

    }

    GLuint prog = glCreateProgram();

    glAttachShader(prog, frag);
    glAttachShader(prog, vert);
    printf("Linking Program.\n");
    glLinkProgram(prog);

    glGetProgramiv(prog, GL_LINK_STATUS, &program_status);

    if(!program_status){
        printf("Could not link program.\n");
        GLint log_size;
        char *log_text;

        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &log_size);
        log_text = (char *)malloc(log_size+1);
        glGetProgramInfoLog(prog, log_size, NULL, log_text);
        printf("%s\n", log_text);
        free(log_text);
        glDeleteProgram(prog);

        return 0;

    }
    printf("Program linked ok.\n");
    return prog;

}








