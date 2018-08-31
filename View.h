#include "Camera.h"

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

	char vertex_shader[1024 * 256];
	char fragment_shader[1024 * 256];

	Camera *camera;
	bool loadShader( char *vert_sha, char *frag_sha );

public:
	View();
	int getWidth() const {return CurrentWindow_W;}
    int getHeight() const {return CurrentWindow_H;}
    void reshapeWindow( int w, int h );
    char *getVertSha() const { return (char*)vertex_shader; }
    char *getFragSha() const { return (char*) fragment_shader; }
	void initList();
	void display();
	
};


#endif