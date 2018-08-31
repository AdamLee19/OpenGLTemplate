#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


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
public:
	Camera();

};


#endif