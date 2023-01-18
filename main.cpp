#include <StageManager.hpp>
#include <Windows.h>
#include <memory>
#include <GL/glut.h>

std::unique_ptr<StageManager> stageManager;

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	stageManager->Display();
	glutSwapBuffers();
}

void Reshape(int width, int height)
{
	Display();
}

void Special(int key, int x, int y)
{
	stageManager->Special(key, x, y);
}

void OnKeyDown(unsigned char key, int x, int y)
{
	stageManager->OnKeyDown(key, x, y);
}

void OnMouseClick(int button, int state, int x, int y)
{
	stageManager->OnMouseClick(button, state, x, y);
}

void Motion(int x, int y)
{
	stageManager->Motion(x, y);
}

void RefreshDisplay(int dt)
{
	glutPostRedisplay();
	glutTimerFunc(0u, RefreshDisplay, 0);
}

void Time(int dt)
{
	stageManager->Time(dt);
	glutTimerFunc(0u, Time, 0);
}

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
int main()
{
	constexpr char WINDOW_NAME[] = "Mechanics of terrain model shaping";

	int argc = 1;
	char* argv[1] = { (char*)"" };

	SetProcessDPIAware();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowSize(GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN)); // Maximum resolution
	glutCreateWindow(WINDOW_NAME);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "OpenGL version supported by this platform %s\n", glGetString(GL_VERSION));
	fprintf(stdout, "Using GLEW %s\n", glewGetString(GLEW_VERSION));
	fprintf(stdout, "Using freeglut %d\n", glutGet(GLUT_VERSION));
	fprintf(stdout, "Using GLM %d\n", GLM_VERSION);
	
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutSpecialFunc(Special);
	glutKeyboardFunc(OnKeyDown);
	glutPassiveMotionFunc(Motion);
	glutMouseFunc(OnMouseClick);

	/* Timer functions */
	glutTimerFunc(0u, RefreshDisplay, 0);
	glutTimerFunc(30u, Time, 0);

	stageManager = std::make_unique<StageManager>();

	glutMainLoop();

	stageManager.reset();
	return EXIT_SUCCESS;
}
