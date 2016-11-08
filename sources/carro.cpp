#include "carro.h"
#include <time.h>

Carro::Carro()
{
    this->moving = false;
    this->carSpeed = this->shotSpeed = 0;
    this->carRotation = 90;
    this->gunRotation = 0;
    this->wheelRotation = 0;
    this->setCarDirection(X_AXIS, 0);
    this->setCarDirection(Y_AXIS, 1);
    this->setCarDirection(Z_AXIS, 0);
    this->setWheelDirection(X_AXIS, 0);
    this->setWheelDirection(Y_AXIS, 1);
    this->setWheelDirection(Z_AXIS, 0);
    this->setGunDirection(X_AXIS, 0);
    this->setGunDirection(Y_AXIS, 1);
    this->setGunDirection(Z_AXIS, 0);
    this->randomWheel = this->randomGun = this->randomDirection = this->randomTime = 0;
}

void Carro::copyInfo(Circulo& circle)
{
    this->setXc(circle.getXc());
    this->setYc(circle.getYc());
    this->setRadius(circle.getRadius());
    this->setId(circle.getId());
    this->setRGBColors(circle.getRGBColors());
}

bool Carro::isMoving() const
{
    return moving;
}

void Carro::setMoving(bool moving)
{
    this->moving = moving;
}

void Carro::setShootFrequence(float freq)
{
    this->shootFrequence = freq;
}

float Carro::getShootFrequence()
{
    return this->shootFrequence;
}

float Carro::getCarSpeed() const
{
    return carSpeed;
}

void Carro::setCarSpeed(float carSpeed)
{
    this->carSpeed = carSpeed;
}

float Carro::getShotSpeed() const
{
    return shotSpeed;
}

void Carro::setShotSpeed(float shotSpeed)
{
    this->shotSpeed = shotSpeed;
}

const float *Carro::getCarDirection() const
{
    return carDirection;
}

void Carro::setCarDirection(AXES axis, float direction)
{
    this->carDirection[axis] = direction;
}

const float *Carro::getGunDirection() const
{
    return gunDirection;
}

void Carro::setGunDirection(AXES axis, float direction)
{
    this->gunDirection[axis] = direction;
}

const float *Carro::getWheelDirection() const
{
    return wheelDirection;
}

void Carro::setWheelDirection(AXES axis, float direction)
{
    this->wheelDirection[axis] = direction;
}

float Carro::getCarRotation() const
{
    return carRotation;
}

void Carro::setCarRotation(float rotation)
{
    if(rotation > 360)
        rotation -= 360;
    else if(rotation < 0)
        rotation += 360;

    this->carRotation = rotation;
    this->setCarDirection(X_AXIS, cos(rotation * M_PI/180.0));
    this->setCarDirection(Y_AXIS, sin(rotation * M_PI/180.0));
}

float Carro::getGunRotation() const
{
    return gunRotation;
}

void Carro::setGunRotation(float rotation)
{
    float const MAX_GUN_ROTATION = 45;

    if(rotation < -MAX_GUN_ROTATION)
        rotation = -MAX_GUN_ROTATION;
    else if(rotation > MAX_GUN_ROTATION)
            rotation = MAX_GUN_ROTATION;

    this->gunRotation = rotation;

    rotation += getCarRotation();

    this->setGunDirection(X_AXIS, cos(rotation * M_PI/180.0));
    this->setGunDirection(Y_AXIS, sin(rotation * M_PI/180.0));
//    cout << "Theta: " << rotation << endl;
//    cout << "Gun: x = " << getGunDirection()[X_AXIS] << " " << "y = " << getGunDirection()[Y_AXIS] << endl;
}

float Carro::getWheelRotation() const
{
    return wheelRotation;
}

