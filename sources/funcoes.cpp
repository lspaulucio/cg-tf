#include "funcoes.h"

extern Janela MainWindow;
extern Circulo arena[2];
extern Retangulo rect;
extern list<Carro> enemies;
extern Carro player;
extern list<Tiro> playerShots, enemiesShots;
extern int key_status[256];
extern Camera camera;

int _w, _h;

//camera
double camXYAngle=0;
double camXZAngle=30;
int buttonDown=0;
float lastX, lastY;
int night_mode = 0;

void readXMLFile(const char *path)
{
    const char config_file_name[] = "config.xml";

    string svg_name, svg_type, svg_path, pathFile;
    XMLDocument config_file, svg_file;
    XMLError statusLoad;
    XMLElement *pElem;
    XMLNode *pRoot;

    if(!path) //Verify if the path was provided
    {
        cout << "Path to config file not provided, the program will be finished" << endl;
        exit(1);
    }

    pathFile = path;
    pathFile += config_file_name;
    //cout << pathFile << endl;

    //Opening file
    statusLoad = config_file.LoadFile(pathFile.c_str());

    if(statusLoad != XML_SUCCESS) //Test if file has been opened correctly
    {
        cerr << "Error opening configuration file\nProgram will be finished" << endl;
        exit(XML_ERROR_FILE_READ_ERROR);
    }

    pRoot = config_file.FirstChild(); //Get first element

    if(!pRoot)
    {
        cerr << "Error parsing element on configuration file\nProgram will be finished" << endl;
        exit(XML_ERROR_PARSING_ELEMENT);
    }
    //cout << pRoot->Value() << endl;

    //config.xml file

    //Arena info
    pElem = pRoot->FirstChildElement("arquivoDaArena");
    svg_name = pElem->FindAttribute("nome")->Value();
    svg_type = pElem->FindAttribute("tipo")->Value();
    svg_path = pElem->FindAttribute("caminho")->Value();
    //    cout << name << endl;
    //    cout << type << endl;
    //    cout << svg_path << endl;

    //Car info
    pElem = pRoot->FirstChildElement("carro");
    player.setShotSpeed(pElem->FindAttribute("velTiro")->FloatValue());
    player.setCarSpeed(pElem->FindAttribute("velCarro")->FloatValue());

    pElem = pRoot->FirstChildElement("carroInimigo");

    float enemyShotFrequence, enemyCarSpeed, enemyShotSpeed;
    enemyShotFrequence = pElem->FindAttribute("freqTiro")->FloatValue();
    enemyCarSpeed = pElem->FindAttribute("velCarro")->FloatValue();
    enemyShotSpeed = pElem->FindAttribute("velTiro")->FloatValue();

    //     cout << "shootFreq " << enemyShootFrequence << endl;
    //     cout << "velTiro " << enemyShootSpeed << endl;
    //     cout << "velCarro " << enemyCarVelocity << endl;

        //Path and name to svg file

        if(svg_path[0] == '~') //Testing if there is a tilde on beginning of path
        {
            pathFile = getenv("HOME");
            svg_path.erase(0,1);
            pathFile += svg_path;
            // cout << pathFile << endl;
        }
        else
        {
            pathFile = svg_path;
        }

        pathFile += svg_name += ".";
        pathFile += svg_type;

        // cout << pathFile << endl;

        //SVG file
        statusLoad = svg_file.LoadFile(pathFile.c_str());

        if(statusLoad != XML_SUCCESS) //Test if file has been opened correctly
        {
            cerr << "Error opening svg file\nProgram will be finished" << endl;
            exit(XML_ERROR_FILE_READ_ERROR);
        }

        pRoot = svg_file.FirstChild(); //Get first element

        if(!pRoot)
        {
            cerr << "Error parsing element on svg file\nProgram will be finished" << endl;
            exit(XML_ERROR_PARSING_ELEMENT);
        }
    //    cout << pRoot->Value() << endl;

    pElem = pRoot->FirstChildElement();
    // cout << pElem->Value() << endl;

    for(; pElem != NULL; pElem = pElem->NextSiblingElement())
    {
        string tipo = pElem->Value();

        if(!tipo.compare("circle")) //If is a circle
        {
            Circulo c;
            c.setXc(atof(pElem->FindAttribute("cx")->Value()));
            c.setYc(atof(pElem->FindAttribute("cy")->Value()));
            c.setRadius(atof(pElem->FindAttribute("r")->Value()));
            c.setId(pElem->FindAttribute("id")->Value());
            c.setRGBColors(pElem->FindAttribute("fill")->Value());

            // cout << pElem->FindAttribute("cx")->Value() << endl;
            // cout << pElem->FindAttribute("cy")->Value() << endl;
            // cout << pElem->FindAttribute("r")->Value() << endl;
            // cout << pElem->FindAttribute("id")->Value() << endl;
            // cout << pElem->FindAttribute("fill")->Value() << endl;

            //cout << "Circulo " << "cx: " << c.getXc() << " cy: " << c.getYc() << " r: " << c.getRadius() <<
            //" colors: " << c.getRGBColors(RED) << ", " << c.getRGBColors(GREEN) << ", " << c.getRGBColors(BLUE) << endl;
            if(!c.getId().compare("Jogador"))
            {
                player.copyInfo(c);
            }
            else if(!c.getId().compare("Pista"))
                {
                    if(arena[0].getRadius() > c.getRadius())
                        arena[1] = c;
                    else{
                            arena[1] = arena[0];
                            arena[0] = c;
                        }
                }
                else
                {
                    Carro e;
                    e.copyInfo(c);
                    e.setShootFrequence(enemyShotFrequence);
                    e.setCarSpeed(enemyCarSpeed);
                    e.setShotSpeed(enemyShotSpeed);
                    enemies.push_back(e);
                }
        }
        else if(!tipo.compare("rect")) //If is a rectangle
            {
                rect.setXc(atof(pElem->FindAttribute("x")->Value()));
                rect.setYc(atof(pElem->FindAttribute("y")->Value()));
                rect.setWidth(atof(pElem->FindAttribute("width")->Value()));
                rect.setHeight(atof(pElem->FindAttribute("height")->Value()));
                rect.setId(pElem->FindAttribute("id")->Value());
                rect.setRGBColors(pElem->FindAttribute("fill")->Value());

                // cout << pElem->FindAttribute("cx")->Value() << endl;
                // cout << pElem->FindAttribute("cy")->Value() << endl;
                // cout << pElem->FindAttribute("r")->Value() << endl;
                // cout << pElem->FindAttribute("id")->Value() << endl;
                // cout << pElem->FindAttribute("fill")->Value() << endl;

                // cout << "Retangulo " << "x: " << rect.getXc() << " y: " << rect.getYc() <<
                // " width: " << rect.getWidth() << " height: " << rect.getHeight() << " colors: " <<
                // rect.getRGBColors(RED) << ", " << rect.getRGBColors(GREEN) << ", " << rect.getRGBColors(BLUE) << endl;
            }
    } //End SVG file

    MainWindow.setHeight(2*arena[0].getRadius());
    MainWindow.setWidth(2*arena[0].getRadius());
    MainWindow.setTitle("Jogo Canhao");

    //Adjusting Y-Axis -> y = hy - y;  and Change center coordinate to (R,R)

    //Calculating distance to new center
    float dx = arena[0].getXc() - arena[0].getRadius(), dy = arena[0].getYc() - arena[0].getRadius();

    //Changing center to coordinate (Radius, Radius)
    for(int i = 0; i < 2; i++)
    {
        arena[i].setXc(arena[0].getRadius());
        arena[i].setYc(arena[0].getRadius());
    }

    rect.setYc(rect.getYc() - dy);
    rect.setXc(rect.getXc() - dx);
    rect.setYc(MainWindow.getHeight() - rect.getYc());
    rect.updateVertices();
    // cout << "x: " << rect.getXc() << "y: " << rect.getYc() << endl;

    for(list<Carro>::iterator it = enemies.begin(); it != enemies.end(); it++)
    {
        (*it).setXc((*it).getXc() - dx);
        (*it).setYc((*it).getYc() - dy);
        (*it).setYc(MainWindow.getHeight() - (*it).getYc());
    }

    player.setXc(player.getXc() - dx);
    player.setYc(player.getYc() - dy);
    player.setYc(MainWindow.getHeight() - player.getYc());

    // for(list<Carro>::iterator it = enemies.begin(); it != enemies.end(); it++)
    // cout << (*it).getId() << endl;

    return;
}

