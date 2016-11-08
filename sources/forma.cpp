#include "forma.h"

Forma::Forma()
{
    xc = yc = 0;
}

Forma::Forma(const Forma &f)
{
    this->xc = f.xc;
    this->yc = f.yc;
    this->setRGBColors(f.getRGBColors());
    this->id = f.id;
}

const float* Forma::getRGBColors() const
{
    return RGBColors;
}

const float Forma::getRGBColors(COLOR_ID id) const
{
    return RGBColors[id];
}

int Forma::colorVerification(std::string color) //Check the color's name
{
    if(!color.compare("white")) //If color is white
        return WHITE;
    if(!color.compare("black")) //If color is black
        return BLACK;
    if(!color.compare("red")) //If color is red
        return RED;
    if(!color.compare("green")) //If color is green
        return GREEN;
    if(!color.compare("blue")) //If color is blue
        return BLUE;

    return -1;
}

void Forma::setRGBColors(std::string color_name)
{
    float colors[3] = {0.0};

    switch(this->colorVerification(color_name)) //Choose RGB values for each color's type
    {
        case BLACK:
            this->setRGBColors(colors);
            break;
        case WHITE:
            colors[RED]= colors[GREEN] = colors[BLUE] = 1.0;
            this->setRGBColors(colors);
            break;
        case RED:
            colors[RED] = 1.0;
            this->setRGBColors(colors);
            break;
        case GREEN:
            colors[GREEN] = 1.0;
            this->setRGBColors(colors);
            break;
        case BLUE:
            colors[BLUE] = 1.0;
            this->setRGBColors(colors);
            break;
        default:
            std::cout << "Unknown color" << std::endl;
            return;
    }
}

void Forma::setRGBColors(const float colors[3])
{
    for(int i = 0; i < 3; i++)
    this->RGBColors[i] = colors[i];
}

float Forma::getXc() const
{
    return xc;
}

void Forma::setXc(float xc)
{
    this->xc = xc;
}

float Forma::getYc() const
{
    return yc;
}

void Forma::setYc(float yc)
{
    this->yc = yc;
}

const std::string &Forma::getId() const
{
    return id;
}

void Forma::setId(const std::string &id)
{
    this->id = id;
};

Forma::~Forma(){};
