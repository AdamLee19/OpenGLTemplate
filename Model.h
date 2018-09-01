#include <glm/glm.hpp>
#ifndef __MODEL_H__
#define __MODEL_H__ 



class Model
{
private:
	char vert_sha[1024 * 256];
	char frag_sha[1024 * 256];

	
    float *point;
    float *norm;
    float *text;
	int pointCount;
	
	bool load_obj_file( const char *file_name, float *&points, float *&tex_coords,\
										float *&normals, int &point_count );
	bool loadShader();
public:
	Model();
	Model( const Model & ) = delete;
	Model( const char * );
	const char* getVertShad() const { return (char*) vert_sha; }
	const char* getFragShad() const { return (char*) frag_sha; }
	float* getPoints() { return point; }
	int getPointCount() {return pointCount;}
};



#endif