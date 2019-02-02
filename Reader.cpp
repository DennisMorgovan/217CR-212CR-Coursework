#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#  include <glm/glm.hpp> 
#pragma comment(lib, "glew32.lib") 
#endif 

#include<vector>
#include<fstream>
#include "Reader.h"

std::ofstream g("test.txt"); //Debugging file used to store read vertices

Reader::Reader()
{
}

Reader::~Reader()
{
}

void Reader::loadObj(char *fname, GLuint uniqueID)
{
	this->fp = fopen(fname, "r"); //Opens the file fname
	this->uniqueID = uniqueID;

	int indexVertex = 0, indexFace = 0;

	while (!(feof(fp))) //While not at the end of the file
	{
		read = fscanf(fp, "%c %f %f %f", &character, &x, &y, &z); // Reads lines as sets of character, x coord, y coord, z coord, and returns the number of elements successfully read
		if (read == 4 && character == 'v') //If the number of elements read is equal to 4 (char, x, y and z) and the character is v (if it's a vertex), add it to vertices vector
		{
			//Adds coordinates to their respective vector
			vertices[indexVertex].x = x;
			vertices[indexVertex].y = y;
			vertices[indexVertex].z = z;

			g << indexVertex << " " << vertices[indexVertex].x << " " << vertices[indexVertex].y << " " << vertices[indexVertex].z << std::endl; //Used for debugging
			indexVertex++;
		}
		else
			if (read == 4 && character == 'f') //If we are reading face information, create the face using pre-existing vertex information
			{
				//Adds face information to the respective face vector
				faces[indexFace].x = x;
				faces[indexFace].y = y;
				faces[indexFace].z = z;

				g << "f " << faces[indexFace].x << " " << faces[indexFace].y << " " << faces[indexFace].z << std::endl; // Debugging
				indexFace++;
			}
		
	}
	faceNumber = indexFace; //Correctly assigns the number of faces

	fclose(fp);
}

void Reader::calculateNormals()
{
	int i, id1, id2, id3;
	float length;
	Vertex edge1, edge2, testNor, unitNor;

	for (i = 0; i < faceNumber; i++)
	{
		//Saves the data from each face into temporary variables; id1 = vertex1 index of the triangle, id2 = vertex2 index of the triangle, etc
		id1 = faces[i].x;
		id2 = faces[i].y;
		id3 = faces[i].z;

		//Calculating the edges. For a triangle with vertexes v1, v2, v3, to calculate the edge vector between v1 and v2, the formula is:
		//U = v2 - v1; this means that the x component of U will be v2.x - v1.x, y component will be v2.y - v1.y and so on. The index used will be that of the triangle vertexes, meaning th id's
		edge1.x = vertices[id2].x - vertices[id1].x;
		edge1.y = vertices[id2].y - vertices[id1].y;
		edge1.z = vertices[id2].z - vertices[id1].z;

		//Vector edge V between vertices v3 and v2
		edge2.x = vertices[id3].x - vertices[id2].x;
		edge2.y = vertices[id3].y - vertices[id2].y;
		edge2.z = vertices[id3].z - vertices[id2].z;

		//Calculating the vector cross product between vectors U and V calculated above. Formula is:
		// N.x = U.y * V.z - U.z * V.y
		// N.y = U.z * V.x - U.x * V.z
		// N.z = U.x * V.y - U.y * V.x
		testNor.x = edge1.y*edge2.z - edge1.z*edge2.y;
		testNor.y = edge1.z*edge2.x - edge1.x*edge2.z;
		testNor.z = edge1.x*edge2.y - edge1.y*edge2.x;

		//Calculating the length of the normal, using the formula:
		// length = sqrt(N.x * N.x + N.y * N.y + N.z * N.z)  -  Pythagora's theorem in 3D space
		length = sqrt(testNor.x*testNor.x + testNor.y*testNor.y + testNor.z*testNor.z);
		
		//
		unitNor.x = testNor.x / length;
		unitNor.y = testNor.y / length;
		unitNor.z = testNor.z / length;

		//Assigning the 
		normal[id1].x = unitNor.x;
		normal[id1].y = unitNor.y;
		normal[id1].z = unitNor.z;

		normal[id2].x = unitNor.x;
		normal[id2].y = unitNor.y;
		normal[id2].z = unitNor.z;

		normal[id3].x = unitNor.x;
		normal[id3].y = unitNor.y;
		normal[id3].z = unitNor.z;
	}
}

//Executes functions needed to load a model
void Reader::loadModel(char *fname, GLuint uniqueID)
{
	loadObj(fname, uniqueID);
	calculateNormals();
}

void Reader::drawObj()
{
	int id;

	glPointSize(2.0); //Sets vertex draw size
	glNewList(this->uniqueID, GL_COMPILE); //Creates a GL display list to be executed (a series of commands that end at glEndList(); ); first argument is the name of the list, second is the mode; GL_COMPILE means the commands are simply compiled, not executed
	{
		glPushMatrix();
			glBegin(GL_TRIANGLE_STRIP);
			for (int i = 0; i < faceNumber; i++)
			{
				id = (int)faces[i].x;
				glNormal3d(normal[id].x, normal[id].y, normal[id].z);
				glVertex3f(this->vertices[(int)faces[i].x - 1].x, this->vertices[(int)faces[i].x - 1].y, this->vertices[(int)faces[i].x - 1].z);

				id = (int)faces[i].y;
				glNormal3d(normal[id].x, normal[id].y, normal[id].z);
				glVertex3f(this->vertices[(int)faces[i].y - 1].x, this->vertices[(int)faces[i].y - 1].y, this->vertices[(int)faces[i].y - 1].z);

				id = (int)faces[i].z;
				glNormal3d(normal[id].x, normal[id].y, normal[id].z);
				glVertex3f(this->vertices[(int)faces[i].z - 1].x, this->vertices[(int)faces[i].z - 1].y, this->vertices[(int)faces[i].z - 1].z);
			}
			glEnd();
		glPopMatrix();

	}glEndList();

	glCallList(this->uniqueID);
}