void Carro::setWheelRotation(float rotation)
{
    // Wheel rotation verification
    float const MAX_WHEEL_ROTATION = 45;

    if(rotation < -MAX_WHEEL_ROTATION)
    {
        rotation = -MAX_WHEEL_ROTATION;
    }
    else if(rotation > MAX_WHEEL_ROTATION)
    {
        rotation = MAX_WHEEL_ROTATION;
    }

    this->wheelRotation = rotation;
    rotation += getCarRotation();
    //cout << "Rotation " << rotation << endl;

    this->setWheelDirection(X_AXIS, cos(rotation * M_PI/180.0));
    this->setWheelDirection(Y_AXIS, sin(rotation * M_PI/180.0));
    // cout << "Roda: x = " << getWheelDirection()[X_AXIS] << " " << "y = " << getWheelDirection()[Y_AXIS] << endl;
}

void Carro::draw(char type)
{
    //Car parameters
    float carWidth = 140;
    float carHeight = 300;
    float ellipseBigAxis = 80;
    float ellipseSmallAxis = 40;
    float gunWidth = 20;
    float gunHeight = 90;
    float wheelShaftLength = 30;
    float wheelShaftWidth = 70;
    float wheelLength = 125;
    float wheelWidth = 65;
    float wheelAxisDistance = 45;
    float exhaustWidth = 70;
    float exhaustHeight = 35;
    float exhaustFireHeight = carHeight/4;
    float CORRECTION_FACTOR = 5;
    float ROTATION_CORRECTION = -90.0; //Correction to make x axis to cos axis and y to sin axis
    static int animationAux = 0;
    float scale_factor = (this->getRadius()*2) / (carWidth + 2*wheelShaftWidth + 2*wheelLength);

    glPushMatrix();
        //car body
        glTranslatef(this->getXc(), this->getYc(), 0);
        glRotated(ROTATION_CORRECTION + this->getCarRotation(), 0.0, 0.0, 1.0);
        glScalef(scale_factor, scale_factor, 1);
            if(type == 'e')
            {
                drawRectangle(-carWidth / 2, carHeight / 2, carWidth / 2, -carHeight / 2, ENEMY_BODY_COLOR);
                drawEllipse(0.0, 0.0, ellipseSmallAxis, ellipseBigAxis, ENEMY_ELLIPSE_COLOR);
            }
            else
            {
                drawRectangle(-carWidth / 2, carHeight / 2, carWidth / 2, -carHeight / 2, BODY_COLOR);
                drawEllipse(0.0, 0.0, ellipseSmallAxis, ellipseBigAxis, ELLIPSE_COLOR);
            }
//            drawCircle(0.0, 0.0, this->getRadius()/scale_factor);

        glPushMatrix();
            //move to gun position (body upper)
            glTranslatef(0.0, carHeight/2 - CORRECTION_FACTOR, 0.0);
            glPushMatrix();
                //drawing gun
                glRotated(this->getGunRotation(), 0.0, 0.0, 1);

                if(type == 'e')
                    drawRectangle(-gunWidth/2, gunHeight, gunWidth/2, 0.0, ENEMY_GUN_COLOR);
                else
                    drawRectangle(-gunWidth/2, gunHeight, gunWidth/2, 0.0, GUN_COLOR);

            glPopMatrix();

            //drawing wheels and axis

            //////////////////////////////////// UPPER WHEELS /////////////////////////////////////////////////
            glPushMatrix();
                //drawing wheelshaft upper left
                glTranslatef(-carWidth/2 - wheelShaftWidth/2, -wheelAxisDistance - wheelShaftLength/2, 0);
                    drawRectangle(-wheelShaftWidth/2, wheelShaftLength/2, wheelShaftWidth/2, -wheelShaftLength/2, AXIS_COLOR);
                //drawing wheel upper left
                glTranslatef(-wheelShaftWidth/2 - wheelWidth/2 + CORRECTION_FACTOR, 0, 0);
                    glRotated(this->getWheelRotation(), 0.0, 0.0, 1);
                    drawRectangle(-wheelWidth/2, wheelLength/2, wheelWidth/2, -wheelLength/2, WHEEL_COLOR);
                    //Wheel move effect
                    if(isMoving())
                    {
                        if(animationAux / 5 == 0)
                        {
                            drawRectangle(-wheelWidth/2, wheelLength/4, wheelWidth/2, 0.0, DEFAULT_COLOR);
                            drawRectangle(-wheelWidth/2, -wheelLength/4, wheelWidth/2, -wheelLength/2, DEFAULT_COLOR);
                        }

                        else if(animationAux /10 == 0 ){
                            drawRectangle(-wheelWidth/2, 0.0, wheelWidth/2, -wheelLength/4, DEFAULT_COLOR);
                            drawRectangle(-wheelWidth/2, wheelLength/2, wheelWidth/2, wheelLength/4, DEFAULT_COLOR);
                        }
                    }
            glPopMatrix();

            glPushMatrix();
                //drawing wheelshaft upper right
                glTranslatef(carWidth/2 + wheelShaftWidth/2, -wheelAxisDistance - wheelShaftLength/2, 0);
                    drawRectangle(-wheelShaftWidth/2, wheelShaftLength/2, wheelShaftWidth/2, -wheelShaftLength/2, AXIS_COLOR);
                //drawing wheel upper right
                glTranslatef(wheelShaftWidth/2 + wheelWidth/2 - CORRECTION_FACTOR, 0, 0);
                    glRotated(this->getWheelRotation(), 0.0, 0.0, 1);
                    drawRectangle(-wheelWidth/2, wheelLength/2, wheelWidth/2, -wheelLength/2, WHEEL_COLOR);
                    //Wheel move effect
                    if(isMoving())
                    {
                        if(animationAux / 5 == 0)
                        {
                            drawRectangle(-wheelWidth/2, wheelLength/4, wheelWidth/2, 0.0, DEFAULT_COLOR);
                            drawRectangle(-wheelWidth/2, -wheelLength/4, wheelWidth/2, -wheelLength/2, DEFAULT_COLOR);
                        }

                        else if(animationAux /10 == 0 ){
                            drawRectangle(-wheelWidth/2, 0.0, wheelWidth/2, -wheelLength/4, DEFAULT_COLOR);
                            drawRectangle(-wheelWidth/2, wheelLength/2, wheelWidth/2, wheelLength/4, DEFAULT_COLOR);
                        }
                    }
            glPopMatrix();

            //////////////////////////////////// BOTTOM WHEELS /////////////////////////////////////////////////

            //moving to body bottom
            glTranslatef(0.0, -carHeight + CORRECTION_FACTOR, 0.0);

            //Drawing car exhaust
            glPushMatrix();
                drawRectangle(-exhaustWidth/2, 0.0, exhaustWidth/2, -exhaustHeight, GREY_COLOR);
                glTranslatef(0.0, -exhaustHeight, 0.0);

                if(isMoving()) //if car is moving draw fire
                {
                    if(animationAux % 4 == 0){
                        glPushMatrix();
                        glTranslatef(0.0, -carHeight/10, 0.0);
                        glColor3fv(YELLOW_COLOR);
                        glBegin(GL_POLYGON);
                        glVertex3f(-exhaustWidth / 2, 0.0, 0.0);
                        glVertex3f(-exhaustWidth / 3, -exhaustFireHeight / 2, 0.0);
                        glVertex3f(0, -exhaustFireHeight, 0.0);
                        glVertex3f(exhaustWidth / 3, -exhaustFireHeight / 2, 0.0);
                        glVertex3f(exhaustWidth / 2, 0.0, 0.0);
                        glEnd();

                        glColor3fv(RED_COLOR);
                        glBegin(GL_POLYGON);
                        glVertex3f(-exhaustWidth / 4, 0.0, 0.0);
                        glVertex3f(0, -exhaustFireHeight / 2, 0.0);
                        glVertex3f(exhaustWidth / 4, 0.0, 0.0);
                        glEnd();
                        glPopMatrix();
                    }
                    else {
                        glColor3fv(YELLOW_COLOR);
                        glBegin(GL_POLYGON);
                        glVertex3f(-exhaustWidth / 2, 0.0, 0.0);
                        glVertex3f(-exhaustWidth / 3, -exhaustFireHeight / 2, 0.0);
                        glVertex3f(0, -exhaustFireHeight, 0.0);
                        glVertex3f(exhaustWidth / 3, -exhaustFireHeight / 2, 0.0);
                        glVertex3f(exhaustWidth / 2, 0.0, 0.0);
                        glEnd();

                        glColor3fv(RED_COLOR);
                        glBegin(GL_POLYGON);
                        glVertex3f(-exhaustWidth / 4, 0.0, 0.0);
                        glVertex3f(0, -exhaustFireHeight / 2, 0.0);
                        glVertex3f(exhaustWidth / 4, 0.0, 0.0);
                        glEnd();
                    }
                    if(++animationAux > 10)
                        animationAux = 0;
                }

            glPopMatrix();

            glPushMatrix();
                //drawing wheelshaft bottom left
                glTranslatef(-carWidth/2 - wheelShaftWidth/2, wheelAxisDistance + wheelShaftLength/2, 0);
                    drawRectangle(-wheelShaftWidth/2, wheelShaftLength/2, wheelShaftWidth/2, -wheelShaftLength/2, AXIS_COLOR);
                //drawing wheel bottom left
                glTranslatef(-wheelShaftWidth/2 - wheelWidth/2, 0, 0);
                    drawRectangle(-wheelWidth/2, wheelLength/2, wheelWidth/2, -wheelLength/2, WHEEL_COLOR);
                    //Wheel move effect
                    if(isMoving())
                    {
                        if(animationAux / 5 == 0)
                        {
                            drawRectangle(-wheelWidth/2, wheelLength/4, wheelWidth/2, 0.0, DEFAULT_COLOR);
                            drawRectangle(-wheelWidth/2, -wheelLength/4, wheelWidth/2, -wheelLength/2, DEFAULT_COLOR);
                        }

                        else if(animationAux /10 == 0 ){
                            drawRectangle(-wheelWidth/2, 0.0, wheelWidth/2, -wheelLength/4, DEFAULT_COLOR);
                            drawRectangle(-wheelWidth/2, wheelLength/2, wheelWidth/2, wheelLength/4, DEFAULT_COLOR);
                        }
                    }
            glPopMatrix();

            glPushMatrix();
                //drawing wheelshaft bottom right
                glTranslatef(carWidth/2 + wheelShaftWidth/2, wheelAxisDistance + wheelShaftLength/2, 0);
                    drawRectangle(-wheelShaftWidth/2, wheelShaftLength/2, wheelShaftWidth/2, -wheelShaftLength/2, AXIS_COLOR);
                //drawing wheel bottom right
                glTranslatef(wheelShaftWidth/2 + wheelWidth/2, 0, 0);
                    drawRectangle(-wheelWidth/2, wheelLength/2, wheelWidth/2, -wheelLength/2, WHEEL_COLOR);
                    //Wheel move effect
                    if(isMoving())
                    {
                        if(animationAux / 5 == 0)
                        {
                            drawRectangle(-wheelWidth/2, wheelLength/4, wheelWidth/2, 0.0, DEFAULT_COLOR);
                            drawRectangle(-wheelWidth/2, -wheelLength/4, wheelWidth/2, -wheelLength/2, DEFAULT_COLOR);
                        }

                        else if(animationAux /10 == 0 ){
                            drawRectangle(-wheelWidth/2, 0.0, wheelWidth/2, -wheelLength/4, DEFAULT_COLOR);
                            drawRectangle(-wheelWidth/2, wheelLength/2, wheelWidth/2, wheelLength/4, DEFAULT_COLOR);
                        }
                    }
            glPopMatrix();

        glPopMatrix();//Back to central position of car

    glPopMatrix();

}// End draw

