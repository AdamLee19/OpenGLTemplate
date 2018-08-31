#include "View.h"
#include "Camera.h"
#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };

GLuint VAOs[ NumVAOs ];
GLuint Buffers[ NumBuffers ];

const GLfloat points[] = { 0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f };

	/* GL shader programme object [combined, to link] */
GLuint shader_programme;

	/* the fragment shader colours each fragment (pixel-sized area of the
	triangle) */





View :: View() : InitWindow_W(WINDOW_W), InitWindow_H( WINDOW_H ), camera( nullptr )
{
	CurrentWindow_H = InitWindow_H;
	CurrentWindow_W = InitWindow_W;

	camera = new Camera();
	loadShader( vertex_shader, fragment_shader );
	//std::cout << fragment_shader << std::endl;
	
}


void View :: reshapeWindow( int w, int h )
{
	float camaspect = float(InitWindow_W) / float(InitWindow_H);   // camera's aspect ratio
	float newaspect = float(w) / float(h);

	CurrentWindow_W = w;
	CurrentWindow_H = h;

	if(newaspect > camaspect)
    	CurrentWindow_W = int(h * camaspect);
  	else
    	CurrentWindow_H = int(w / camaspect);
 	
 	 float x0 = (w - CurrentWindow_W) / 2;
  	 float y0 = (h - CurrentWindow_H) / 2;

  	 glViewport(x0, y0, CurrentWindow_W, CurrentWindow_H);
}



bool View::loadShader( char *vert_sha, char *frag_sha )
{
	char *file_name = (char*)"vs.glsl";
	FILE *file = fopen( file_name, "r" );
	if ( !file ) {
		std::cout << "ERROR: opening shading for reading: " << file_name << std::endl;
		return false;
	}
	size_t cnt = fread( vert_sha, 1, 1024 * 256 - 1, file );
	if ( (int)cnt >= 1024 * 256 - 1 ) {
		std::cout << "WARNING: file %s too big - truncated." << file_name << std::endl;
	}
	if ( ferror( file ) ) {
		std::cout <<  "ERROR: reading shader file: " << file_name << std::endl;
		fclose( file );
		return false;
	}
	
	vert_sha[cnt] = 0;
	fclose( file );

	file_name = (char*)"fs.glsl";

	file = fopen( file_name, "r" );
	if ( !file ) {
		std::cout << "ERROR: opening shading for reading: " << file_name << std::endl;
		return false;
	}
	cnt = fread( frag_sha, 1, 1024 * 256 - 1, file );
	if ( (int)cnt >= 1024 * 256 - 1 ) {
		std::cout << "WARNING: file %s too big - truncated." << file_name << std::endl;
	}
	if ( ferror( file ) ) {
		std::cout <<  "ERROR: reading shader file: " << file_name << std::endl;
		fclose( file );
		return false;
	}
	
	frag_sha[cnt] = 0;
	fclose( file );
	
	file_name = (char*)"fs.glsl";


	return true;
}


void View :: initList()
{
	GLuint vertNum, fragNum;
	const char*v = (char*) vertex_shader;
	const char*f = (char*) fragment_shader;

	glGenBuffers( NumVAOs,Buffers );
	glBindBuffer( GL_ARRAY_BUFFER, Buffers[ArrayBuffer] );
	glBufferData( GL_ARRAY_BUFFER, 9 * sizeof( GLfloat ), points, GL_STATIC_DRAW );

	glGenVertexArrays( NumVAOs, &VAOs[Triangles] );
	glBindVertexArray( VAOs[Triangles] );

	//Active VAO, Bind VBO to VAO
	glEnableVertexAttribArray( Triangles );
	glBindBuffer( GL_ARRAY_BUFFER, Buffers[ArrayBuffer] );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
	
	vertNum = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertNum, 1, &v, NULL );
	glCompileShader( vertNum );
	fragNum = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragNum, 1, &f, NULL );
	glCompileShader( fragNum );
	shader_programme = glCreateProgram();
	glAttachShader( shader_programme, fragNum );
	glAttachShader( shader_programme, vertNum );
	glLinkProgram( shader_programme );	
	
}

void View :: display()
{
	GLsizei vx = CurrentWindow_W;
	GLsizei vy = CurrentWindow_H;
	GLsizei v = vx < vy ? vx : vy;

	GLint xl = ( vx - v ) / 2;
	GLint yb = ( vy - v ) / 2;

	glViewport( xl, yb, v, v );
	glUseProgram( shader_programme );
	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

