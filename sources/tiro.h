#ifndef TIRO_H
#define TIRO_H

#include "circulo.h"

const float DEFAULT_SHOOT_LENGHT = 5;
const float SHOOT_COLOR[3] = {0.32, 0.32, 0.32};

class Tiro : public Circulo
{

private:
    float shotSpeed;
    float shotDirection[3];
    float shotRotation;

public:

    Tiro();

    Tiro(const Tiro& s);

    float getShootSpeed() const;

    void setShootSpeed(float shotSpeed);

    const float *getShootDirection() const;

    void setShootDirection(AXES axis, float direction);

    float getShootRotation() const;

    void setShootRotation(float shootRotation);

    void draw();

    void move(double time);

    bool isInWindow(float x0, float y0, float x1, float y1);

    ~Tiro();

};

#endif //TIRO_H
