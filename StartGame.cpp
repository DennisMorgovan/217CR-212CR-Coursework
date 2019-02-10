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
#include "Lighting.h"
#include<iostream>
using namespace std;

#define PI 3.14159265

//Globals
Obstacle obstacle1 = Obstacle(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
Obstacle obstacle2 = Obstacle(glm::vec3(2, 2, 2), glm::vec3(0, 0, 1));

int CameraMode; //Integer that determines the angle that the camera will take

GLuint racetrackID = 1, hovercraftID = 1; //Unique identification for the display list used in the function loadObj

glm::vec3 cameraUp(0, 1, 0), cameraCorrection(10 * cos(0), 5, 0); //Camera variables.

//Object hovercraft;
Hovercraft hovercraft(glm::vec3(0, 0, 0), (char *)"hovercraft_body_blender.obj", (char *)"hovercraft_propeller_blender.obj", hovercraftID); //Takes in a position vector, the model's path and the base ID of the hovercraft.
Racetrack racetrack(glm::vec3(0, -40.00, -105), (char *)"racetrack_blender.obj", racetrackID);
Camera camera(&hovercraft, cameraUp, cameraCorrection); //Camera; requires a pointer to a hovercraft, an "up" vector
Lighting lighting;

int msaa = 1; //Multisampling

int lastTime = 0, currentTime = 0;

//Stores keys as pairs of key and state (true = pressed, false = released)
std::map <int, bool> GameObject::specialKeys;
std::map <char, bool> GameObject::keys;

static long font = (long)GLUT_BITMAP_8_BY_13; // Font selection.

// Routine to draw a bitmap character string.
void writeBitmapString(void *font, char *string)
{
	char *c;

	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Initialization routine. Similar to void Start() in Unity
void setup(void)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2, 0.6, 1, 0);
	glEnable(GL_MULTISAMPLE);

	//Functions that are called to setup basic OpenGL lighting
	lighting.setupLighting();

	unsigned int base = glGenLists(2); // Generate display list base. 
	base = obstacle1.setupDrawing(base);
	base = obstacle2.setupDrawing(base);

	obstacle1.start();
	obstacle2.start();
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);

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
		camera.cameraMode = 0;
		break;
	case 's':
		camera.cameraMode = 1;
		break;
	case 'd':
		camera.cameraMode = 2;
		break;
	case 'f':
		camera.cameraMode = 3;
		break;
	case 'g':
		camera.cameraMode = 4;
		break;
	case '1': //Toggles MSAA on/off
		if (msaa == 1)
		{
			glEnable(GL_MULTISAMPLE_ARB);
			cout << "MSAA on" << endl;
		}
		else
		{
			glDisable(GL_MULTISAMPLE_ARB);
			cout << "MSAA off" << endl;
		}
		msaa *= -1;
		break;
	default:
		break;
	}
}

//Function that processes movement key inputs and modifies hovercraft global x,z and angle values accordingly.
void specialKeyInput(int key, int x, int y)
{
	//hovercraft.movement(key);

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
	//Calculates delta time (in ms)
	lastTime = currentTime;
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = currentTime - lastTime;

	//If the last frame was rendered less than 1 ms ago, the detalaTime will be 0 ms. This causes problems in calculations, so sleep for 1ms to adjust.
	if (deltaTime == 0) {
		Sleep(1);
		currentTime = glutGet(GLUT_ELAPSED_TIME);
		deltaTime = currentTime - lastTime;
	}

	std::cout << "FPS: " << 1000 / deltaTime << endl;

	//Run update for all game objects.
	//for (std::vector<GameObject*>::size_type i = 0; i != gameobjects.size(); i++) {
	//	gameobjects[i]->update(deltaTime);
	//}	

	   // Write text in isolated (i.e., before gluLookAt) translate block.
	glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glRasterPos2f(20, 20);
		writeBitmapString((void*)font, (char*)"FPS: " + 1000 / deltaTime);
	glPopMatrix();

	hovercraft.update(deltaTime);

	glutPostRedisplay(); //Refreshes the current window
}

// Initialises various OpenGL functions
void initialise(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE); //GLUT_DOUBLE - double buffered window; GLUT_RGBA - rgba mode bit mask; GLUT_DEPTH - depth buffer
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Hovercraft Program");
}

void display(void)
{
	float lightPos0[] = { 1.0, 2.0, 0.0, 1.0 };
	float lightAmb[] = { 0, 0, 0, 1.0 };
	float lightDifAndSpec0[] = { 1.0, 1.0, 1.0, 1.0 };

	// Light0 properties.
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec0);

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//grass field
	glPushMatrix();
		glColor3f(0, 1, 0);
		glScalef(500, 500, 500);
		glBegin(GL_QUADS);
			glVertex3f(5, 0, 5);
			glVertex3f(-5, 0, 5);
			glVertex3f(-5, 0, -5);
			glVertex3f(5, 0, -5);
		glEnd();
	glPopMatrix();

	//Obstacles
	obstacle1.draw();
	obstacle2.draw();

	//Racetrack
	racetrack.draw();

	camera.update(); //Updating camera position

	//Hovercraft transforms
	hovercraft.draw();

	//Sets light position
	glPushMatrix();
		lightPos0[0] = 50; lightPos0[1] = 50; lightPos0[2] = 0.0;
		glRotatef(45, 1, 0, 0);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
		glTranslatef(lightPos0[0], lightPos0[1], lightPos0[2]);
	glPopMatrix();
	
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

	// Register the mouse callback function.
    glutMouseFunc(mouseControl); 

    // Register the mouse motion callback function.
    glutMotionFunc(mouseMotion);

	//Lambda functions to link our code to glut's keydown and keyup. Our function deals with both regular and special keys in one.
	glutKeyboardFunc([](unsigned char key, int x, int y) {
		GameObject::keys[key] = true;
		//if we press escape, exit the game
		if (key == 27) {
			exit(0);
		}
	});

	glutKeyboardUpFunc([](unsigned char key, int x, int y) {
		GameObject::keys[key] = false;
	});

	glutSpecialFunc([](int key, int x, int y) {
		GameObject::specialKeys[key] = true;
	});

	glutSpecialUpFunc([](int key, int x, int y) {
		GameObject::specialKeys[key] = false;
	});

	glutIdleFunc(idle); //Sets what function to be callbacked when idle

	glewExperimental = GL_TRUE;
	glewInit();

	setup();
	CameraMode = 0;

	glutMainLoop(); //Starts game loop
}

//Framerate on right side of screen; make camera follow hovercraft, finish up hovercraft class; make inheritance of hovercraft work
//Acceleration
//Make rotation using mosue wheel