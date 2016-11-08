#ifndef FORMA_H
#define FORMA_H

#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include "types.h"

class Forma
{
    private:
        float RGBColors[3];
        float xc, yc;
        std::string id;

    public:

        Forma();

        Forma(const Forma& f);

        const float* getRGBColors() const;

        const float getRGBColors(COLOR_ID id) const;

        int colorVerification(std::string color);

        void setRGBColors(const float colors[3]);

        void setRGBColors(std::string color_name);

        float getXc() const;

        void setXc(float xc);

        float getYc() const;

        void setYc(float yc);

        const std::string &getId() const;

        void setId(const std::string &id);

        virtual void translate(float dx, float dy)=0;

        virtual void draw()=0;

        ~Forma();

};



#endif //FORMA_H
