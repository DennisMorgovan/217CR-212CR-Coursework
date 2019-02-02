#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#  include <glm/glm.hpp> 
#pragma comment(lib, "glew32.lib") 
#endif 

#include<vector>

const int maxVertices = 5000;

struct Vertex
{
	float x;
	float y;
	float z;
	float w;
};

//Class for a .obj reader
class Reader
{
private:
	FILE *fp; //Pointer to the file
	GLuint uniqueID; //Unique identification for the display list used in the function loadObj
	int read; //Integer used to determine the amount of items that are read per line. It is used in conjunction with fscanf, which returns the number of elements read per line
	char character; //character that starts at the beginning of every .obj file line
	GLfloat x, y, z, w; //Coordinates to be read from file

	//Vectors that hold x, y and z coords of a vertex, faces and normals. For instance, for i = 1, vertices[i] holds information about the x,y and z coordinates of vertex 1
	Vertex vertices[maxVertices], faces[maxVertices], normal[maxVertices]; 
	int faceNumber; //Total number of faces of the object

public:
	Reader();
	~Reader();

	void loadObj(char *fname, GLuint uniqueID); //Reads the object data

	void loadObjQuads(char *fname, GLuint uniqueID);

	void calculateNormals(); //Calculates normals using read data

	void loadModel(char *fname, GLuint uniqueID); //Calls the loadObj and calculateNormals functions

	void loadModelQuads(char *fname, GLuint uniqueID);

	void drawObj(); //Draws the object using triangle strips

	void drawObjQuads();
};
