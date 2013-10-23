
#include "shader.h"
#include "shaderload.h"
#include <cstdio>
#include <cstdlib>


#ifdef __linux__
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glx.h>

typedef Display vwindow;
typedef Window window;
typedef XVisualInfo visualinfo;
typedef XSetWindowAttributes windowattr;
typedef XWindowAttributes windowattrg;
typedef Colormap colormap;

GLint attr[] = {GLX_RGBA, 0, 24, 0, 0};

#endif // __linux__


void SetDefaults(){
    glClearColor(0, 0, 0, 255);
    glClearDepth(1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
}

void CreateWindow(uint32_t w, uint32_t h){

    vwindow *disp = XOpenDisplay(NULL);

    if(disp==NULL){
        printf("Could not open X display.\n");
        return;
    }

    window wind = DefaultRootWindow(disp);

    visualinfo * vinfo = glXChooseVisual(disp, 0, attr);
    if(vinfo==NULL){
        printf("No X visual found.\n");
        return;
    }

    colormap cm = XCreateColormap(disp, wind, vinfo->visual, AllocNone);

    windowattr windattr;

    windattr.colormap = cm;

    windattr.event_mask = ExposureMask | KeyPressMask;

    window mainwindow = XCreateWindow(disp, wind, 0, 0, w, h, 0, vinfo->depth, InputOutput, vinfo->visual, CWColormap | CWEventMask, &windattr);

    XMapWindow(disp, wind);

    XStoreName(disp, wind, "GL Shader Tester");

    GLXContext context = glXCreateContext(disp, vinfo, NULL, GL_TRUE);

    glXMakeCurrent(disp, wind, context);

    //glViewPort(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, 1, -1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[]){

CreateWindow(800, 600);
SetDefaults();

const char *vert = loadTextFile("vert.vs");
const char *frag = loadTextFile("frag.fs");

GLuint vertsh = createShader(vert, GL_VERTEX_SHADER);
GLuint fragsh = createShader(frag, GL_FRAGMENT_SHADER);

printf("Shader IDs: %i\t%i\n", vertsh, fragsh);

GLuint prog = createProgram(fragsh, vertsh);

printf("Press return to quit.\n");

getc(stdin);

    return 0;
}