//OpenGL functions

void drawRectangle(float x1, float y1, float x2, float y2, const float colors[3], float alpha)
{

    float cor[4];

    float* _cor = (GLfloat*)(colors);

    cor[0] = _cor[0];
    cor[1] = _cor[1];
    cor[2] = _cor[2];
    cor[3] = alpha;

    glColor4fv(cor);

    glBegin(GL_POLYGON);
        glVertex3f(x1, y1, 0.0);
        glVertex3f(x1, y2, 0.0);
        glVertex3f(x2, y2, 0.0);
        glVertex3f(x2, y1, 0.0);
    glEnd();
}

void drawCube(float length, float width, float height, const float colors[3], float alpha)
{
    float l = length/2;
    float w = width/2;
    float h = height/2;

    glColor3fv(colors);

    glBegin(GL_TRIANGLE_FAN);
	// top
	// glColor3f(0.0f, 0.0f, 0.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-w, l, h);
	glVertex3f(w, l, h);
	glVertex3f(w, l, -h);
	glVertex3f(-w, l, -h);

	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	// front
	// glColor3f(0.0f, 0.0f, 1.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(w, -l, h);
	glVertex3f(w, l, h);
	glVertex3f(-w, l, h);
	glVertex3f(-w, -l, h);

	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	// right
	// glColor3f(0.0f, 1.0f, 0.0f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(w, l, -h);
	glVertex3f(w, l, h);
	glVertex3f(w, -l, h);
	glVertex3f(w, -l, -h);

	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	// left
	// glColor3f(0.0f, 1.0f, 1.0f);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-w, -l, h);
	glVertex3f(-w, l, h);
	glVertex3f(-w, l, -h);
	glVertex3f(-w, -l, -h);

	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	// bottom
	// glColor3f(1.0f, 0.0f, 0.0f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(w, -l, h);
	glVertex3f(-w, -l, h);
	glVertex3f(-w, -l, -h);
	glVertex3f(w, -l, -h);

	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	// back
	// glColor3f(1.0f, 0.0f, 1.0f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(w, l, -h);
	glVertex3f(w, -l, -h);
	glVertex3f(-w, -l, -h);
	glVertex3f(-w, l, -h);

	glEnd();
}

