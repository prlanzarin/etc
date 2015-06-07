
#define GLEW_STATIC

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <unistd.h>
//OpenGL functions
#include "GL/glew.h"

//Window handler
#include "GL/freeglut.h"


// Include GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
    using namespace glm;

#include "common/shader.cpp"
#include "common/texture.cpp"
#include "common/objloader.cpp"

#include "monkey.c"

GLuint programID;
GLuint vertexID;
GLuint vertexBuffer;
GLuint uvBuffer;
GLuint matrixID;    // Get a handle for our "MVP" uniform
GLuint texture;     // To load our texture
GLuint textureID;	// Get a handle for our "myTextureSampler" uniform

std::vector<glm::vec3> vertices;
std::vector<glm::vec2> uvs;
std::vector<glm::vec3> normals;


int init_resources() {

    glEnable(GL_DEPTH_TEST); //habilita o z-buffer: prof. correta
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glGenVertexArrays(1, &vertexID); //load shaders
    glBindVertexArray(vertexID);
    programID = LoadShaders( "TransformVertexShader.vertexshader",
    "TextureFragmentShader.fragmentshader" );
    matrixID = glGetUniformLocation(programID, "MVP");


    //texture = loadDDS("uvmap.DDS");
        //textureID = glGetUniformLocation(programID, "myTextureSampler");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D, // target
        0,
// level, 0 = base, no minimap,
        GL_RGB,
// internalformat
        monkey.width,
// width
        monkey.height, // height
        0,
// border, always 0 in OpenGL ES
        GL_RGB,
// format
        GL_UNSIGNED_BYTE, // type
        monkey.pixel_data // data
    );

    bool res = loadOBJ("monkey.obj", vertices, uvs, normals);
    //vértices
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0],
    GL_STATIC_DRAW);
    //textura
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
    return programID;

}


//metodo para desenhar
void onDisplay() {


    // CODE HERE
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glUseProgram(programID);

    glm::mat4 Projection = glm::perspective(60.0f, 16.0f / 9.0f, 0.1f, 100.0f);

    glm::mat4 View = glm::lookAt(glm::vec3(5, 4.7, -9.5), // Camera is at (4,3,3), in World Space
                                glm::vec3(5, 5, -5.5), // and looks at the origin
                                glm::vec3(0,1,0)); // Head is up (set to 0,-1,0 to look upside-down));

    glm::mat4 Model = glm::mat4(1.0f);

    glm::mat4 MVP = Projection * View * Model;
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(textureID, 0);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(
        0,                  // attribute
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glVertexAttribPointer(
        1,                                // attribute
        2,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );


    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

	glutSwapBuffers();
    glutPostRedisplay();

}


//libera recursos
void free_resources() {

    glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &uvBuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &textureID);
	glDeleteVertexArrays(1, &vertexID);

}


int main(int argc, char* argv[]) {

    //inicia janela
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH|GLUT_MULTISAMPLE);
    glutInitWindowSize(800, 450);
    glutCreateWindow("Window Title");

    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
        return 1;
    }

    if (init_resources() != 0) {
        glutDisplayFunc(onDisplay);
        glutMainLoop();
    }

    free_resources();
    return 0;
}

