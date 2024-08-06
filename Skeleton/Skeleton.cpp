#include "framework.h"
#include "Spiral.h"
#include "Textures.h"
#include "App.h"

enum State {
	width, steepnes, speed, alpha
};
State userState(width);

//Spiral spiral2(400);
// Initialization, create an OpenGL context
void onInitialization() {
	glViewport(0, 0, windowWidth, windowHeight);
	glLineWidth(5.0f);
	glEnable(GL_BLEND);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	
	app->loadFromFile("settings.json");

	app->create();
}

// Window has become invalid: Redraw
void onDisplay() {
	app->render();

	glutSwapBuffers(); // exchange buffers for double buffering

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cerr << "OpenGL error: " << err << std::endl;
	}
}

void onKeyboard(unsigned char key, int pX, int pY)
{
	if (key == 'w') {
		userState = width;
		std::cout << key << std::endl;
	}
	else if (key == 'd')
	{
		userState = steepnes;
		std::cout << key << std::endl;
	}
	else if (key == 'l')
	{
		userState = alpha;
		std::cout << key << std::endl;
	}
	else if (key == 's')
	{
		userState = speed;
		std::cout << key << std::endl;
	}
	else if (key == 'r')
	{
		app->loadFromFile("settings.json");
	}
}

void onSpecialKeyboard(int key, int pX, int pY)
{

	if (key == GLUT_KEY_LEFT)
	{		
		if (userState == width)
		{
			//spiral.SetWidth(-0.01f);
			//app.update();
			glutPostRedisplay();
		}
		else if (userState == steepnes)
		{
			//spiral.SetSteepnes(-0.01f);
			//app.update();
			glutPostRedisplay();
		}
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		if (userState == width)
		{
			//spiral.SetWidth(0.01f);
			//app.update();
			glutPostRedisplay();
		}
		else if (userState == steepnes)
		{
			//spiral.SetSteepnes(0.01f);
			//app.update();
			glutPostRedisplay();
		}
	}

}


// Idle event indicating that some time elapsed: do animation here
void onIdle() {
	long time = glutGet(GLUT_ELAPSED_TIME); // elapsed time since the start of the program
	glutPostRedisplay();
}