void drawCone(float radius, float height)
{
    GLUquadric *obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GL_TRIANGLE_FAN);
    gluQuadricNormals(obj, GL_SMOOTH);//GL_FLAT / GL_SMOOTH
    gluCylinder(obj, radius, 0, height, 100, 100);
    gluDeleteQuadric(obj);
}

void drawCylinder(float radius, float height)
{
    GLUquadric *obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GL_TRIANGLE_FAN);
    gluQuadricNormals(obj, GL_SMOOTH);//GL_FLAT / GL_SMOOTH
    gluCylinder(obj, radius, radius, height, 100, 100);
    gluDeleteQuadric(obj);
}

void drawSphere(float radius)
{
    GLUquadric *obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GL_TRIANGLE_FAN);
    gluQuadricNormals(obj, GL_SMOOTH);//GL_FLAT / GL_SMOOTH
    gluSphere(obj, radius, 100, 100);
    gluDeleteQuadric(obj);
}

void drawCircle(float xc, float yc, float radius, const float colors[3], int resolution, float alpha)
{
    float dx, dy;

    float cor[4];

    float* _cor = (GLfloat*)(colors);

    cor[0] = _cor[0];
    cor[1] = _cor[1];
    cor[2] = _cor[2];
    cor[3] = alpha;

    glColor4fv(cor);

    glBegin(GL_TRIANGLE_FAN);
		glVertex3f(xc, yc, 0);
		for(int i = 0; i <= resolution; i++)
        {
            dx = xc + (radius * cos(i * 2.0*M_PI / resolution));
            dy = yc + (radius * sin(i * 2.0*M_PI / resolution));
			glVertex3f(dx, dy, 0);
		}
    glEnd();
}

void drawEllipse(float xc, float yc, float width, float height, const float colors[3], int resolution, float alpha)
{
    float dx, dy;

    float cor[4];

    float* _cor = (GLfloat*)(colors);

    cor[0] = _cor[0];
    cor[1] = _cor[1];
    cor[2] = _cor[2];
    cor[3] = alpha;

    glColor4fv(cor);
    glBegin(GL_TRIANGLE_FAN);
		glVertex2f(xc, yc);
		for(int i = 0; i <= resolution; i++)
        {
            dx = xc + (width * cos(i * 2.0*M_PI / resolution));
            dy = yc + (height * sin(i * 2.0*M_PI / resolution));
			glVertex2f(dx, dy);
		}
    glEnd();
}

void drawWheel(float radius, float width)
{
    glPushMatrix();
        glRotatef(90, 1.0, 0.0, 0.0);
        glRotatef(-90, 0.0, 1.0, 0.0);
        drawCircle(0, 0, radius);
        drawCylinder(radius, width);
        glTranslatef(0.0,0.0,width);
            drawCircle(0, 0, radius);
    glPopMatrix();
}

