#include "janela.h"

Janela::Janela()
{
    width = height = 0;
    for(int i = 0; i < 3; i++)
        bgColors[i] = 1.0;
}

int Janela::getWidth() const
{
    return width;
}

void Janela::setWidth(int width)
{
    this->width = width;
}

int Janela::getHeight() const
{
    return height;
}

void Janela::setHeight(int height)
{
    this->height = height;
}

void Janela::setBgColors(const float colors[3])
{
    for(int i = 0; i < 3; i++)
        bgColors[i] = colors[i];
}

const float Janela::getBgColors(COLOR_ID id) const
{
    return bgColors[id];
}

const std::string &Janela::getTitle() const
{
    return title;
}

void Janela::setTitle(const std::string &title)
{
    this->title = title;
}

Janela::~Janela(){}
