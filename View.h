#include "Camera.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

#ifndef __VIEW_H__
#define __VIEW_H__

#define WINDOW_W 1000
#define WINDOW_H 800
#define FOV   70.0

class View
{
private:
	int CurrentWindow_W;
	int CurrentWindow_H;
	int InitWindow_W;
	int InitWindow_H;

	

	Camera *camera;

	float *backgroundcolor;

	glm::mat4 proj;
	glm::mat4 view;
	glm::mat4 model;
	
public:
	View();
	int getWidth() const {return CurrentWindow_W;}
    int getHeight() const {return CurrentWindow_H;}
    void reshapeWindow( int w, int h );
 
	void initList();
	void display();
	void handleMouseButtons(int button, int action, double x, double y);
	void handleMouseMove( double x, double y );
	
};

#endif