void drawArenaOutside(float alpha)
{

    arena[0].draw(alpha);
    GLUquadric *obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GL_TRIANGLE_FAN);
    glColor4f(0, 0, 0, 0.5);
    glPushMatrix();
    glTranslatef(arena[0].getXc(), arena[0].getYc(),0);

    gluQuadricOrientation(obj, GLU_OUTSIDE);

    gluQuadricNormals(obj, GL_SMOOTH);
    // gluQuadricTexture(obj, textureSun);
    gluCylinder(obj, arena[0].getRadius(), arena[0].getRadius(), 100, 100, 5);
    gluDeleteQuadric(obj);
    glPopMatrix();
}

void drawArenaInside(float alpha)
{
    glPushMatrix();
        glTranslatef(0, 0, 0.1);
        arena[1].draw(alpha);
    glPopMatrix();   
        
    GLUquadric *obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GL_TRIANGLE_FAN);
    glColor4f(0, 0, 0, 0.5);
    glPushMatrix();
    glTranslatef(arena[1].getXc(), arena[1].getYc(),0);

    gluQuadricOrientation(obj, GLU_INSIDE);

    gluQuadricNormals(obj, GL_SMOOTH);
    // gluQuadricTexture(obj, textureSun);
    gluCylinder(obj, arena[1].getRadius(), arena[1].getRadius(), 100, 100, 5);
    gluDeleteQuadric(obj);
    glPopMatrix();
}

void init(void)
{
    /*Selecting background color*/
    //cout << " Janela "<< MainWindow.getBgColors(RED) << MainWindow.getBgColors(GREEN) << MainWindow.getBgColors(BLUE) << endl;
    glClearColor(MainWindow.getBgColors(RED),MainWindow.getBgColors(GREEN),MainWindow.getBgColors(BLUE), 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 2*arena[0].getRadius(), 0.0, 2*arena[0].getRadius(), -1.0, 1.0);

    //glClearColor( 0.0f, 0.1f, 0.0f, 0.5f );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glShadeModel(GL_FLAT);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    configObservator();
}

// Flags to check the result of the game
bool WIN_FLAG = false;
bool LOSE_FLAG = false;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    configHub();
    drawHub();

    configGame();
    DefineIluminacao();
    drawAll(1.0);

    configRetrovisor();
    drawAll();

    configMiniMapa();
    drawAll(0.2);

    glutSwapBuffers();
}

void drawHub()
{
    if(WIN_FLAG)
        printMessage(MainWindow.getWidth()/4, MainWindow.getHeight()/2, "Congratulations!!! You won the game");
    else if(LOSE_FLAG)
        printMessage(MainWindow.getWidth()/4, MainWindow.getHeight()/2, "Game Over!!!   An enemy hit you");
    else
        printClock(MainWindow.getWidth() - MainWindow.getWidth() / 4, MainWindow.getHeight() - 20);
}

void drawAll(float alpha)
{

    if(!WIN_FLAG && !LOSE_FLAG)
    {

        drawArenaOutside(alpha);

        drawArenaInside(alpha);

        glPushMatrix();
        glTranslatef(0, 0, 0.1);
            rect.draw(alpha);
        glPopMatrix();  
        

        for (list<Carro>::iterator it = enemies.begin(); it != enemies.end(); it++)
            (*it).draw('e', alpha);

        player.draw3d('p',alpha);

        for (list<Tiro>::iterator it = playerShots.begin(); it != playerShots.end(); it++)
            (*it).draw3d(alpha);

        for (list<Tiro>::iterator it = enemiesShots.begin(); it != enemiesShots.end(); it++)
            (*it).draw(alpha);
    }
}

bool START_FLAG = false; //Flag to indicate beginning the game
bool SHOT_FLAG = false;  //Flag to indicate the moment that the enemies will shoot

