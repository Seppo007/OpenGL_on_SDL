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
void draw(GLuint &vertexbuffer);
void clearAll(SDL_Window *win, SDL_GLContext &ctx);

int main(int, char**){
	
    SDL_Window *win = nullptr;
    SDL_GLContext ctx;

    SDL_Event event;
    GLuint vbo_Vertexbuffer;

    init();

    win = setupWindow(win, ctx);

    initGL(vbo_Vertexbuffer);

    // MAIN LOOP

    do {

        SDL_PollEvent(&event);
        draw(vbo_Vertexbuffer);
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
        if(glewInit() < 0){
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


void initGL(GLuint &vertexbuffer){

    GLuint VAO_VertexArrayID;
    // Allocate and assign 1 Vertex Array Object to our handle
    glGenVertexArrays(1, &VAO_VertexArrayID);
    glBindVertexArray(VAO_VertexArrayID);

    // An array of 3 vectors which represents 3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
       -0.5f, -0.5f, 0.0f,
       0.0f, 0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
    };

    // Generate 1 Vertex Buffer Object, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);

    // Bind our VBO as being the active buffer and storing vertex attributes (coordinates)
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    // Give our vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

}


void draw(GLuint &vertexbuffer){

    // Specify that our coordinate data is going into attribute index 0, and contains 3 floats per vertex
    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       0                   // array buffer offset
    );

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

    glDisableVertexAttribArray(0);

}


void clearAll(SDL_Window *win, SDL_GLContext &ctx){

    SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(win);
    SDL_Quit();

}