float* Carro::move(bool direction, double time)
{
    static float position[3];
    float CAR_ROTATION_STEP = 2;
    float carRotation = this->getCarRotation();
    float theta = this->getCarDirection()[X_AXIS] * this->getWheelDirection()[X_AXIS] + this->getCarDirection()[Y_AXIS] * this->getWheelDirection()[Y_AXIS];

    theta = acos(theta);
    CAR_ROTATION_STEP *= tan(theta); //Adjusting curve sensitivity

    theta *= 180/M_PI;

    if(this->getCarRotation() + this->getWheelRotation() < this->getCarRotation())
        theta *= -1;

    if(direction)
    {
        if(theta > 0) //wheel curved to left
        {
            carRotation += CAR_ROTATION_STEP;
            this->setCarRotation(carRotation);
            this->setWheelRotation(this->getWheelRotation());
            // this->setWheelRotation(this->getWheelRotation() - CAR_ROTATION_STEP);
        }
        else if (theta < 0) //Wheel curved to right
            {
                carRotation -= CAR_ROTATION_STEP;
                this->setCarRotation(carRotation);
                this->setWheelRotation(this->getWheelRotation());
                // this->setWheelRotation(this->getWheelRotation() + CAR_ROTATION_STEP);
            }

        position[X_AXIS] = (this->getCarSpeed() * time * cos(this->getCarRotation() * M_PI / 180.0));
        position[Y_AXIS] = (this->getCarSpeed() * time * sin(this->getCarRotation() * M_PI / 180.0));
        position[Z_AXIS] = 0;
    }
    else
    {
        if(theta > 0) //wheel curved to left
        {
            carRotation -= CAR_ROTATION_STEP;
            this->setCarRotation(carRotation);
            this->setWheelRotation(this->getWheelRotation());
            // this->setWheelRotation(this->getWheelRotation() - CAR_ROTATION_STEP);
        }
        else if (theta < 0) //Wheel curved to right
        {
            carRotation += CAR_ROTATION_STEP;
            this->setCarRotation(carRotation);
            this->setWheelRotation(this->getWheelRotation());
            // this->setWheelRotation(this->getWheelRotation() + CAR_ROTATION_STEP);
        }

        position[X_AXIS] = -(this->getCarSpeed() * time * cos(this->getCarRotation() * M_PI / 180.0));
        position[Y_AXIS] = -(this->getCarSpeed() * time * sin(this->getCarRotation() * M_PI / 180.0));
        position[Z_AXIS] = 0;
    }

    return position;
}

