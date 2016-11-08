#ifndef CARRO_H
#define CARRO_H

#include "funcoes.h"
#include "circulo.h"
#include "retangulo.h"
#include "tiro.h"

class Carro : public Circulo
{

private:

    bool moving;
    float carSpeed, shotSpeed;
    float shootFrequence;
    float carDirection[3], gunDirection[3], wheelDirection[3];
    float carRotation, gunRotation, wheelRotation;
    int randomWheel, randomGun, randomDirection, randomTime;

public:
    Carro();

    void copyInfo(Circulo& circle);

    bool isMoving() const;

    void setMoving(bool moving);

    float getShootFrequence();

    void setShootFrequence(float freq);

    float getCarSpeed() const;

    void setCarSpeed(float carSpeed);

    float getShotSpeed() const;

    void setShotSpeed(float shotSpeed);

    const float *getCarDirection() const;

    void setCarDirection(AXES axis, float direction);

    const float *getGunDirection() const;

    void setGunDirection(AXES axis, float direction);

    const float *getWheelDirection() const;

    void setWheelDirection(AXES axis, float direction);

    float getCarRotation() const;

    void setCarRotation(float rotCar);

    float getGunRotation() const;

    void setGunRotation(float rotation);

    float getWheelRotation() const;

    void setWheelRotation(float rotation);

    void draw(char type = 'p');

    float* move(bool direction, double time);

    float* randomMove(double time, int id);

    Tiro shoot();

    ~Carro();

};

const float AXIS_COLOR[3] = {0.32, 0.5, 0.74};
const float WHEEL_COLOR[3] = {0.68, 0.68, 0.68};
const float ELLIPSE_COLOR[3] = {0.0, 0.7, 0.32};
const float BODY_COLOR[3] = {0.6, 0.74, 0.35};
const float GUN_COLOR[3] = {0.4, 0.67, 0.46};
const float ENEMY_BODY_COLOR[3] = {0.78, 0.0, 0.0};
const float ENEMY_ELLIPSE_COLOR[3] = {1.0, 0.4, 0.0};
const float ENEMY_GUN_COLOR[3] = {0.0, 1.0, 0.0};

#endif //CARRO_H
