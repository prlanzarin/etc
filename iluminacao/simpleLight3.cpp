
#define GLEW_STATIC

#include <stdio.h>
#include <stdlib.h>

#include "GL/glew.h"
#include "GL/freeglut.h"


// Include GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
    using namespace glm;

#include "common/shader.cpp"
#include "common/texture.cpp"
#include "common/objloader.cpp"

#include "woodBox.c"

GLuint programID;
GLuint matrixID;        // Get a handle for our "MVP" uniform
GLuint modelID;
//cube
GLuint vertexID;
GLuint vertexBuffer;
GLuint vertexArray;
GLuint uvBuffer;
GLuint textureID1;                  // Get a handle for our "myTextureSampler" uniform
std::vector<glm::vec3> vertices;
std::vector<glm::vec2> uvs;
std::vector<glm::vec3> normals;


bool keystates[256];


void loadTexture(unsigned int width, unsigned int height, const unsigned char * data) {

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D, // target
        0, // level, 0 = base, no minimap,
        GL_RGB, // internalformat
        width, // width
        height, // height
        0, // border, always 0 in OpenGL ES
        GL_RGB, // format
        GL_UNSIGNED_BYTE, // type
        data // data
    );


}

struct Light {
    glm::vec3 position;
    glm::vec3 intensities; //a.k.a. the color of the light
    float coeficiente_ambiente;
};

GLfloat brilhosidade = 50.0;

Light gLight;

int tamanho;

