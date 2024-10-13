/*
  Dreiecke
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <glew.h>
#include <freeglut.h>
#include <FreeImage.h>

GLuint loadShaders(const char* vertexFilePath,
	const char* fragmentFilePath,
	const char* geometryFilePath,
	const char* tesscontrolFilePath,
	const char* tessevaluationFilePath,
	const char* computeFilePath);
GLint height = 100, width = 100;
enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition, vColor };
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 42;
GLuint program;


void skale(GLfloat vertices[][2], GLuint size)
{
	GLfloat factor = 0.0;
	for (GLuint i=0; i<size; i++) {
		if (vertices[i][0] > factor) factor = vertices[i][0];
		if (vertices[i][1] > factor) factor = vertices[i][1];
	}

	for (GLuint i = 0; i < size; i++) {
		vertices[i][0] /= factor;
		vertices[i][1] /= factor;
		vertices[i][0] -= 0.5;
		vertices[i][1] -= 0.5;
	}
	return;

}

void init(void)
{
	printf("\n%s", (char*)glGetString(GL_RENDERER));
	printf("\n%s", (char*)glGetString(GL_VERSION));
	printf("\n%s\n", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	program = loadShaders("Programme/Dreiecke.vs", "Programme/Dreiecke.fs", "", "", "", "");
	glUseProgram(program);
	glGenBuffers(NumBuffers, Buffers);
	glGenVertexArrays(NumVAOs, VAOs);
	GLfloat vertices[NumVertices][2] = {
		{0.0, 0.0}, {3.0, 0.0}, {0.0, 15.0}, //P1 P2 P3
		{3.0, 0.0}, {0.0, 15.0}, {3.0, 15.0}, 
		{3.0, 7.5}, {10.0, 7.5}, // x P4
		{10.0, 0.0}, {10.0, 15.0 }, 
		{ 10.0, 15.0 }, { 18.0, 15.0 }, 
		{ 15.0, 15.0 }, { 15.0, 0.0 }, { 18.0, 0.0 }, //x P5
		{ 18.0, 0.0 }, { 18.0, 15.0 }, { 15.0, 15.0 }, 
		{ 22.0, 0.0 }, { 22.0, 15.0 }, //P6
		{ 22.0, 15.0 }, { 26.0, 15.0 }, //x P9
		{ 22.0, 0.0 }, { 25.0, 0.0 }, { 31.0, 15.0 }, //P6 P7 P8
		{ 31.0, 15.0 }, { 34.0, 15.0 }, { 25.0, 0.0 },
		{ 30.0, 0.0 }, { 39.0, 15.0 },	{ 33.0, 0.0 }, //P10
		{ 39.0, 15.0 }, { 42.0, 15.0 }, { 33.0, 0.0 }, 
		{ 30.0, 0.0 }, { 33.0, 0.0 }, 
		{ 30.0, 0.0 }, { 39.0, 15.0 },
		{ 39.0, 15.0 }, { 42.0, 15.0 },	
		{ 42.0, 15.0 }, { 33.0, 0.0 } 
	}; // Setzt Punkte für Randlinien.
	skale(vertices, NumVertices);
	glBindVertexArray(VAOs[Triangles]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(vPosition);
}

void display(void)
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAOs[Triangles]);
	glVertexAttrib3f(vColor, 0, 0, 0); //Farbe 100 Rot, 101 Pink, 001 Blau, 111 Weiß, 110 Gelb, 010 Grün
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawArrays(GL_LINES, 6, 6);
	glDrawArrays(GL_TRIANGLES, 12, 6);

	glDrawArrays(GL_LINES, 18, 4);
	glDrawArrays(GL_TRIANGLES, 22, 6);

	glVertexAttrib3f(vColor, 249.0/255.0, 155.0/255.0, 28.0/255.0);
	glDrawArrays(GL_TRIANGLES, 28, 6);
	glVertexAttrib3f(vColor, 0, 0, 0);
	glDrawArrays(GL_LINES, 34, 8);
	glFlush();
}

void reshape(int w, int h) {
	width = w;
	height = h;
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(4, 5);  // (4,2) (3,3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	//GLUT_COMPATIBILITY_PROFILE
	glutCreateWindow(argv[0]);
	glewExperimental = GL_TRUE;
	if (glewInit()) printf("Error");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
}
