#include "retangulo.h"

Retangulo::Retangulo()
{
   width = height = 0;
    for(int i = 0; i < 3; i++)
        vertices[i][Z_AXIS] = 0;
}

Retangulo::Retangulo(const Retangulo& rect): Forma(rect)
{
   this->width = rect.getWidth();
   this->height = rect.getHeight();
}

float Retangulo::getHeight() const
{
   return height;
}

void Retangulo::setHeight(float height)
{
    this->height = height;
}

float Retangulo::getWidth() const
{
   return width;
}

void Retangulo::setWidth(float width)
{
   this->width = width;
}

const float* Retangulo::getVertices(int n) const
{
    return vertices[n];
}

const float Retangulo::getVertices(int n, AXES a) const
{
    return vertices[n][a];
}

void Retangulo::translate(float dx, float dy)
{
    this->setXc(this->getXc() + dx);
    this->setYc(this->getYc() + dy);
    updateVertices();
}

void Retangulo::updateVertices()
{
    //counter clock-wise
    //Vertice one already in correct position

    vertices[0][X_AXIS] = this->getXc();
    vertices[0][Y_AXIS] = this->getYc();

    //Vertice two
    vertices[1][X_AXIS] = this->getXc();
    vertices[1][Y_AXIS] = this->getYc() - height;
    //Vertice three
    vertices[2][X_AXIS] = this->getXc() + width;
    vertices[2][Y_AXIS] = this->getYc() - height;
    //Vertice four
    vertices[3][X_AXIS] = this->getXc() + width;
    vertices[3][Y_AXIS] = this->getYc();
}

bool Retangulo::insideSquare(float x, float y) const
{
    if(x >= vertices[0][X_AXIS] && x <= vertices[3][X_AXIS] && y <= vertices[0][Y_AXIS] && y >= vertices[1][Y_AXIS])
        return true;
    else
        return false;
}

void Retangulo::draw()
{
    glColor3fv((GLfloat*)(this->getRGBColors()));
    glBegin(GL_POLYGON);
        for(int i = 0; i < 4; i++)
            glVertex3fv((GLfloat*)(this->getVertices(i)));
    glEnd();
}

Retangulo::~Retangulo(){}
