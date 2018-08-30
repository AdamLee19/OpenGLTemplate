#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>




GLFWwindow* window = NULL;
const GLFWvidmode* mode = NULL;
GLFWmonitor* monitor = NULL;
const char *WINDOWTITLE = {"OpenGL/Template"};


enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };

GLuint VAOs[ NumVAOs ];
GLuint Buffers[ NumBuffers ];

const GLfloat points[] = { 0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f };
GLuint vert_shader, frag_shader;
	/* GL shader programme object [combined, to link] */
GLuint shader_programme;

const char *vertex_shader = "#version 410\n"
"in vec3 vp;"
"void main () {"
"  gl_Position = vec4 (vp, 1.0);"
"}";
	/* the fragment shader colours each fragment (pixel-sized area of the
	triangle) */
const char *fragment_shader = "#version 410\n"
"out vec4 frag_colour;"
"void main () {"
"  frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
"}";

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



int main()
{
	InitGraph();
	InitList();
	while( !glfwWindowShouldClose(window) )
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		
		
		Display();


		//Callback Function
		glfwSetKeyCallback( window, key_callback );
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetCursorPosCallback(window, mouse_move_callback);
		glfwSetWindowSizeCallback(window, window_size_callback);

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


	monitor = glfwGetPrimaryMonitor();
	mode = glfwGetVideoMode( monitor );
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	glfwWindowHint(GLFW_DEPTH_BITS, GL_TRUE);
	glfwWindowHint(GLFW_ALPHA_BITS, GL_TRUE);
	window = glfwCreateWindow(mode->width, mode->height, WINDOWTITLE, NULL, NULL);
	//window = glfwCreateWindow( 640, 480, "Hello Triangle", NULL, NULL );

	if( !window )
	{
		std::cout << "ERROR: Could not open window GLFW3" << std::endl;
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent( window );

	//Initialize GLew
	glewExperimental = GL_TRUE;
	glewInit();


	glEnable (GL_DEPTH_TEST); 
	glDepthFunc (GL_LESS); 
	glEnable (GL_CULL_FACE); 
	glCullFace (GL_BACK); 
	glFrontFace (GL_CW);

	glViewport(0, 0, mode->width, mode->height);

	glClearColor( 0.5f,0.5f, 0.5f, 1.f );



}


void InitList()
{
	glGenBuffers( NumVAOs,Buffers );
	glBindBuffer( GL_ARRAY_BUFFER, Buffers[ArrayBuffer] );
	glBufferData( GL_ARRAY_BUFFER, 9 * sizeof( GLfloat ), points, GL_STATIC_DRAW );

	glGenVertexArrays( NumVAOs, &VAOs[Triangles] );
	glBindVertexArray( VAOs[Triangles] );

	//Active VAO, Bind VBO to VAO
	glEnableVertexAttribArray( Triangles );
	glBindBuffer( GL_ARRAY_BUFFER, Buffers[ArrayBuffer] );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
	
	vert_shader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vert_shader, 1, &vertex_shader, NULL );
	glCompileShader( vert_shader );
	frag_shader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( frag_shader, 1, &fragment_shader, NULL );
	glCompileShader( frag_shader );
	shader_programme = glCreateProgram();
	glAttachShader( shader_programme, frag_shader );
	glAttachShader( shader_programme, vert_shader );
	glLinkProgram( shader_programme );	
	
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if ( glfwGetKey ( window, GLFW_KEY_C ) )
       glClearColor( 1.f,0.5f, 0.5f, 1.f );


}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{


    //glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    //glfwSetCursorPosCallback(window, cursor_pos_callback)
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		glClearColor( 1.f,0.5f, 0.5f, 1.f );


}

void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
	//std::cout << xpos << "," << ypos << std::endl;
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	//std::cout << width << "," << height << std::endl;
	//glViewport(0, 0, width, height);
}



void Display()
{
	glUseProgram( shader_programme );
	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
