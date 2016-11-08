#ifndef RETANGULO_H
#define RETANGULO_H

#include "forma.h"
#include <iostream>

class Retangulo: public Forma
{
private:
    float width, height;
    float vertices[4][3];

public:

    Retangulo();

    Retangulo(const Retangulo &rect);

    float getWidth() const;

    void setWidth(float width);

    float getHeight() const;

    void setHeight(float height);

    const float* getVertices(int n) const;

    const float getVertices(int, AXES) const;

    void translate(float dx, float dy);

    void updateVertices();

    bool insideSquare(float x, float y) const;

    void draw();

    ~Retangulo();

};


#endif //RETANGULO_H
