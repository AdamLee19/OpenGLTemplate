
#include "Camera.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>


#define INITUP glm::vec3(0.0f, 1.0f, 0.0f)
#define INITFORWARD glm::vec3(0.0f, 0.0f, -1.0f)
#define INITRIGHT glm::vec3(1.0f, 0.0f, 0.0f)
#define INITPOS glm::vec3(0.0f, 0.0f, 5.0f)
#define FOVY 70.
#define ZNEAR 0.01
#define ZFAR 1000.



Camera :: Camera() : InitUp( INITUP ), InitForward( INITFORWARD ),
InitRight( INITRIGHT ), InitPos( INITPOS ), rotateOn(false), fovy( FOVY ), znear ( ZNEAR ), zfar( ZFAR )
{
	Pos = InitPos;
	Forward = InitForward;
	Up = InitUp;
	Right = InitRight;
	oldX = 0;
	oldY = 0;

}

void Camera :: handleMouseButtons( int button, int action, double x, double y )
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
	
		oldX = x;
		oldY = y;
		rotateOn = true;
	}
	else if ( button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE )
		rotateOn = false;
	

}

void Camera :: handleMouseMove( double x, double y )
{
	float sensityvity = 0.5f;
	if( rotateOn )
	{
		float dx = float(x - oldX);
	 	float dy = float(y - oldY);
	 	oldX = x;
	 	oldY = y;

		if( glm::abs( dx ) > ( glm::abs( dy ) ) )
		{
			Pos =  glm::rotate(Pos, glm::radians(-dx*sensityvity), Up);
			Forward =  glm::rotate(Forward, glm::radians(-dx*sensityvity), Up);
			Right =  glm::rotate(Right, glm::radians(-dx*sensityvity), Up);
			
		}
		else
		{
			Pos =  glm::rotate(Pos, glm::radians(-dy*sensityvity), Right);
			Forward = glm::rotate(Forward, glm::radians(-dy*sensityvity), Right);
			Up =  glm::rotate(Up, glm::radians(-dy*sensityvity), Right);

		}
	}
}



