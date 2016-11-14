#ifndef FUNCOES_H
#define FUNCOES_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <math.h>
#include "types.h"
#include "../tinyxml2/tinyxml2.h"
#include "forma.h"
#include "janela.h"
#include "circulo.h"
#include "retangulo.h"
#include "carro.h"
#include "camera.h"

using namespace std;
using namespace tinyxml2;

void readXMLFile(const char *path);

//OpenGL functions
void init(void);
void display(void);
void idle(void);
void mouse(int key, int state, int x, int y);
void keypress (unsigned char key, int x, int y);
void keyUp (unsigned char key, int x, int y);
void passiveMouse(int x, int y);
void printClock(GLfloat x, GLfloat y);
void updateClock(double time);
void checkShotTime(double time);
void printMessage(int x, int y, const char* message);

//Drawing functions
void drawRectangle(float x1, float y1, float x2, float y2, const float colors[3] = DEFAULT_COLOR, float alpha = 1);
void drawCircle(float xc, float yc, float radius, const float colors[3] = DEFAULT_COLOR, int resolution = 100, float alpha = 1);
void drawEllipse(float xc, float yc, float width, float height, const float colors[3] = DEFAULT_COLOR, int resolution = 100, float alpha = 1);

//Câmera
void configObservator(void);
void configGame(void);
void configRetrovisor(void);
void reshape(GLsizei w, GLsizei h);
void specialFunc(int key, int x, int y);
void drawAll(float alpha = 1);
void drawHub(void);
void configHub();
void configMiniMapa(void);
void motionMouse(int x, int y);

#endif //FUNCOES_H
