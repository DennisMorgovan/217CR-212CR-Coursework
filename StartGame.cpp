/* OPENGL_INCLUDES */
#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/freeglut.h>
#pragma comment(lib, "glew32.lib") 
#endif 
#include<math.h>
#include<fstream>
#include<vector>
#include "Obstacle.h";
#include "Reader.h"
using namespace std;

#define PI 3.14159265

//Globals
Obstacle obstacle1 = Obstacle(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
Obstacle obstacle2 = Obstacle(glm::vec3(2, 2, 2), glm::vec3(0, 0, 1));

int CameraMode; //Integer that determines the angle that the camera will take
float latAngle = 0.0;

GLuint racetrackID = 1; //Unique identification for the display list used in the function loadObj
float racetrackrot; //Used to display the imported model (the racetrack in this case) as rotating
Reader racetrack;

// Initialization routine. Similar to void Start() in Unity
void setup(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	unsigned int base = glGenLists(2); // Generate display list base. 
	base = obstacle1.setupDrawing(base);
	base = obstacle2.setupDrawing(base);

	obstacle1.start();
	obstacle2.start();

	racetrack.loadModel((char *)"racetrack_blender.obj", racetrackID);
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);

	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	/* set up depth-buffering */
	glEnable(GL_DEPTH_TEST);

	/* turn on default lighting */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1920 / 1080, 4, 500);

	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'a':
		CameraMode = 0;
		break;
	case 's':
		CameraMode = 1;
		break;
	case 'd':
		CameraMode = 2;
		break;
	default:
		break;
	}
}

void animate() {

	//latAngle += 0.1; //Rotates the sphere
	//if (latAngle > 360.0) latAngle -= 360.0;

	/* refresh screen */
	glutPostRedisplay();
}

void idle()
{
	glutPostRedisplay(); //Refreshes the current window
}

// Initialises various OpenGL functions
void initialise(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Hovercraft Program");
}

//Function that creates the racetrack. Used in the display function.
void drawRacetrack()
{
	glPushMatrix();
	glTranslatef(0, -40.00, -105);
	glColor3f(1.0, 0.23, 0.27);
	glScalef(0.1, 0.1, 0.1);
	glRotatef(racetrackrot, 0, 1, 0);

	//Creates racetrack
	racetrack.drawObj();

	glPopMatrix();
	racetrackrot = racetrackrot + 0.6;
	if (racetrackrot > 360)
		racetrackrot = racetrackrot - 360;
}

void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Camera mode; change camera mode using keys
	if (CameraMode == 0)
		gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //fix camera
	else if (CameraMode == 1)
		gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //an exampleof fix camera
	else
		gluLookAt(0.0, 0.0, 7.0, 3.0, 0.0, 3.0, 0.0, 1.0, 0.0); //an exampleof fix camera

	//Obstacles
	obstacle1.draw();
	obstacle2.draw();

	//Hovercraft
	glPushMatrix();
	glTranslatef(0, -40, -50); //Sets cube position
	glColor3f(1, 1, 1); //Sets cube colour
	glutSolidCube(2); //Creates cube shape
	glPopMatrix();

	//Hovercraft front
	glPushMatrix();
	glColor3f(-2, 0, 2); //Sets cone colour
	glTranslatef(-2, -40, -50); //Sets cone position
	glRotatef(-90, 0, 1, 0); //Sets cone rotation
	glutSolidCone(2, 2, 30, 30); //Creates cone shape
	glPopMatrix();

	//Racetrack
	drawRacetrack();

	glutSwapBuffers(); //swap the buffers
}

// Main routine.
int main(int argc, char **argv)
{
	//auto keyEsc = [](unsigned char key, int x, int y) -> void { switch (key){case 27:exit(0);break;default:break;} }; //Lambda function for exiting program when pressing Esc
	//auto idle = []() -> void { glutPostRedisplay(); };
	//auto resize = [](int w, int h) -> void { glViewport(0, 0, w, h);glMatrixMode(GL_PROJECTION);glLoadIdentity();gluPerspective(60.0, (float)w / (float)h, 1.0, 500.0);glMatrixMode(GL_MODELVIEW); };

	initialise(argc, argv);

	glutDisplayFunc(display); //Sets callback function for displaying
	glutReshapeFunc(resize); //Sets what function to be callbacked in order to resize the window
	glutKeyboardFunc(keyInput); //Sets what function to be callbacked when pressing a specific key 
	glutIdleFunc(idle); //Sets what function to be callbacked when idle

	glewExperimental = GL_TRUE;
	glewInit();

	setup();
	CameraMode = 0;


	glutMainLoop(); //Starts game loop
}
