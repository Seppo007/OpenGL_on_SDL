#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>
#include <string>
#include "../../OpenGL_on_SDL/shaderLoading/loadShaders.hpp"

// PROTOTYPING
bool init();
void logSDLError(std::ostream& os, std::string);
SDL_Window* setupWindow(SDL_Window *win, SDL_GLContext &ctx);
void initGL(GLuint &vertexbuffer);
void updateMVP(glm::mat4 &MVP, GLuint &programID);
void clearAll(SDL_Window *win, SDL_GLContext &ctx);
void polling(SDL_Event &event);
void draw();
void matrixTest();

static GLuint MatrixID;
static glm::mat4 MVP;
static float XrotationVar = 0, YrotationVar = 0;
static float xvar = 0.0f, yvar = 0.0f, zvar = 10.0f;        // View is centered on Origin with z-distance of 10

int main(int, char**){

    SDL_Window *win = nullptr;
    SDL_GLContext ctx;

    SDL_Event event;
    GLuint vbo_Vertexbuffer;

    init();

    win = setupWindow(win, ctx);

    glm::mat4 myMat;

    // Defining a Shader Program to be applied later
    GLuint programID = loadShaders("..\\..\\OpenGL_on_SDL\\transformations\\shader.vert", "..\\..\\OpenGL_on_SDL\\transformations\\shader.frag");

    initGL(vbo_Vertexbuffer);

    // MAIN LOOP
    do {

        polling(event);

        // Use Shader Program
        glUseProgram(programID);
        updateMVP(MVP, programID);
        draw();

        // Swap Backbuffer to Frontbuffer
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

    win = SDL_CreateWindow("Testing Transformations via MVP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

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


void initGL(GLuint &vertexbuffer){

    GLuint VAO_VertexArrayID;
    // Allocate and assign 1 Vertex Array Object to our handle
    glGenVertexArrays(1, &VAO_VertexArrayID);
    glBindVertexArray(VAO_VertexArrayID);

    // An array of 3 vectors which represents 3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
       1.0f, -1.0f, 0.0f,
       -1.0f, -1.0f, 0.0f,
       0.0f, 1.0f, 0.0f,
    };

    // Generate 1 Vertex Buffer Object, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);

    // Bind our VBO as being the active buffer and storing vertex attributes (coordinates)
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    // Give our vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // Specify that our coordinate data is going into attribute index 0, and contains 3 floats per vertex
    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       0                   // array buffer offset
    );

    // Set Clear Color
    glClearColor(0.35, 0, 0, 1);

}


void draw(){

    // Clear Background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform. For each model you render, since the MVP will be different (at least the M part)
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

    glDisableVertexAttribArray(0);

}


void updateMVP(glm::mat4 &MVP, GLuint &programID){

    // Define Matrices
    // Projection Matrix
    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 2.0f, 100.0f); // FOV, Format, Near Clip, Far Clip

    // Camera Matrix
    glm::mat4 View = glm::lookAt(
        glm::vec3(xvar, yvar, zvar),            // Camera Position at 4, 3, 3
        glm::vec3(xvar, yvar, zvar-10.f),       // Looks at origin
        glm::vec3(0, 1, 0));    // Head is up

    // Model & MVP Matrix
    glm::mat4 Xrotate = glm::rotate(glm::mat4(1.0f), XrotationVar, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 Yrotate = glm::rotate(glm::mat4(1.0f), YrotationVar, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::mat4(1.0f) * Xrotate * Yrotate;
    MVP = Projection * View * Model;

    // SET MVP Matrix
    MatrixID = glGetUniformLocation(programID, "MVP");

}


void polling(SDL_Event &event){

    SDL_PollEvent(&event);

    if(event.type == SDL_KEYDOWN){
        switch(event.key.keysym.sym){

            case SDLK_UP:
                yvar += 0.15f;
                break;

            case SDLK_DOWN:
                yvar -= 0.15f;
                break;

            case SDLK_RIGHT:
                xvar += 0.15f;
                break;

            case SDLK_LEFT:
                xvar -= 0.15f;
                break;

            case SDLK_PAGEUP:
                zvar -= 0.15f;
                break;

            case SDLK_PAGEDOWN:
                zvar += 0.15f;
                break;

            case SDLK_q:
                YrotationVar -= 0.1f;
                break;

            case SDLK_e:
                YrotationVar += 0.1f;
                break;

            case SDLK_w:
                XrotationVar += 0.1f;
                break;

            case SDLK_s:
                XrotationVar -= 0.1f;
                break;
        }
    }
}


void clearAll(SDL_Window *win, SDL_GLContext &ctx){

    SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(win);
    SDL_Quit();

}


void matrixTest(){

    glm::mat4 myTranslateMatrix = glm::translate(glm::mat4(), glm::vec3(20.0f, 0.0f, 0.0f));
    glm::vec4 myVec(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec4 transformedVector = myTranslateMatrix * myVec;

    std::cout << glm::to_string(transformedVector) << std::endl;

}
