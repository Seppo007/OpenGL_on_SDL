#ifndef LOADSHADERS
#define LOADSHADERS

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>
#include <string>

extern GLuint loadShaders(const char *vertex_file_path, const char *fragment_file_path);

#endif // LOADSHADERS

