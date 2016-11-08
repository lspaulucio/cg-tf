#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include <iostream>
#include <vector>
#include "tinyxml2/tinyxml2.h"
#include "sources/forma.h"
#include "sources/funcoes.h"
#include "sources/janela.h"
#include "sources/retangulo.h"
#include "sources/circulo.h"
#include "sources/carro.h"

using namespace tinyxml2;
using namespace std;

//Global variables
Janela MainWindow;
list<Carro> enemies;
Circulo arena[2];
Retangulo rect;
Carro player;
list<Tiro> playerShots, enemiesShots;

int key_status[256] = {0};

int main(int argc, char** argv)
{
    readXMLFile(argv[1]);
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(MainWindow.getWidth(),MainWindow.getHeight());
    glutInitWindowPosition(500,500);
    glutCreateWindow(MainWindow.getTitle().c_str());
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(passiveMouse);
    glutKeyboardFunc(keypress);
    glutKeyboardUpFunc(keyUp);
    glutIdleFunc(idle);
    glutMainLoop();


    return EXIT_SUCCESS;
}
