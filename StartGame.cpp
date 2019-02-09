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
#include "Obstacle.h"
#include "Reader.h"
#include "Hovercraft.h"
#include "Racetrack.h"
#include "Camera.h"
#include<iostream>
using namespace std;

#define PI 3.14159265

//Globals
Obstacle obstacle1 = Obstacle(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
Obstacle obstacle2 = Obstacle(glm::vec3(2, 2, 2), glm::vec3(0, 0, 1));
//float angle = 0.0; //Angle of the hovercraft that will be modified via key input
//float xCoord = 0, zCoord = 0; //x and z coordinates that will be modified via key input

int CameraMode; //Integer that determines the angle that the camera will take

GLuint racetrackID = 1, hovercraftID = 1; //Unique identification for the display list used in the function loadObj

glm::vec3 cameraUp(0, 1, 0), cameraCorrection(20 * cos(0), 10, 20 * sin(0)); //Camera variables.

//Object hovercraft;
Hovercraft hovercraft(glm::vec3(0, 0, 0), (char *)"hovercraft_blender_final.obj", hovercraftID); //Takes in a position vector, the model's path and the base ID of the hovercraft.
Racetrack racetrack(glm::vec3(0, -40.00, -105), (char *)"racetrack_blender.obj", racetrackID);
Camera camera(&hovercraft, cameraUp, cameraCorrection); //Camera; requires a pointer to a hovercraft, an "up" vector

// Initialization routine. Similar to void Start() in Unity
void setup(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	unsigned int base = glGenLists(2); // Generate display list base. 
	base = obstacle1.setupDrawing(base);
	base = obstacle2.setupDrawing(base);

	obstacle1.start();
	obstacle2.start();
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);

	//glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
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

//Function that processes movement key inputs and modifies hovercraft global x,z and angle values accordingly.
void specialKeyInput(int key, int x, int y)
{
	hovercraft.movement(key);

	glutPostRedisplay();
}

// Mouse callback routine.
void mouseControl(int key, int state, int x, int y)
{
	camera.mouseControl(key, state, x, y);
}

// Mouse motion callback routine.
void mouseMotion(int x, int y)
{
	camera.mouseMotion(x, y);
}

void animate() {
	
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //GLUT_DOUBLE - double buffered window; GLUT_RGBA - rgba mode bit mask; GLUT_DEPTH - depth buffer
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Hovercraft Program");
}

void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Obstacles
	obstacle1.draw();
	obstacle2.draw();

	//Racetrack
	racetrack.draw();

	//hovercraft.position.x = xCoord; hovercraft.position.z = zCoord; //Updating the coordinates of the hovercraft based on input
	camera.update(); //Updating camera position

	//Hovercraft transforms
	hovercraft.draw();
	
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
	glutSpecialFunc(specialKeyInput);
	glutIdleFunc(animate); //Sets what function to be callbacked when idle

	// Register the mouse callback function.
    glutMouseFunc(mouseControl); 

    // Register the mouse motion callback function.
    glutMotionFunc(mouseMotion);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();
	CameraMode = 0;

	glutMainLoop(); //Starts game loop
}

//Framerate on right side of screen; make camera follow hovercraft, finish up hovercraft class; make inheritance of hovercraft work
//Acceleration
//Make rotation using mosue wheel