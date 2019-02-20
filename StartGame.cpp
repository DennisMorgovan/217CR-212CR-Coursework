/* OPENGL_INCLUDES */
#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/freeglut.h>
#pragma comment(lib, "glew32.lib") 
#endif 

#include <math.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <iterator>

#include "Hovercraft.h"
#include "Reader.h"
#include "Obstacle.h"
#include "Racetrack.h"
#include "Camera.h"
#include "Lighting.h"
#include "Grassfield.h"

using namespace std;

#define PI 3.14159265

//Globals
Obstacle obstacle1 = Obstacle(glm::vec3(0, 1, 0), glm::vec3(1, 0, 0), 5);
Obstacle obstacle2 = Obstacle(glm::vec3(7, 1, 10), glm::vec3(0, 0, 1), 15);

int CameraMode; //Integer that determines the angle that the camera will take

GLuint racetrackID = 1, hovercraftID = 1; //Unique identification for the display list used in the function loadObj

glm::vec3 cameraUp(0, 1, 0), cameraCorrection(10 * cos(0), 5, 0); //Camera variables.

//GameObject* hovercraft = new Hovercraft(glm::vec3(10, 0, 0), (char *)"./Models/hovercraft_body_blender.obj", (char *)"./Models/hovercraft_propeller_blender.obj", hovercraftID); 

//Object hovercraft;
Hovercraft hovercraft(glm::vec3(10, 0, 0), (char *)"./Models/hovercraft_body_blender.obj", (char *)"./Models/hovercraft_propeller_blender.obj", hovercraftID); //Takes in a position vector, the model's path and the base ID of the hovercraft.
Racetrack racetrack(glm::vec3(0, -40.00, -105), (char *)"./Models/racetrack_blender.obj", racetrackID);
Camera camera(&hovercraft, cameraUp, cameraCorrection); //Camera; requires a pointer to a hovercraft, an "up" vector
Lighting lighting;
Grassfield grassfield(glm::vec3(0, 0, 0), (char*)"./Models/grass_field_blender.obj", 1);

int msaa = 1, shading = 1; //Multisampling

int lastTime = 0, currentTime = 0, deltaTime = 1, fps;

//Stores keys as pairs of key and state (true = pressed, false = released)
std::map <int, bool> GameObject::specialKeys;
std::map <char, bool> GameObject::keys;
std::vector<GameObject*> gameObjects;
std::vector<Collider*> cubeColliderVector;
//std::vector<Obstacle*> obstacles;

//std::vector <Obstacle> obstacles;

static long font = (long)GLUT_BITMAP_8_BY_13; // Font selection.
static char fpsString[5], currentSpeedString[10];
float currentSpeed;

// Routine to draw a bitmap character string.
void writeBitmapString(void *font, char *string)
{
	char *c;
	
	for (c = string; *c != '\0'; c++) 
		glutBitmapCharacter(font, *c);
}

//Converts a float to an array of chars
void floatToString(char * destStr, int precision, float val)
{
	sprintf(destStr, "%f", val);
	destStr[precision] = '\0';
}

// Initialization routine. Similar to void Start() in Unity
void setup(void)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 0);
	glEnable(GL_MULTISAMPLE);

	//grassField.loadModelQuads((char*)"./Models/grass_field_blender.obj", 1);

	cubeColliderVector.push_back(hovercraft.collider);
	cubeColliderVector.push_back(obstacle1.collider);
	cubeColliderVector.push_back(obstacle2.collider);
	cubeColliderVector.push_back(grassfield.collider);

	//Functions that are called to setup basic OpenGL lighting
	lighting.setupLighting();
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1920 / 1080, 4, 500);

	glMatrixMode(GL_MODELVIEW);
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

void idle()
{
	//Calculates delta time (in ms)
	lastTime = currentTime;
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = currentTime - lastTime;

	//If the last frame was rendered less than 1 ms ago, the detalaTime will be 0 ms. This causes problems in calculations, so sleep for 1ms to adjust.
	if (deltaTime == 0) {
		Sleep(1);
		currentTime = glutGet(GLUT_ELAPSED_TIME);
		deltaTime = currentTime - lastTime;
	}
	fps = 1000 / deltaTime;

	//Updates
	hovercraft.update(deltaTime);

	for (std::vector<Collider*>::size_type i = 0; i != cubeColliderVector.size(); i++) {
		for (std::vector<Collider*>::size_type j = i + 1; j != cubeColliderVector.size(); j++) {
			if (cubeColliderVector[i] != NULL) {
				if (cubeColliderVector[i]->collidesWith(cubeColliderVector[j]))//If it collides
				{
					if (cubeColliderVector[i]->objectType == 1 && cubeColliderVector[j]->objectType == 2) //If first object is hovercraft & second one is obstacle
						hovercraft.collides(cubeColliderVector[j], cubeColliderVector[j]->materialBounce);
					if (cubeColliderVector[i]->objectType == 1 && cubeColliderVector[j]->objectType == 3) //If first object is hovercraft & second one is grass
						hovercraft.collidesWithGround = true;
					else
						hovercraft.collidesWithGround = false;
				}
			}
		}
	}

	currentSpeed = hovercraft.currentspeedMagnitude * 10;

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
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Hovercraft Program");
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	floatToString(fpsString, 4, fps);
	floatToString(currentSpeedString, 5, currentSpeed);

	// Write text in isolated (i.e., before gluLookAt) translate block.
	glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glScalef(2, 2, 2);
		glWindowPos2f(1700, 1000);
		writeBitmapString((void*)font, (char *)"FPS: ");
		glWindowPos2f(1750, 1000);
		writeBitmapString((void*)font, fpsString);
		glColor3f(1.0, 1.0, 1.0);
		glScalef(10, 10, 10);
		glWindowPos2f(50, 100);
		writeBitmapString((void*)font, (char *)"Speed: ");
		glWindowPos2f(100, 100);
		writeBitmapString((void*)font, currentSpeedString);
	glPopMatrix();

	//grass field
	grassfield.draw();
	
	obstacle1.draw();
	obstacle2.draw();

	//Racetrack
	racetrack.draw();

	lighting.drawLighting();
	lighting.drawSpotlight(&hovercraft);

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
	//glutKeyboardFunc(keyInput); //Sets what function to be callbacked when pressing a specific key 
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
		else if(key == '1')
			camera.cameraMode = 0;
		else if (key == '2')
			camera.cameraMode = 1;
		else if (key == '3')
			camera.cameraMode = 2;
		else if (key == '4')
			camera.cameraMode = 3;
		else if (key == '5')
			camera.cameraMode = 4;
		else if (key == 'x')
		{ 
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
		}
		else if (key == 'c')
		{
			if (shading == 1)
				glShadeModel(GL_SMOOTH);
			else
				glShadeModel(GL_FLAT);
			shading *= -1;
		}
		else if (key == 'v')
		{
			if (lighting.spotlightOn == 1)
			{
				glDisable(GL_LIGHT0);
				glEnable(GL_LIGHT1);
			}
			else
			{
				glEnable(GL_LIGHT0);
				glDisable(GL_LIGHT1);
			}

			lighting.spotlightOn *= -1;
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

//Add GameEngine class
//Make windmill + terrain
//add textures
//added ground friction
//https://www.gamedev.net/articles/programming/math-and-physics/a-verlet-based-approach-for-2d-game-physics-r2714/
