#include <glm/glm.hpp>


#ifndef __CAMERA_H__
#define __CAMERA_H__ 

class Camera
{
private:
	glm::vec3 InitUp;
	glm::vec3 InitForward;
	glm::vec3 InitRight;
	glm::vec3 InitPos;

	glm::vec3 Pos;
  	glm::vec3 Up;
  	glm::vec3 Forward;
  	glm::vec3 Right;


  	double oldX;
  	double oldY;

  	bool rotateOn;

  	const float fovy;
  	const float znear;
  	const float zfar;

public:
	Camera();
	glm::vec3 getPos() const { return Pos;}
	glm::vec3 getForw() const { return Forward;}
	glm::vec3 getUp() const { return Up;}
	float getFovy() const{ return fovy;}
	float getZnear() const { return znear;}
	float getZfar() const { return zfar;}
	void handleMouseButtons(int button, int action, double x, double y);
	void handleMouseMove( double x, double y );


};


#endif