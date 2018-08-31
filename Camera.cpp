
#include "Camera.h"


Camera :: Camera() : InitUp( glm::vec3(0.0f, 1.0f, 0.0f) ), InitForward( glm::vec3(0.0f, 0.0f, -1.0f) ),
InitRight( glm::vec3(1.0f, 0.0f, 0.0f) ), InitPos( glm::vec3(0.0f, 0.0f, 2.0f) )
{
	Pos = InitPos;
	Forward = InitForward;
	Up = InitUp;
	Right = InitRight;

}