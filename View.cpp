#include "View.h"
#include "Camera.h"
#include "Model.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>



enum VAO_IDs { Teapot, NumVAOs };
enum Buffer_IDs { PointBuffer, PointNormalBuffer, NumBuffers };

GLuint VAOs[ NumVAOs ];
GLuint Buffers[ NumBuffers ];

                            
GLuint shader_programme;


float InitBackGroundColor[4] = { 0.5, 0.5, 0.5, 1.0 };


Model teapot("teapot.obj");

View :: View() : InitWindow_W(WINDOW_W), InitWindow_H( WINDOW_H ), camera( nullptr )
{

   
	CurrentWindow_H = InitWindow_H;
	CurrentWindow_W = InitWindow_W;

	camera = new Camera();
	backgroundcolor = InitBackGroundColor;

	proj =  glm::perspective(glm::radians(camera -> getFovy()), (float)CurrentWindow_W/(float)CurrentWindow_H, camera -> getZnear(), camera -> getZfar());
	view = glm::lookAt( camera -> getPos(), camera -> getForw(), camera -> getUp() );
	model = glm::mat4(1.0);
	
	
}


void View :: reshapeWindow( int w, int h )
{
	float camaspect = float(CurrentWindow_W) / float(CurrentWindow_H);   // camera's aspect ratio
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


void View :: initList()
{
	GLuint vertNum, fragNum;
	const char*v = teapot.getVertShad();
	const char*f = teapot.getFragShad();
	

	glGenBuffers( NumBuffers,Buffers );
	glBindBuffer( GL_ARRAY_BUFFER, Buffers[PointBuffer] );
	glBufferData( GL_ARRAY_BUFFER, teapot.getPointCount() * sizeof( float ) * 3, teapot.getPoints(), GL_STATIC_DRAW );

	glBindBuffer( GL_ARRAY_BUFFER, Buffers[PointNormalBuffer]);
	glBufferData( GL_ARRAY_BUFFER, teapot.getPointCount() * sizeof( float ) * 3, teapot.getNormals(), GL_STATIC_DRAW );
	

	glGenVertexArrays( NumVAOs, &VAOs[Teapot] );
	glBindVertexArray( VAOs[Teapot] );

	//Active VAO, Bind VBO to VAO
	glEnableVertexAttribArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER, Buffers[PointBuffer] );
	glVertexAttribPointer( PointBuffer, 3, GL_FLOAT, GL_FALSE, 0, NULL );
	
	glEnableVertexAttribArray( 1 );
	glBindBuffer( GL_ARRAY_BUFFER, Buffers[PointNormalBuffer]);
	glVertexAttribPointer( PointNormalBuffer, 3, GL_FLOAT, GL_TRUE, 0, NULL );

	
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



	glEnable (GL_DEPTH_TEST); 
	glDepthFunc (GL_LESS); 
	// glEnable (GL_CULL_FACE); 
	// glCullFace (GL_FRONT); 
	// glFrontFace (GL_CW);

	glClearColor( backgroundcolor[0],backgroundcolor[1], backgroundcolor[2], backgroundcolor[3] );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram( shader_programme );
	proj =  glm::perspective(glm::radians(camera -> getFovy()), (float)CurrentWindow_W/(float)CurrentWindow_H, camera -> getZnear(), camera -> getZfar());
	
	//2nd prameter is actually look at a position. Not forward vector;
	view = glm::lookAt( camera -> getPos(), camera -> getForw() + camera -> getPos(), camera -> getUp() );
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

	int view_mat_location = glGetUniformLocation (shader_programme, "view_mat");
	int proj_mat_location = glGetUniformLocation (shader_programme, "proj_mat");
	int model_mat_location = glGetUniformLocation (shader_programme, "model_mat");
	int model_color = glGetUniformLocation (shader_programme, "color");
	//std::cout << model_color << std::endl;

	

	//1 represents 1 matrix, GL_FALSE represents transpose
	glUniformMatrix4fv (view_mat_location, 1, GL_FALSE,  glm::value_ptr(view));
	glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE,  glm::value_ptr(proj));
	glUniformMatrix4fv (model_mat_location, 1, GL_FALSE,  glm::value_ptr(model));

	glUniform3fv ( model_color, 1, glm::value_ptr(teapot.getColor() ) );
	//std::cout << teapot.getColor()[0] << std::endl;





	glUseProgram( shader_programme );
	glBindVertexArray(VAOs[Teapot]);
	glDrawArrays(GL_TRIANGLES, 0, teapot.getPointCount() );


	//std::cout <<  << std::endl;



}

void View :: handleMouseButtons(int button, int action, double x, double y)
{
	camera -> handleMouseButtons( button, action, x, y );
}

void View :: handleMouseMove( double x, double y )
{
	camera -> handleMouseMove( x, y );
}


void View :: handleMouseRoll( double y )
{
	camera -> handleMouseRoll( y );
}

