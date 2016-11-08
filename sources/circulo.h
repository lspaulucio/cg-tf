#ifndef CIRCULO_H
#define CIRCULO_H

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "forma.h"
#include "types.h"

class Circulo: public Forma
{
    private:
        float radius;
        int drawResolution;

    public:

        Circulo();

        Circulo(const Circulo& circle);

        float getRadius() const;

        void setRadius(float radius);

        int getDrawResolution() const;

        void setDrawResolution(int resolution);

        void translate(float dx, float dy);

        bool insideCircle(float x, float y) const;

        bool insideCircle(Circulo& circle) const;

        bool outsideCircle(Circulo& circle) const;

        void draw();

        ~Circulo();

};



#endif //CIRCULO_H