float* Carro::randomMove(double timeDif, int id)
{
    const int TIME = 1500;

    randomTime += timeDif;

    if(randomTime >= TIME) {
        this->randomWheel = rand() % 2;
        this->randomGun = rand() % 2;
        this->randomDirection = rand() % 2;
        randomTime -= TIME;
//        cout << id << " " << randomDirection << endl;
    }

    if(randomWheel < 1)
    {
        setWheelRotation(getWheelRotation() + 2);
    }
    else
    {
        setWheelRotation(getWheelRotation() - 2);
    }

    if(randomGun < 1)
    {
        setGunRotation(getGunRotation() + 2);
    }
    else
    {
        setGunRotation(getGunRotation() - 2);
    }

    return move(randomDirection, timeDif);
}

Tiro Carro::shoot()
{
    float carHeight = 300;
    float gunHeight = 90;
    float carWidth = 140;
    float wheelShaftWidth = 70;
    float wheelLength = 125;
    float scale_factor = (this->getRadius()*2) / (carWidth + 2*wheelShaftWidth + 2*wheelLength);

    carHeight *= scale_factor;
    gunHeight *= scale_factor;

    float shootRotation = getCarRotation() + getGunRotation();


    Tiro shot;

    //Add radius to adjust shot to appear upper the gun
    float xc = getXc() + (carHeight/2 * cos(this->getCarRotation() * M_PI / 180.0) + (gunHeight + shot.getRadius()) * cos(shootRotation * M_PI / 180.0));
    float yc = getYc() + (carHeight/2 * sin(this->getCarRotation() * M_PI / 180.0) + (gunHeight + shot.getRadius()) * sin(shootRotation * M_PI / 180.0));

//    cout <<  "p " << cos(this->getCarRotation() << " " << getYc() << endl;

//    cout << "p " << getXc() << " " << getYc() << endl;
//    cout << "t " << xc << " " << yc<< endl;
    shot.setXc(xc);
    shot.setYc(yc);
    shot.setId(this->getId());
    shot.setShootSpeed(this->getShotSpeed());
    shot.setShootRotation(getCarRotation()+getGunRotation());
    shot.setShootDirection(X_AXIS, this->getGunDirection()[X_AXIS]);
    shot.setShootDirection(Y_AXIS, this->getGunDirection()[Y_AXIS]);

    return shot;
}

Carro::~Carro(){};
