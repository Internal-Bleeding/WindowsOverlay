//=============================================================================================
// Collection of classes from lecture slides.
// Framework for assignments. Valid from 2019.
// Do not change it if you want to submit a homework.
//=============================================================================================
#include "framework.h"
#include "App.h"

// Initialization
void onInitialization();

// Window has become invalid: Redraw
void onDisplay();

// Idle event indicating that some time elapsed: do animation here
void onIdle();

void onKeyboard(unsigned char key, int pX, int pY);

void onSpecialKeyboard(int key, int pX, int pY);

HWND getWindowHandle() {
	return FindWindow(NULL, "SPIRAL");
}

void hideTitleBar(HWND hwnd) {
	// Hide the title bar
	LONG style = GetWindowLong(hwnd, GWL_STYLE);
	style &= ~WS_CAPTION;
	SetWindowLong(hwnd, GWL_STYLE, style);

	// Optional: Force the window to update its appearance
	SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
}

void makeWindowTransparent(HWND hwnd) {
	// Make the window transparent
	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
	SetLayeredWindowAttributes(hwnd, 0, 100, LWA_ALPHA);
	//SetLayeredWindowAttributes(hwnd, 0, 100, LWA_ALPHA);

	// Make the window click-through
	LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
	exStyle |= WS_EX_LAYERED | WS_EX_TRANSPARENT;
	SetWindowLong(hwnd, GWL_EXSTYLE, exStyle);
}

void makeTopMost(HWND hwnd) {
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

App* app = nullptr;

// Entry point of the application
int main(int argc, char * argv[]) {
	// Initialize GLUT, Glew and OpenGL 
	glutInit(&argc, argv);

	// OpenGL major and minor versions
	int majorVersion = 3, minorVersion = 3;
#if !defined(__APPLE__)
	glutInitContextVersion(majorVersion, minorVersion);
#endif
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	glutInitWindowSize(screenWidth, screenHeight);			// Application window is initially of resolution 600x600
	glutInitWindowPosition(0, 0);							// Relative location of the application window
#if defined(__APPLE__)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);  // 8 bit R,G,B,A + double buffer + depth buffer
#else
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
#endif
	
	glutCreateWindow(argv[0]);
	glutSetWindowTitle("SPIRAL");

#if !defined(__APPLE__)
	glewExperimental = true;	// magic
	glewInit();
#endif
	printf("GL Vendor    : %s\n", glGetString(GL_VENDOR));
	printf("GL Renderer  : %s\n", glGetString(GL_RENDERER));
	printf("GL Version (string)  : %s\n", glGetString(GL_VERSION));
	glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
	printf("GL Version (integer) : %d.%d\n", majorVersion, minorVersion);
	printf("GLSL Version : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	// Initialize this program and create shaders

	app = new App();
	HWND hwnd = getWindowHandle();
	app->setWindowHandle(hwnd);

	hideTitleBar(hwnd);
	makeTopMost(hwnd);

	onInitialization();
	glutFullScreen();



	glutDisplayFunc(onDisplay);                // Register event handlers
	glutSpecialFunc(onSpecialKeyboard);
	glutKeyboardFunc(onKeyboard);
	glutIdleFunc(onIdle);

	glutMainLoop();

	delete app;

	return 1;
}
