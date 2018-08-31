#include <glm/vec3.hpp> 
#ifndef __MODEL_H__
#define __MODEL_H__ 

class Model
{
private:
	glm::vec3 *vertex;
	glm::vec3 *vertexNorm;
	int *FaceV;
	int *FaceT;
	int *FaceN;
	const char *vert_sha;
	const char *frag_sha;
public:
	Model();
	Model( const Model & ) = delete;
	Model( const char * );
};



#endif