#include <glm/glm.hpp>
#ifndef __MODEL_H__
#define __MODEL_H__ 



class Model
{
private:
	char vert_sha[1024 * 256];
	char frag_sha[1024 * 256];

	
    float *points;
    float *normals;
    float *textCoords;
	int pointCount;

	glm::vec4 color;
	
	bool load_obj_file( const char *file_name );
	bool loadShader();
public:
	Model();
	Model( const Model & ) = delete;
	Model( const char * );
	const char* getVertShad() const { return (char*) vert_sha; }
	const char* getFragShad() const { return (char*) frag_sha; }
	float* getPoints() const { return points; }
	float* getNormals() const { return normals;}
	int getPointCount() const {return pointCount;}
	glm::vec4 getColor() const{ return color;}
};



#endif