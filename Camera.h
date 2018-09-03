#include <glm/glm.hpp>


#ifndef __CAMERA_H__
#define __CAMERA_H__ 



class Light
{
private:
	glm::vec3 Pos;
	glm::vec4 Color;
	bool LightSwitch;
	glm::vec4 onColor;
	glm::vec4 offColor;
public:
	Light( glm::vec3 p, glm::vec4 c ) : Pos( p ), Color( c ) { onColor = c; offColor = glm::vec4( 0.0, 0.0, 0.0, 1.0); \
		LightSwitch = true; }
	glm::vec3 &getPos() { return Pos; }
	glm::vec4 &getColor() { return Color;}
	bool &getLightSwitch(){ return LightSwitch; }
	glm::vec4 getOffColor() const {return offColor; }
	glm::vec4 getOnColor() const {return onColor; }

	//Use Template Later;
	void setPos( glm::vec3 p ) { Pos = p; }
	

};

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


  	Light *KeyLight;

  	Light *FillLight;
  	Light *BackLight;

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
	void handleMouseRoll( double y );
	void handleKeyBoard( int key, int action );


	glm::vec3 getLightPos( char light );
	glm::vec4 &getLightColor( char light );

};


#endif