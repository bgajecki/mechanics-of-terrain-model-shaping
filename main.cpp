#include <StageManager.hpp>
#include <Windows.h>
#include <memory>

constexpr unsigned REFRESH_DISPLAY = 13u; // 60 fps
constexpr unsigned TIME = 100u; // 100 milisekund
constexpr char WINDOW_NAME[] = "Mechanics of terrain model shaping";

std::unique_ptr<StageManager> stageManager;

void Display()
{
	// Background color
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// Start painting
	stageManager->Display();
	// End painting
	glFlush();
	glPopMatrix();
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
	glutTimerFunc(TIME, Time, 0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned int)time(NULL));

	int argc = 1;
	char* argv[1] = { (char*)"" };
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN)); // Maximum resolution
	glutCreateWindow(WINDOW_NAME);
	glutFullScreen();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutSpecialFunc(Special);
	glutKeyboardFunc(OnKeyDown);
	glutMouseFunc(OnMouseClick);
	glutSetCursor(GLUT_CURSOR_NONE); // Nothing

	/* Timer functions */
	glutTimerFunc(REFRESH_DISPLAY, RefreshDisplay, 0);
	glutTimerFunc(TIME, Time, 0);

	// OpenGL initialization
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	stageManager = std::make_unique<StageManager>();

	glutMainLoop();

	stageManager.reset();
	return EXIT_SUCCESS;
}
