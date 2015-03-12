#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <string>


// PROTOTYPING
bool init();
void logSDLError(std::ostream& os, std::string);
SDL_Window* setupWindow(SDL_Window *win, SDL_GLContext &ctx);
void initGL(GLuint &vertexbuffer);
void draw();
void clearAll(SDL_Window *win, SDL_GLContext &ctx);


int main(int, char**){

    SDL_Window *win = nullptr;
    SDL_GLContext ctx;

    SDL_Event event;

    init();

    // win = weg lassen funktioniert nicht, why?
    win = setupWindow(win, ctx);


    // MAIN LOOP

    glClearColor(0.8f, 0.1f, 0.1f, 1.0f);

    do {

        SDL_PollEvent(&event);

        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(win);

    } while(event.key.keysym.sym != SDLK_ESCAPE && event.type != SDL_QUIT);

    clearAll(win, ctx);

    return 0;
	
}


bool init(){
    bool initOK = true;

    // Preparing OpenGL Attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
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

    if(!win){
        logSDLError(std::cerr, "Creating Window");
        SDL_Quit();
    } else {
        ctx = SDL_GL_CreateContext(win);
        SDL_GL_MakeCurrent(win, ctx);

        // GLEW INITIALIZATION
        if(glewInit() != 0){
            logSDLError(std::cerr, "Initializing GLEW");
            SDL_DestroyWindow(win);
            win = nullptr;
            SDL_Quit();
        } else {
            glewExperimental = true;
        }
    }

    return win;

}


void clearAll(SDL_Window *win, SDL_GLContext &ctx){

    SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(win);
    SDL_Quit();

}
