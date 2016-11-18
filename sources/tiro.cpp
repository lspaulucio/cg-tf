#include "tiro.h"

Tiro::Tiro()
{
    shotSpeed = shotRotation = 0;
    shotDirection[X_AXIS] = shotDirection[Y_AXIS] = shotDirection[Z_AXIS] = 0;
    this->setRadius(DEFAULT_SHOOT_LENGHT);
}

Tiro::Tiro(const Tiro &s) : Circulo(s)
{
    this->shotSpeed = s.shotSpeed;
    this->shotDirection[X_AXIS] = s.shotDirection[X_AXIS];
    this->shotDirection[Y_AXIS] = s.shotDirection[Y_AXIS];
    this->shotRotation = s.shotRotation;
}

float Tiro::getShootSpeed() const
{
    return shotSpeed;
}

void Tiro::setShootSpeed(float shotSpeed)
{
    Tiro::shotSpeed = shotSpeed;
}

const float *Tiro::getShootDirection() const
{
    return shotDirection;
}

void Tiro::setShootDirection(AXES axis, float direction)
{
    this->shotDirection[axis] = direction;
}

float Tiro::getShootRotation() const
{
    return shotRotation;
}

void Tiro::setShootRotation(float shotRotation)
{
    Tiro::shotRotation = shotRotation;
}

void Tiro::draw(float alpha)
{
    float dx, dy;

    float cor[4];
    float* _cor = (GLfloat*)RED_COLOR;

    cor[0] = _cor[0];
    cor[1] = _cor[1];
    cor[2] = _cor[2];
    cor[3] = alpha;

    glColor4fv(cor);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(getXc(), getYc());
		for(int i = 0; i <= getDrawResolution(); i++)
        {
            dx = getXc() + (getRadius() * cos(i * 2.0*M_PI / getDrawResolution()));
            dy = getYc() + (getRadius() * sin(i * 2.0*M_PI / getDrawResolution()));
            glVertex2f(dx, dy);
        }
    glEnd();


    _cor = (GLfloat*)YELLOW_COLOR;

    cor[0] = _cor[0];
    cor[1] = _cor[1];
    cor[2] = _cor[2];
    cor[3] = alpha;

    glColor4fv(cor);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(getXc(), getYc());
    for(int i = 0; i <= getDrawResolution(); i++)
    {
        dx = getXc() + (getRadius()/2 * cos(i * 2.0*M_PI / getDrawResolution()));
        dy = getYc() + (getRadius()/2 * sin(i * 2.0*M_PI / getDrawResolution()));
        glVertex2f(dx, dy);
    }
    glEnd();
}

void Tiro::draw3d(float alpha)
{
    GLUquadric *obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GL_TRIANGLE_FAN);
    gluQuadricNormals(obj, GL_SMOOTH);//GL_FLAT / GL_SMOOTH
    gluSphere(obj, getRadius(), 100, 100);
    gluDeleteQuadric(obj);
}



void Tiro::move(double time)
{
    setXc(getXc() + (this->getShootSpeed() * time * getShootDirection()[X_AXIS]));
    setYc(getYc() + (this->getShootSpeed() * time * getShootDirection()[Y_AXIS]));
}

bool Tiro::isInWindow(float x0, float y0, float x1, float y1)
{
    return x0 < this->getXc() && this->getXc() < x1 && y0 < this->getYc() && this->getYc() < y1;
}

Tiro::~Tiro(){}