void idle(void)
{
    //Variables to check victory
    static float finish_line[2] = {player.getXc(), player.getYc() - 1};
    static float yp_old = player.getYc();
    static int win = 0;

    //Variables to control car's movements
    float tx, ty;
    const float WHEEL_ROTATION_STEP = 1;
    float wheelTheta = player.getWheelRotation();
    float move_vector[3] = {0}, *p = NULL;

    //Variables to get time
    static GLdouble previousTime = 0;
    GLdouble currentTime;
    GLdouble timeDiference;

    // Elapsed time from the initiation of the game.
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDiference = currentTime - previousTime; // Elapsed time from the previous frame.
    previousTime = currentTime; //Update previous time

    if(key_status['w'])
    {
        p = player.move(true, timeDiference);
        move_vector[X_AXIS] = p[X_AXIS];
        move_vector[Y_AXIS] = p[Y_AXIS];
        START_FLAG = true;
    }
    if(key_status['s'])
    {
        p = player.move(false, timeDiference);
        move_vector[X_AXIS] = p[X_AXIS];
        move_vector[Y_AXIS] = p[Y_AXIS];
        START_FLAG = true;
    }
    if(key_status['d'])
    {
        wheelTheta -= WHEEL_ROTATION_STEP;
        player.setWheelRotation(wheelTheta);
        START_FLAG = true;
    }
    if(key_status['a'])
    {
        wheelTheta += WHEEL_ROTATION_STEP;
        player.setWheelRotation(wheelTheta);
        START_FLAG = true;
    }

    if(START_FLAG) {
        updateClock(timeDiference);   //Update clock
        checkShotTime(timeDiference); //Check if is time to enemies shoot
        // Collision verification
        tx = player.getXc();
        ty = player.getYc();

        bool teste = true;

        // Test new position x
        player.setXc(tx + move_vector[X_AXIS]);

        for (list<Carro>::iterator it = enemies.begin(); it != enemies.end(); it++) {
            teste = teste && (*it).outsideCircle(player);
        }

        if (arena[0].insideCircle(player) && arena[1].outsideCircle(player) && teste);
        else {
            player.setXc(tx);
        }

        // Test new position y
        player.setYc(ty + move_vector[Y_AXIS]);

        for (list<Carro>::iterator it = enemies.begin(); it != enemies.end(); it++) {
            teste = teste && (*it).outsideCircle(player);
        }

        if (arena[0].insideCircle(player) && arena[1].outsideCircle(player) && teste);
        else {
            player.setYc(ty);
        }
        // End player collision verification

        ///////////////////////////////////////// ENEMY COLISION VERIFICATION //////////////////////////////////////////
        int i = 0;
        for(list<Carro>::iterator en = enemies.begin(); en != enemies.end(); en++)
        {
            float *p = en->randomMove(timeDiference, i++);
            float move_vector[3] = {0};
            move_vector[X_AXIS] = p[X_AXIS];
            move_vector[Y_AXIS] = p[Y_AXIS];

            //cout << "x " << move_vector[0] << " y " << move_vector[1] << endl;

            tx = en->getXc();
            ty = en->getYc();

            bool teste = true;

            // Test new position x
            en->setXc(tx + move_vector[X_AXIS]);

            for (list<Carro>::iterator it = enemies.begin(); it != enemies.end(); it++)
            {
                if(en != it)
                    teste = teste && (*en).outsideCircle(*it);
            }

            teste = teste && en->outsideCircle(player);

            if (arena[0].insideCircle(*en) && arena[1].outsideCircle(*en) && teste);
            else
            {
                en->setXc(tx);
            }

            // Test new position y
            en->setYc(ty + move_vector[Y_AXIS]);

            for (list<Carro>::iterator it = enemies.begin(); it != enemies.end(); it++)
            {
                if(en != it)
                    teste = teste && (*en).outsideCircle(*it);
            }

            teste = teste && en->outsideCircle(player);

            if (arena[0].insideCircle(*en) && arena[1].outsideCircle(*en) && teste);
            else
            {
                en->setYc(ty);
            }
        ////////////////////////////////  End enemy collision verification ///////////////////////////////////
        }

        ///////////////////////////////////////// ENEMIES SHOTS ////////////////////////////////////////

        if(SHOT_FLAG) {
            for (list<Carro>::iterator en = enemies.begin(); en != enemies.end(); en++) {
                Tiro t = en->shoot();
                enemiesShots.push_back(t);
            }
            SHOT_FLAG = false;
        }

        /////////////////////////////////// Shot moving /////////////////////////////////////////////////

        //Player shots
        for (list<Tiro>::iterator it = playerShots.begin(); it != playerShots.end(); it++)
        {
            (*it).move(timeDiference);


            if (!(*it).isInWindow(0.0, 0.0, 2 * arena[0].getRadius(), 2 * arena[0].getRadius()))
            {
                it = playerShots.erase(it);
                if (playerShots.empty()) {
                    break;
                }
            }

            //Checking hits
            for (list<Carro>::iterator en = enemies.begin(); en != enemies.end(); en++)
            {
                if (!en->outsideCircle(*it)) //If player hit an enemy exclude this enemy
                {
                    en = enemies.erase(en);
                    it = playerShots.erase(it);
                }
            }
        }

        //Enemy shots
        for (list<Tiro>::iterator it = enemiesShots.begin(); it != enemiesShots.end(); it++)
        {
            (*it).move(timeDiference);

            //Checking hit
            if (player.insideCircle((*it))) //If an enemy hits player show end game message
            {
                LOSE_FLAG = true;
                START_FLAG = false;
            }

            if (!(*it).isInWindow(0.0, 0.0, 2 * arena[0].getRadius(), 2 * arena[0].getRadius()))
            {
                it = enemiesShots.erase(it);
                if (enemiesShots.empty())
                    break;
            }
        }
        //cout << shoots.size() << endl;

        ////////////////////////////////// End shot moving //////////////////////////////////////////////

        ///////////////////////////////////////// Checking victory /////////////////////////////////////////

        if (player.getXc() > rect.getVertices(0, X_AXIS) && player.getXc() < rect.getVertices(3, X_AXIS))
        {
            if (player.getYc() > finish_line[Y_AXIS] && yp_old < finish_line[Y_AXIS])
            {
                win++;
            } else if (player.getYc() < finish_line[Y_AXIS] && yp_old > finish_line[Y_AXIS])
                    {
                        win--;
                    }
        }

        yp_old = player.getYc();
        //    cout << win << endl;
        if (win == 1)
        {
            WIN_FLAG = true;
            START_FLAG = false;
        }
        //            cout << "Win" << endl;
        // ///////////////////////////////////// End Check Victory ///////////////////////////////////////////

    }

    glutPostRedisplay();
}

