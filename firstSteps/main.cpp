#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <string>


// PROTOTYPING
bool init();
void logSDLError(std::ostream& os, std::string);
SDL_Window* setupWindow(SDL_Window *win, SDL_GLContext &ctx);
void drawSomething(SDL_Window *win);


int main(int, char**){
	
    SDL_Window *win = nullptr;
    SDL_GLContext ctx;

    init();

    win = setupWindow(win, ctx);

    drawSomething(win);

    SDL_Delay(1500);

    return 0;
	
}


bool init(){
    bool initOK = true;

    // Preparing OpenGL Attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        logSDLError(std::cerr, "SDL Initializing");
    }

    return initOK;

}


void logSDLError(std::ostream& os, std::string err){
    os << "An error occured whithin \"" << err << "\" -> " << SDL_GetError() << std::endl;
}


SDL_Window* setupWindow(SDL_Window *win, SDL_GLContext &ctx){

    win = SDL_CreateWindow("Testing OpenGL on SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    ctx = SDL_GL_CreateContext(win);
    SDL_GL_MakeCurrent(win, ctx);

    glewInit();

    return win;

}


void drawSomething(SDL_Window *win){


    GLuint VertexArrayID;

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    static const GLfloat g_vertex_buffer_data[] = {
           -1.0f, -1.0f, 0.0f,
           1.0f, -1.0f, 0.0f,
           0.0f,  1.0f, 0.0f,
        };

    SDL_GL_SwapWindow(win);

}
