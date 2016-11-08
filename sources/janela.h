#ifndef JANELA_H
#define JANELA_H

#include <iostream>
#include "types.h"

class Janela
{

    private:
        int width, height;
        float bgColors[3];
        std::string title;

    public:

        Janela();

        int getWidth() const;

        void setWidth(int width);

        int getHeight() const;

        void setHeight(int height);

        const float getBgColors(COLOR_ID) const;

        void setBgColors(const float colors[3]);

        const std::string &getTitle() const;

        void setTitle(const std::string &title);

        ~Janela();

};


#endif //JANELA_H
