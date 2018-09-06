#include "View.h"
#include "Camera.h"
#include "Model.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>





enum VAO_IDs { Teapot, NumVAOs };
enum Buffer_IDs { PointBuffer, PointNormalBuffer, PointColor, NumBuffers };

GLuint VAOs[ NumVAOs ];


                            



float InitBackGroundColor[4] = { 0.62, 0.62, 0.62, 1.0 };


Model teapot("teapot.obj");
GLuint teapotShader;

View :: View() : InitWindow_W(WINDOW_W), InitWindow_H( WINDOW_H ), camera( nullptr )
{

   
	CurrentWindow_H = InitWindow_H;
	CurrentWindow_W = InitWindow_W;

	camera = new Camera();
	backgroundcolor = InitBackGroundColor;

	proj_mat =  glm::perspective(glm::radians(camera -> getFovy()), (float)CurrentWindow_W/(float)CurrentWindow_H, camera -> getZnear(), camera -> getZfar());
	view_mat = glm::lookAt( camera -> getPos(), camera -> getForw(), camera -> getUp() );
	model_mat = glm::mat4(1.0);
	
	
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

void View :: dataPrepare( Model& model )
{
	GLuint vertNum, fragNum;
	const char*v = model.getVertShad();
	const char*f = model.getFragShad();

	glGenBuffers( NumBuffers, model.getBuffers() );
	glBindBuffer( GL_ARRAY_BUFFER, *(model.getBuffers() + PointBuffer) );
	glBufferData( GL_ARRAY_BUFFER, model.getPointCount() * sizeof( float ) * 3, model.getPoints(), GL_STATIC_DRAW );
	glBindBuffer( GL_ARRAY_BUFFER, *(model.getBuffers() + PointNormalBuffer) );
	glBufferData( GL_ARRAY_BUFFER, model.getPointCount() * sizeof( float ) * 3, model.getNormals(), GL_STATIC_DRAW );


	glEnableVertexAttribArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER, *(model.getBuffers() + PointBuffer) );
	glVertexAttribPointer( PointBuffer, 3, GL_FLOAT, GL_FALSE, 0, NULL );

	glEnableVertexAttribArray( 1 );
	glBindBuffer( GL_ARRAY_BUFFER, *(model.getBuffers() + PointNormalBuffer) );
	glVertexAttribPointer( PointNormalBuffer, 3, GL_FLOAT, GL_TRUE, 0, NULL );


	vertNum = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertNum, 1, &v, NULL );
	glCompileShader( vertNum );

	GLint success = 0;
	glGetShaderiv(vertNum, GL_COMPILE_STATUS, &success);
	if ( success == GL_FALSE )
	{
		GLint logSize = 0;

		glGetShaderiv( vertNum, GL_INFO_LOG_LENGTH, &logSize);
		GLchar errorLog[ logSize ];
		glGetShaderInfoLog(vertNum, logSize, &logSize, &errorLog[0]);
		std::cout << std::endl << "ERROR: Vertex Shader: "<< errorLog << std::endl;
		glDeleteShader(vertNum);
		exit( 1 );
	}
	
	fragNum = glCreateShader( GL_FRAGMENT_SHADER );

	glShaderSource( fragNum, 1, &f, NULL );
	glCompileShader( fragNum );

	success = 0;
	glGetShaderiv(fragNum, GL_COMPILE_STATUS, &success);

	if ( success == GL_FALSE )
	{
		GLint logSize = 0;

		glGetShaderiv( fragNum, GL_INFO_LOG_LENGTH, &logSize);
		GLchar errorLog[ logSize ];
		glGetShaderInfoLog(fragNum, logSize, &logSize, &errorLog[0]);
		std::cout << std::endl << "ERROR: Fragment Shader: "<< errorLog << std::endl;
		glDeleteShader(fragNum);
		exit( 1 );
	}




	model.getShaderProgram() = glCreateProgram();
	glAttachShader( model.getShaderProgram(), fragNum );
	glAttachShader( model.getShaderProgram(), vertNum );
	glLinkProgram( model.getShaderProgram() );

	

}
void View ::sendToShader( Model& model)
{
	glUseProgram( teapot.getShaderProgram() );
	proj_mat =  glm::perspective(glm::radians(camera -> getFovy()), (float)CurrentWindow_W/(float)CurrentWindow_H, camera -> getZnear(), camera -> getZfar());
	
	//2nd prameter is actually look at a position. Not forward vector;
	view_mat = glm::lookAt( camera -> getPos(), camera -> getForw() + camera -> getPos(), camera -> getUp() );
	model_mat = glm::translate(model_mat, glm::vec3(0.0f, 0.0f, 0.0f));
	int view_mat_location = glGetUniformLocation (model.getShaderProgram(), "view_mat");
	int proj_mat_location = glGetUniformLocation (model.getShaderProgram(), "proj_mat");
	int model_mat_location = glGetUniformLocation (model.getShaderProgram(), "model_mat");



	int model_color = glGetUniformLocation (model.getShaderProgram(), "model_color");
	int camera_pos = glGetUniformLocation (model.getShaderProgram(), "uCamPos");
	int key_light_pos = glGetUniformLocation( model.getShaderProgram(), "uKeyLightPos");
	int key_light_color = glGetUniformLocation( model.getShaderProgram(), "uKeyLightColor");
	int fill_light_pos = glGetUniformLocation( model.getShaderProgram(), "uFillLightPos");
	int fill_light_color = glGetUniformLocation( model.getShaderProgram(), "uFillLightColor");
	int back_light_pos = glGetUniformLocation( model.getShaderProgram(), "uBackLightPos");
	int back_light_color = glGetUniformLocation( model.getShaderProgram(), "uBackLightColor"); 
	//std::cout << model_color << std::endl;

	

	//1 represents 1 matrix, GL_FALSE represents transpose
	glUniformMatrix4fv (view_mat_location, 1, GL_FALSE,  glm::value_ptr(view_mat));
	glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE,  glm::value_ptr(proj_mat));
	glUniformMatrix4fv (model_mat_location, 1, GL_FALSE,  glm::value_ptr(model_mat));

	glUniform4fv ( model_color, 1, glm::value_ptr(teapot.getColor() ) );
	glUniform3fv( camera_pos, 1, glm::value_ptr( camera ->getPos() ) );
	glUniform3fv( key_light_pos, 1, glm::value_ptr( camera -> getLightPos( 'k' ) ) );
	glUniform4fv( key_light_color, 1, glm::value_ptr( camera ->getLightColor( 'k' ) ) );
	glUniform3fv( fill_light_pos, 1, glm::value_ptr( camera -> getLightPos( 'f' ) ) );
	glUniform4fv( fill_light_color, 1, glm::value_ptr( camera ->getLightColor('f') ) );
	glUniform3fv( back_light_pos, 1, glm::value_ptr( camera -> getLightPos( 'b' ) ) );
	glUniform4fv( back_light_color, 1, glm::value_ptr( camera ->getLightColor('b') ) );
}

void View :: initList()
{	

	glGenVertexArrays( NumVAOs, &VAOs[Teapot] );
	glBindVertexArray( VAOs[Teapot] );
	dataPrepare( teapot );
	
}

void View :: display()
{




	glEnable (GL_DEPTH_TEST); 
	glDepthFunc (GL_LESS); 
	

	glClearColor( backgroundcolor[0],backgroundcolor[1], backgroundcolor[2], backgroundcolor[3] );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	


	

	sendToShader(teapot);




	glUseProgram( teapot.getShaderProgram() );
	glBindVertexArray(VAOs[Teapot]);
	glDrawArrays(GL_TRIANGLES, 0, teapot.getPointCount() );






}
void View :: handleKeyBoard( int key, int action )
{

	camera -> handleKeyBoard( key, action );
	
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

