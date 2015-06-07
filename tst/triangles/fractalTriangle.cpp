
#define GLEW_STATIC

#include <stdio.h>
#include <stdlib.h>
#include <cmath>

/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include "GL/glew.h"

#include "GL/freeglut.h"

#include "common/shader.cpp"

GLuint programID;
GLuint vertexID;
GLuint vertexBuffer;

int size = 8;
int time = 1000;


GLfloat vertices[10000];

GLfloat my_vertices[10000];


int init_resources() {
    my_vertices[0] = -1.0f; my_vertices[1] = -0.75f;
    my_vertices[2] = 0.0f; my_vertices[3] = 0.75f;
    my_vertices[4] = 1.0f; my_vertices[5] = -0.75f;
    my_vertices[6] = -1.0f; my_vertices[7] = -0.75f;

/*
    my_vertices[0] = -1.0f; my_vertices[1] = 0.0f;
    my_vertices[2] = -0.5f; my_vertices[3] = 0.0f;
    my_vertices[4] = 0.0f; my_vertices[5] = 0.5f;
    my_vertices[6] = 0.5f; my_vertices[7] = 0.0f;
    my_vertices[8] = 1.0f; my_vertices[9] = 0.0f;
/*
    my_vertices[4] = -0.5f; my_vertices[5] = 0;
    my_vertices[6] = 0; my_vertices[7] = 0.5f;
    my_vertices[8] = 0; my_vertices[9] = 0.5f;
    my_vertices[10] = 0.5; my_vertices[11] = 0;
    my_vertices[12] = 0.5; my_vertices[13] = 0;
    my_vertices[14] = 1; my_vertices[15] = 0;
*/
    // Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    //setup vertexID
    glGenVertexArrays(1, &vertexID);
    glBindVertexArray(vertexID);

    //use commmon to load shaders
    programID = LoadShaders( "VertexShader.vertexshader", "FragmentShader.fragmentshader" );

    return programID;
}
int last = 0;
void update(int value) {

    if (size > 100) {
       my_vertices[0] = -1.0f; my_vertices[1] = -0.75f;
        my_vertices[2] = 0.0f; my_vertices[3] = 0.75f;
        my_vertices[4] = 1.0f; my_vertices[5] = -0.75f;
        my_vertices[6] = -1.0f; my_vertices[7] = -0.75f;

        last = 0;
        size = 8;
    }
    else {

        int i, n;

        float x0, x1, x2, x3, x4, x5, y0, y1, y2, y3, y4, y5;


            i = last;

            x0 = my_vertices[i];
            y0 = my_vertices[i+1];
            x1 = my_vertices[i+2];
            y1 = my_vertices[i+3];
            x2 = my_vertices[i+4];
            y2 = my_vertices[i+5];

            x3 = (x0 + x1)/2;
            y3 = (y0 + y1)/2;

            x4 = (x1 + x2)/2;
            y4 = (y1 + y2)/2;

            x5 = (x0 + x2)/2;
            y5 = (y0 + y2)/2;

            // 3 4 5
            my_vertices[i+8] = x3;
            my_vertices[i+9] = y3;
            my_vertices[i+10] = x4;
            my_vertices[i+11] = y4;
            my_vertices[i+12] = x5;
            my_vertices[i+13] = y5;
            my_vertices[i+14] = x3;
            my_vertices[i+15] = y3;

            //my_vertices[i+16] = (x3+x4)/2;
            //my_vertices[i+17] = (y3+y4)/2;
            last = last + 8;

            size = last+8;

        /*
        printf("\n\nTESTE: %d\n", size);

        for (i = 0 ; i < last; i+=2) {
            printf("%f\t%f\n", my_vertices[i], my_vertices[i+1]);
        }
        */
    }


    glutPostRedisplay();
    //getchar();
    glutTimerFunc(time, update,0);

}

//metodo para desenhar
void onDisplay() {

    // Clear the screen
	glClear( GL_COLOR_BUFFER_BIT );


    glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(GLfloat) * size), my_vertices, GL_STATIC_DRAW);

    //utilizar o nosso shader
    glUseProgram(programID);

    //1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        2,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0             // array buffer offset
    );


    // Draw the triangle !
    glDrawArrays(GL_LINE_STRIP, 0, (sizeof(GLfloat) * size)); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(0);


	glutSwapBuffers();
    glutPostRedisplay();

}


//libera recursos
void free_resources() {

    glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &vertexID);
    glDeleteProgram(programID);

}


int main(int argc, char* argv[]) {

    //inicia janela
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Window Title");

    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
        return 1;
    }

    if (init_resources() != 0) {
        glutDisplayFunc(onDisplay);
        glutTimerFunc(time, update,0);
        glutMainLoop();
    }

    free_resources();
    return 0;
}