int init_resources() {

        int i;
    for (i = 0; i < 256; i++) {
        keystates[i] = false;
    }


	glClearColor(0.4f, 0.4f, 0.4f, 0.4f);
	glEnable(GL_DEPTH_TEST);

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &textureID1);
    glBindTexture(GL_TEXTURE_2D, textureID1);
    loadTexture(woodBox.width, woodBox.height, woodBox.pixel_data);

    gLight.position = vec3(0.0f, 10.0f, -10.0f);
    gLight.intensities = vec3(1.0f, 1.0f, 1.0f);
    gLight.coeficiente_ambiente = 0.005f;


    programID = LoadShaders( "vertex-shader.txt", "fragment-shader.txt" );
    matrixID = glGetUniformLocation(programID, "MVP");
    modelID = glGetUniformLocation(programID, "model");

    glUseProgram(programID);


	glClearColor(0.4f, 0.4f, 0.4f, 0.4f);
	glEnable(GL_DEPTH_TEST);
    //setup vertexID
   	glGenBuffers(1, &vertexBuffer);
    glGenVertexArrays(1, &vertexArray);

    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    bool res = loadOBJ("crazyscene.obj", vertices, uvs, normals);

    printf("%d\t%d\t%d\n", vertices.size(), uvs.size(), normals.size());

    // Make a cube out of triangles (two triangles per side)
    tamanho = 3 * vertices.size() + 2 * uvs.size() + 3 * normals.size();
    GLfloat vertexData[tamanho];

    for (int i = 0; i < vertices.size(); i++) {

        vertexData[i*8] = vertices[i][0];
        vertexData[(i*8)+1] = vertices[i][1];
        vertexData[(i*8)+2] = vertices[i][2];

        vertexData[(i*8)+3] = uvs[i][0];
        vertexData[(i*8)+4] = uvs[i][1];

        vertexData[(i*8)+5] = normals[i][0];
        vertexData[(i*8)+6] = normals[i][1];
        vertexData[(i*8)+7] = normals[i][2];

        //printf("%d\t", i);

    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // connect the xyz to the "vert" attribute of the vertex shader
    glEnableVertexAttribArray(glGetAttribLocation(programID, "vert"));
    glVertexAttribPointer(glGetAttribLocation(programID, "vert"), 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (const GLvoid*)(0 * sizeof(GLfloat)));

    // connect the uv coords to the "vertTexCoord" attribute of the vertex shader
    glEnableVertexAttribArray(glGetAttribLocation(programID, "vertTexCoord"));
    glVertexAttribPointer(glGetAttribLocation(programID, "vertTexCoord"), 2, GL_FLOAT, GL_TRUE,  8*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

    // connect the normal to the "vertNormal" attribute of the vertex shader
    glEnableVertexAttribArray(glGetAttribLocation(programID, "vertNormal"));
    glVertexAttribPointer(glGetAttribLocation(programID, "vertNormal"), 3, GL_FLOAT, GL_TRUE,  8*sizeof(GLfloat), (const GLvoid*)(5 * sizeof(GLfloat)));

    // unbind the VAO
    glBindVertexArray(0);


    return programID;

}



float roty = 0;
void idle() {

    if (keystates['e'] == true)
        roty += 0.5f;
    if (keystates['q'] == true)
        roty -= 0.5f;

    if (keystates['w'] == true)
        gLight.position[1] += 0.25f;

    if (keystates['s'] == true)
        gLight.position[1] -= 0.25f;

    if (keystates['d'] == true)
        gLight.position[0] += 0.25f;


    if (keystates['a'] == true)
        gLight.position[0] -= 0.25f;

    if (keystates['z'] == true)
        gLight.position[2] += 0.25f;


    if (keystates['x'] == true)
        gLight.position[2] -= 0.25f;

    if (keystates['c'] == true)
        if (gLight.coeficiente_ambiente < 1.0f)
            gLight.coeficiente_ambiente = gLight.coeficiente_ambiente + 0.01f;

    if (keystates['v'] == true)
        if (gLight.coeficiente_ambiente > 0.0f)
            gLight.coeficiente_ambiente = gLight.coeficiente_ambiente - 0.01f;
        else if (gLight.coeficiente_ambiente < 0.0)
            gLight.coeficiente_ambiente = 0.0;

    if (keystates['n'] == true)
            brilhosidade = brilhosidade + 0.05;

    if (keystates['m'] == true)
        if (brilhosidade > 0.0)
            brilhosidade = brilhosidade - 0.05;
        else if (brilhosidade < 0.0)
            brilhosidade = 0.0;

    printf("BRILHOSIDADE: %f | AMBIENTE: %f\n", brilhosidade, gLight.coeficiente_ambiente);

}


void onDisplay() {


	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    glUseProgram(programID);

    glm::mat4 Projection = glm::perspective(60.0f, 16.0f / 9.0f, 0.1f, 100.0f);

    glm::mat4 View       = glm::lookAt(
								glm::vec3(10,10, 10),
								glm::vec3(0,1, 0),
								glm::vec3(0,1,0)
						   );

    glm::mat4 Model      = glm::mat4(1.0f);


    glm::mat4 rot = glm::rotate(mat4(1.0f), roty, vec3(0, 1, 0));
    glm::mat4 rot2 = glm::rotate(mat4(1.0f), 90.0f, vec3(1, 0, 0));
    Model *= rot ;

	glm::mat4 MVP        = Projection * View * Model ;


    /**************************************************************************************************************/
    //passa os parametros para a glsl

    glUniform1ui(glGetAttribLocation(programID, "tex"), 0);

    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(modelID, 1, GL_FALSE, &Model[0][0]);

    //iluminacao
    glUniform3fv(glGetUniformLocation(programID, "light_position"), 1, glm::value_ptr(gLight.position));
    glUniform3fv(glGetUniformLocation(programID, "light_intensities"), 1, glm::value_ptr(gLight.intensities));

    //envio do coeficiente ambiente
    glUniform1f(glGetUniformLocation(programID, "light_ambient_coefficient"),
                gLight.coeficiente_ambiente);
    //envio da cor especular: escolhi por enviar a cor BRANCA
    glUniform3fv(glGetUniformLocation(programID, "COR_ESPECULAR_MAT"),
                  1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
    // INTENSIDADE da iluminacao ESPECULAR
    glUniform1f(glGetUniformLocation(programID, "material_shininess"),
                brilhosidade);

    /**************************************************************************************************************/

    //bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID1);

    //bind VAO and draw
    glBindVertexArray(vertexArray);
    glDrawArrays(GL_TRIANGLES, 0, tamanho );


    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);


	glutSwapBuffers();
    glutPostRedisplay();

}


void keyboardDown(unsigned char key, int x, int y) {

    keystates[key] = true;

    if (keystates['r'] == true) {
        if (gLight.intensities[0] == 1.0f)
            gLight.intensities[0] = 0.0f;
        else
            gLight.intensities[0] = 1.0f;
    }

    if (keystates['g'] == true) {
        if (gLight.intensities[1] == 1.0f)
            gLight.intensities[1] = 0.0f;
        else
            gLight.intensities[1] = 1.0f;
    }

    if (keystates['b'] == true) {
        if (gLight.intensities[2] == 1.0f)
            gLight.intensities[2] = 0.0f;
        else
            gLight.intensities[2] = 1.0f;
    }

}

void keyboardUp(unsigned char key, int x, int y) {

    keystates[key] = false;

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
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("FPS Game");

    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
        return 1;
    }

    if (init_resources() != 0) {

        glutDisplayFunc(onDisplay);

        glutIdleFunc(idle);

        glutIgnoreKeyRepeat(1);
        glutKeyboardFunc(keyboardDown);
        glutKeyboardUpFunc(keyboardUp);

        glutMainLoop();
    }

    free_resources();
    return 0;
}