void keyUp (unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
        case 'W':
            key_status['w'] = 0;
            player.setMoving(false);
          break;

        case 's':
        case 'S':
            key_status['s'] = 0;
            player.setMoving(false);
          break;

        case 'd':
        case 'D':
          key_status['d'] = 0;
          break;

        case 'a':
        case 'A':
          key_status['a'] = 0;
          break;

        default:
            break;
      }
}

void keypress (unsigned char key, int x, int y)
{
  switch (key)
  {
      case 'w':
      case 'W':
          key_status['w'] = 1;
          player.setMoving(true);
        break;

      case 's':
      case 'S':
          key_status['s'] = 1;
          player.setMoving(true);
        break;

      case 'd':
      case 'D':
        key_status['d'] = 1;
        break;

      case 'a':
      case 'A':
        key_status['a'] = 1;
        break;

      
      case 'n':
      case 'N':
        night_mode = !night_mode;
        break;  

       case 'e':
         exit(0);

      default:
          break;
  }

    configObservator();
    glutPostRedisplay();

}

void specialFunc(int key, int x, int y)
{

    switch (key)
    {
        case GLUT_KEY_F1:
            camera.setType(CAMERA_01);
            camera.setAngle(50);
            configGame();
        break;

        case GLUT_KEY_F2:
            camera.setType(CAMERA_02);
            camera.setAngle(50);
            configGame();
        break;

        case GLUT_KEY_F3:
            camera.setType(CAMERA_03);
            camera.setAngle(50);
            configGame();
        break;
    }

    configObservator();
    glutPostRedisplay();
}

void mouse(int key, int state, int x, int y)
{
    int hy = MainWindow.getHeight();

    y = hy - y; //Adjusting Y-Axis

    if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        int hx = MainWindow.getWidth();
        int theta = -120.0/hx*x + 60.0;
        int alphaZ = -90.0/hy*y + 22.5;

        player.setGunRotation(theta);
        player.setGunRotationZ(alphaZ);

        if(START_FLAG) {
            Tiro t = player.shoot();
            //cout << "ShotID " << t.getId() << endl;
            playerShots.push_back(t);
        }
    }

    if(key == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        lastX = x;
        lastY = y;
        buttonDown = 1;
    }

    if (key == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        buttonDown = 0;
    }
}

void passiveMouse(int x, int y)
{
    int hx = MainWindow.getWidth(), hy = MainWindow.getHeight();

    y = hy - y; //Adjusting Y-Axis

    int theta = -120.0/hx*x + 60.0;
    int alphaZ = -90.0/hy*y + 22.5;

    player.setGunRotation(theta);
    player.setGunRotationZ(alphaZ);

    // cout << player.getGunRotation() << endl;

}

void motionMouse(int x, int y)
{
    if (!buttonDown)
        return;

    float dx = x - lastX;
    float dy =  y - lastY;

    //TO-DO depois tem q resolver isso, do nada dando uns delta muito alto, abaixo solução temporaria

    const float MAIOR_DELTA = 4.0;

    if(dx > MAIOR_DELTA) dx = MAIOR_DELTA;
    else if(dx < -MAIOR_DELTA) dx = -MAIOR_DELTA;

    if(dy > MAIOR_DELTA) dy = MAIOR_DELTA;
    else if(dy < -MAIOR_DELTA) dy = -MAIOR_DELTA;

    camXYAngle += dx;
    camXZAngle += dy;

    camXYAngle = (int)camXYAngle % 360;
    camXZAngle = (int)camXZAngle % 360;


    if(camXZAngle < 0)
        camXZAngle = 0;
    else if(camXZAngle > 180)
        camXZAngle = 180;
    if(camXZAngle == 90)
        camXZAngle = 90.01;

    lastX = x;
    lastY = y;
}

