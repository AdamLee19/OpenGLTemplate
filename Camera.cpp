#include "Camera.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>



#define INITUP glm::vec3(0.0f, 1.0f, 0.0f)
#define INITFORWARD glm::vec3(0.0f, 0.0f, -1.0f)
#define INITRIGHT glm::vec3(1.0f, 0.0f, 0.0f)
#define INITPOS glm::vec3(0.0f, 0.0f, 5.0f)
#define FOVY 70.
#define ZNEAR 0.01
#define ZFAR 1000.

#define INITKEYLIGHTPOS glm::vec3( 1., 1., 2. )
#define INITKEYLIGHTCOLOR glm::vec4( 0.8, 0.8, 0.8, 1.0)
#define INITIFILLLIGHTCOLOR  glm::vec4( 0.45, 0.45, 0.45, 1.0)
#define INITIFILLLIGHTPOS  glm::vec3( -1., 1., 2.0 )
#define INITIBACKLIGHTCOLOR  glm::vec4( 0.4, 0.4, 0.4, 1.0)
#define INITIBACKLIGHTPOS  glm::vec3( 1., 0., -1.0 )

Camera :: Camera() : InitUp( INITUP ), InitForward( INITFORWARD ),
InitRight( INITRIGHT ), InitPos( INITPOS ), rotateOn(false), fovy( FOVY ), znear ( ZNEAR ), zfar( ZFAR )
{
	Pos = InitPos;
	Forward = InitForward;
	Up = InitUp;
	Right = InitRight;
	oldX = 0;
	oldY = 0;

	KeyLight = new Light( INITKEYLIGHTPOS, INITKEYLIGHTCOLOR );
	FillLight = new Light( INITIFILLLIGHTPOS, INITIFILLLIGHTCOLOR );
	BackLight = new Light( INITIBACKLIGHTPOS, INITIBACKLIGHTCOLOR );


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
			glm::normalize(Forward);
			Right =  glm::rotate(Right, glm::radians(-dx*sensityvity), Up);
			glm::normalize(Right);

			KeyLight -> setPos( glm::rotate( KeyLight -> getPos(), glm::radians(-dx*sensityvity), Up ) );
			FillLight -> getPos() = glm::rotate( FillLight -> getPos(), glm::radians(-dx*sensityvity), Up );
			BackLight -> getPos() = glm::rotate( BackLight -> getPos(), glm::radians(-dx*sensityvity), Up );
			

			
		}
		else
		{
			Pos =  glm::rotate(Pos, glm::radians(-dy*sensityvity), Right);
			Forward = glm::rotate(Forward, glm::radians(-dy*sensityvity), Right);
			glm::normalize(Forward);
			Up =  glm::rotate(Up, glm::radians(-dy*sensityvity), Right);
			glm::normalize(Up);


			KeyLight -> setPos( glm::rotate( KeyLight -> getPos(), glm::radians(-dy*sensityvity), Right ) );
			FillLight -> getPos() = glm::rotate( FillLight -> getPos(), glm::radians(-dy*sensityvity), Right );
			BackLight -> getPos() = glm::rotate( BackLight -> getPos(), glm::radians(-dy*sensityvity), Right );
			

		}
	}
}

void Camera :: handleMouseRoll( double y )
{
	Pos = (Pos + Forward*((float)-y*0.4f) );


}
void Camera :: handleKeyBoard( int key, int action )
{

	if( key == GLFW_KEY_K && action == GLFW_PRESS )
	{

		if( KeyLight -> getLightSwitch() )
		{
			KeyLight -> getLightSwitch() = false;
			KeyLight -> getColor() = KeyLight -> getOffColor();
		}
		else
		{
			KeyLight -> getLightSwitch() = true;
			KeyLight -> getColor() = KeyLight -> getOnColor();
		}
	}
	if( key == GLFW_KEY_F && action == GLFW_PRESS )
	{

		if( FillLight -> getLightSwitch() )
		{
			FillLight -> getLightSwitch() = false;
			FillLight -> getColor() = FillLight -> getOffColor();
		}
		else
		{
			FillLight -> getLightSwitch() = true;
			FillLight -> getColor() = FillLight -> getOnColor();
		}
	}
	if( key == GLFW_KEY_B && action == GLFW_PRESS )
	{

		if( BackLight -> getLightSwitch() )
		{
			BackLight -> getLightSwitch() = false;
			BackLight -> getColor() = BackLight -> getOffColor();
		}
		else
		{
			BackLight -> getLightSwitch() = true;
			BackLight -> getColor() = BackLight -> getOnColor();
		}
	}
}



glm::vec3 Camera :: getLightPos( char light )
{
	switch( light )
	{
		case( 'k' ):
			return KeyLight -> getPos();
			break;
		case( 'f' ):
			return FillLight -> getPos();
			break;
		case( 'b' ):
			return BackLight -> getPos();
			break;
	}
	return glm::vec3(0.,0.,0.);
}

glm::vec4& Camera :: getLightColor( char light )
{
	switch( light )
	{
		case( 'k' ):
			return KeyLight -> getColor();
			break;
		case( 'f' ):
			return FillLight -> getColor();
			break;
		default:
			return BackLight -> getColor();
			break;
	}
	
}


