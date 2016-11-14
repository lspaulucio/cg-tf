#ifndef CAMERA_H
#define CAMERA_H

#include "funcoes.h"

typedef  enum _type_camera
{
	CAMERA_01,
	CAMERA_02,
	CAMERA_03
} TypeCamera ;

class Camera
{

	private:

		float angle;
		float srcX;
		float srcY;
		float srcZ;
		float dstX;
		float dstY;
		float dstZ;
		float aspect;
		TypeCamera type;

	public:

	    Camera();
	    //Camera(float srcX, float srcY, float srcZ, float dstX, float dstY, float dstZ);
	    //Camera(float srcX, float srcY, float srcZ, float dstX, float dstY, float dstZ, float angle);
	    //Camera(float srcX, float srcY, float srcZ, float dstX, float dstY, float dstZ, float angle, TypeCamera type);

	  	~Camera();

		void setAngle(float angle) { this->angle = angle; } 
		float getAngle() { return this->angle; }

		void setSrcX(float srcX) { this->srcX = srcX; } 
		float getSrcX() { return this->srcX; }

		void setSrcY(float srcY) { this->srcY = srcY; } 
		float getSrcY() { return this->srcY; }

		void setSrcZ(float srcZ) { this->srcZ = srcZ; } 
		float getSrcZ() { return this->srcZ; }

		void setDstX(float dstX) { this->dstX = dstX; } 
		float getDstX() { return this->dstX; }

		void setDstY(float dstY) { this->dstY = dstY; } 
		float getDstY() { return this->dstY; }

		void setDstZ(float dstZ) { this->dstZ = dstZ; } 
		float getDstZ() { return this->dstZ; }

		void setAspect(float aspect) { this->aspect = aspect; } 
		float getAspect() { return this->aspect; }

		void setType(TypeCamera type) { this->type = type; }
		TypeCamera getType() { return this->type; }

};


#endif //CARRO_H