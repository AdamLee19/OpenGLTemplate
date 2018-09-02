#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "View.h"




GLFWwindow* window = NULL;
//const GLFWvidmode* mode = NULL;
//GLFWmonitor* monitor = NULL;
const char *WINDOWTITLE = {"OpenGL/Template"};

View Object;



/*************
 
Function Prototypes

*************/


void InitGraph();
void InitList();
void Display();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
void window_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);



int main()
{
	InitGraph();
	Object.initList();
	
	

	while( !glfwWindowShouldClose(window) )
	{
		
		
		
		
		Object.display();


		
		glfwSwapBuffers( window );
		glfwPollEvents();
	}
	glfwDestroyWindow( window );
	glfwTerminate();
	return 0;
}

void InitGraph()
{
	if( !glfwInit() )
	{
		std::cout << "ERROR: Could not start GLFW3" << std::endl;
		exit(1);
	}
	#ifdef APPLE
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	#endif


	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *mode = glfwGetVideoMode( monitor );
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	

	window = glfwCreateWindow( 1, 1, WINDOWTITLE, NULL, NULL);

   	
	if( !window )
	{
		std::cout << "ERROR: Could not open window" << std::endl;
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent( window );

	//Initialize GLew
	glewExperimental = GL_TRUE;
	glewInit();

	//Callback Function
	glfwSetKeyCallback( window, key_callback );
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_move_callback);
	glfwSetFramebufferSizeCallback(window, window_size_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetWindowSize( window, Object.getWidth(), Object.getHeight() );	
	glfwSetWindowPos ( window, 0, 0);
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if ( glfwGetKey ( window, GLFW_KEY_Q ) )
    {
      	glfwDestroyWindow( window );
		glfwTerminate();
		exit(0);
    }
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

	double xpos,ypos;

	glfwGetCursorPos(window, &xpos, &ypos);
	Object.handleMouseButtons( button, action, xpos, ypos );


}

void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
	Object.handleMouseMove(xpos,ypos);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	Object.reshapeWindow( width, height );
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Object.handleMouseRoll( yoffset );
}