//Clock variables
char str[100];
int seconds = 0;

void printClock(GLfloat x, GLfloat y) //Printing elapsed time
{
    glColor3f(0.0,0.0,0.0);
    //Create a string to be printed
    char *tmpStr;
    sprintf(str, "Lap Time: %d s", seconds);
    //Define the position to start printing
    glRasterPos2f(x, y);
    //Print  the first Char with a certain font
    //glutBitmapLength(font,(unsigned char*)str);
    tmpStr = str;
    //Print each of the other Char at time
    while( *tmpStr )
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *tmpStr);
        tmpStr++;
    }
}

void updateClock(double time) {

    const int SECOND = 1000;
    static float elapsedTime = 0;
    elapsedTime += time;
//    cout << elapsedTime << endl;

    if (START_FLAG)
    {
        if (elapsedTime >= SECOND)
        {
            seconds++;
            elapsedTime -= SECOND; //Update previous time
        }
    }
}

void checkShotTime(double time) {

    static float shotTimer = 0;
    const float shotPeriod = 1 / enemies.begin()->getShootFrequence();

    shotTimer += time;
    //cout << shotTime << endl;
    if (shotTimer >= shotPeriod) {
        shotTimer -= shotPeriod;
        SHOT_FLAG = true;
    }
}

void printMessage(int x, int y, const char* message)
{
    const char *tmpStr;
    glColor3f(0.0,0.0,0.0);
    //Define the position to start printing
    glRasterPos2f(x, y);
    //Print  the first Char with a certain font
    //glutBitmapLength(font,(unsigned char*)str);
    tmpStr = message;
    //Print each of the other Char at time
    while( *tmpStr )
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *tmpStr);
        tmpStr++;
    }
}

void DefineIluminacao (void)
{

    GLfloat luzAmbienteNight[4]={0.1,0.1,0.1,1.0};
    GLfloat luzAmbienteDay[4]={0.5,0.5,0.5,1.0};

    GLfloat luzDifusa[4]={0.2,0.2,0.2,1.0};    // "cor"
    GLfloat luzEspecular[4]={0.8, 0.8, 0.8, 1.0}; //"brilho"
    GLfloat posicaoLuz[4]={0.0, 0, 20.0, 0.0};

    // Capacidade de brilho do material
    //GLfloat especularidade[4]={0.2,0.2,0.2,1.0};
    //GLint especMaterial = 5;

    // Define a refletância do material
    //glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
    // Define a concentração do brilho
    //glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

    if(!night_mode)
    {

        /*float DISTANCE_FORWARD = 60;

        float dx = DISTANCE_FORWARD*cos(player.getCarRotation() * M_PI/180.0);
        float dy = DISTANCE_FORWARD*sin(player.getCarRotation() * M_PI/180.0);

        glEnable(GL_LIGHT1);

        GLfloat light1_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
        GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat light1_position[] = { player.getXc(), player.getYc(), 20, 1.0 };
        GLfloat spot_direction[] = { player.getXc() + dx, player.getYc()+dy, 0.0 };

        glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
        glLightfv(GL_LIGHT1, GL_POSITION, light1_position);*/

        //glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
        //glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
        //glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

        //glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
        //glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
        //glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

       

    }
    else
    {
        glDisable(GL_LIGHT1);
    }

    // Ativa o uso da luz ambiente
    if(night_mode)
    {
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbienteDay);
        glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbienteDay);
    }
    else
    {
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbienteNight);
        glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbienteNight);
    }

    // Define os parâmetros da luz de número 0
    //glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    // Habilita o modelo de colorização de Gouraud
    //glShadeModel(GL_SMOOTH);
}

