#include <StageManager.hpp>
#include <Windows.h>
#include <memory>
#include <GL/glut.h>

constexpr unsigned REFRESH_DISPLAY = 13u; // 60 fps
constexpr unsigned TIME = 100u; // 100 milisekund
constexpr char WINDOW_NAME[] = "Mechanics of terrain model shaping";

std::unique_ptr<StageManager> stageManager;

void Display()
{
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

void RefreshDisplay(int t)
{
	glutPostRedisplay();
	glutTimerFunc(REFRESH_DISPLAY, RefreshDisplay, 0);
}

void Time(int t)
{
	stageManager->Time(t);
	glutTimerFunc(1u, Time, 0);
}

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
int main()
{
	int argc = 1;
	char* argv[1] = { (char*)"" };

	srand((unsigned int)time(NULL));
	SetProcessDPIAware();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN)); // Maximum resolution
	glutCreateWindow(WINDOW_NAME);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	glutFullScreen();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutSpecialFunc(Special);
	glutKeyboardFunc(OnKeyDown);
	glutMouseFunc(OnMouseClick);
	glutSetCursor(GLUT_CURSOR_NONE); // Nothing

	/* Timer functions */
	glutTimerFunc(REFRESH_DISPLAY, RefreshDisplay, 0);
	glutTimerFunc(1u, Time, 0);

	// OpenGL initialization
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	stageManager = std::make_unique<StageManager>();

	glutMainLoop();

	stageManager.reset();
	return EXIT_SUCCESS;
}