void configObservator(void)
{
    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);

    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();

    if(camera.getType() == CAMERA_01)
    {

        float DISTANCE_BACKWARD = 100;


        float dx = DISTANCE_BACKWARD*cos( ( player.getCarRotation() + camXYAngle ) * M_PI/180.0);
        dx*= cos( camXZAngle * M_PI/180.0 );

        float dy = DISTANCE_BACKWARD*sin( ( player.getCarRotation() + camXYAngle ) * M_PI/180.0);
        dy*= cos( camXZAngle * M_PI/180.0 );

        float dz = DISTANCE_BACKWARD * sin( camXZAngle * M_PI/180.0 );

        //printf("ObsX: %f ObsY: %f ObsZ: %f\n", player.getXc() - dx, player.getYc() - dy, dz);
        //printf("X: %f Y: %f\n", player.getXc(), player.getYc() );
        //printf("CarRotation: %f\n", player.getCarRotation() );
        //printf("camXZAngle: %f\n", camXZAngle);
        //printf("camXYAngle: %f\n", camXYAngle);

        camera.setSrcX(player.getXc() - dx);
        camera.setSrcY(player.getYc() - dy);
        camera.setSrcZ(dz);

        camera.setDstX(player.getXc());
        camera.setDstY(player.getYc());
        camera.setDstZ(0);


        float z = camXZAngle < 90 ? 1 : -1;

        //camera atras do carro
        gluLookAt( camera.getSrcX(), camera.getSrcY(), camera.getSrcZ(),
                   camera.getDstX(), camera.getDstY(), camera.getDstZ(),
                   0 , 0, z );

    }
    else if(camera.getType() == CAMERA_02)
    {
        float DISTANCE_FORWARD = 60;

        float dx = DISTANCE_FORWARD*cos(player.getCarRotation() * M_PI/180.0);
        float dy = DISTANCE_FORWARD*sin(player.getCarRotation() * M_PI/180.0);

        camera.setSrcX(player.getXc() + dx*0.3);
        camera.setSrcY(player.getYc() + dy*0.3);
        camera.setSrcZ(20); //altura

        camera.setDstX(player.getXc()+dx);
        camera.setDstY(player.getYc()+dy);
        camera.setDstZ(0);

        //camera atras do carro
        gluLookAt( camera.getSrcX(), camera.getSrcY(), camera.getSrcZ(),
                   camera.getDstX(), camera.getDstY(), camera.getDstZ(),
                    0, 0, 1 );
    }
    else if(camera.getType() == CAMERA_03) //canhao
    {
        float DISTANCE_FORWARD = 80;

        float* gunTip = player.getGunTip();

        float dx = DISTANCE_FORWARD*cos( (player.getCarRotation() + player.getGunRotation()) * M_PI/180.0);
        float dy = DISTANCE_FORWARD*sin( (player.getCarRotation() + player.getGunRotation()) * M_PI/180.0);

        camera.setSrcX(gunTip[0]);
        camera.setSrcY(gunTip[1]);
        camera.setSrcZ(gunTip[2]);

        camera.setDstX(player.getXc()+dx);
        camera.setDstY(player.getYc()+dy);
        camera.setDstZ(0);

        //camera atras do carro
        gluLookAt( camera.getSrcX(), camera.getSrcY(), camera.getSrcZ(),
                   camera.getDstX(), camera.getDstY(), camera.getDstZ(),
                    0, 0, 1 );
    }
}

// Função usada para especificar o volume de visualização
void configGame(void)
{

    glLoadIdentity();

    glViewport(0, 0, _w, _h-200);

    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);

    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();

    // Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
    gluPerspective(camera.getAngle(),camera.getAspect(),5, 1000);

    configObservator();
}

void configRetrovisor()
{

    glLoadIdentity();

    glViewport(0, _h-200, _w, 200);
    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);

    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();

    gluPerspective(camera.getAngle(),camera.getAspect(),50,1000);

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);

    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();

    float DISTANCE_FORWARD = 60;

    float dx = DISTANCE_FORWARD*cos(player.getCarRotation() * M_PI/180.0);
    float dy = DISTANCE_FORWARD*sin(player.getCarRotation() * M_PI/180.0);

    camera.setSrcX(player.getXc());
    camera.setSrcY(player.getYc());
    camera.setSrcZ(20); //altura

    camera.setDstX(player.getXc()-dx);
    camera.setDstY(player.getYc()-dy);
    camera.setDstZ(0);

    //camera atras do carro
    gluLookAt( camera.getSrcX(), camera.getSrcY(), camera.getSrcZ(),
               camera.getDstX(), camera.getDstY(), camera.getDstZ(),
                0, 0, 1 );
}

void configMiniMapa()
{
    glLoadIdentity();

    glViewport(_w/2, 0, _w/2, _h/2);

    glMatrixMode(GL_PROJECTION);

    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();

    glOrtho(0, _w, 0, _h, -1.0, 1.0);
}

void configHub()
{
    glLoadIdentity();
    glViewport(0, 0, _w, _h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, _w, 0, _h, -1.0, 1.0);
}

// Função callback chamada quando o tamanho da janela é alterado
void reshape(GLsizei w, GLsizei h)
{
    // Para previnir uma divisão por zero
    if ( h == 0 ) h = 1;

    // Calcula a correção de aspecto
    camera.setAspect((GLfloat)w/(GLfloat)h);

    _w = w;
    _h = h;

}
