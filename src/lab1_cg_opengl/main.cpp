#define GL_GLEXT_PROTOTYPES

#include <GL/glew.h>
#include <GL/glut.h>
#include <Cg/cg.h>
#include <Cg/cgGL.h>
#include <iostream>
#include <ctime>

using namespace std;

GLuint textureID;
float dt = 0;
CGprogram vertexProgram;
CGprogram fragmentProgram;
CGparameter LightDir;
CGparameter TextureShift;

void init() {
	glewInit();

	CGcontext shaderContext = cgCreateContext(); // árnyaló kontextus

	CGprofile vertexProf = cgGLGetLatestProfile(CG_GL_VERTEX);
	cgGLEnableProfile(vertexProf);

	vertexProgram = cgCreateProgramFromFile(shaderContext, CG_SOURCE, "lab1.cg",
			vertexProf, "vs", NULL);

	if (vertexProgram == 0) {
		cerr << "!!!!CG_ERROR: Unable to build vertex program.." << endl;
		const char* comM_PIlerError = cgGetLastListing(shaderContext);
		if (comM_PIlerError)
			cerr << comM_PIlerError << endl;
		else
			cerr << "File not found?" << endl;
	}

	cgGLLoadProgram(vertexProgram); 	// GPU-ra töltés

	CGprofile fragmentProf = cgGLGetLatestProfile(CG_GL_FRAGMENT);
	cgGLEnableProfile(fragmentProf);

	CGprogram fragmentProgram = cgCreateProgramFromFile(shaderContext,
			CG_SOURCE, "lab1.cg", fragmentProf, "fs", NULL);

	if (fragmentProgram == 0) {
		cerr << "!!!!CG_ERROR: Unable to build fragment program.." << endl;
		const char* comM_PIlerError = cgGetLastListing(shaderContext);
		if (comM_PIlerError)
			cerr << comM_PIlerError << endl;
		else
			cerr << "File not found?" << endl;
	}

	cgGLLoadProgram(fragmentProgram);	// GPU-ra töltés

	LightDir = cgGetNamedParameter(vertexProgram, "lightdir");
	TextureShift = cgGetNamedParameter(fragmentProgram, "shift");

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	int textureSize = 8;
	GLubyte* pixelData = new GLubyte[textureSize * textureSize * 4];
	for (int i = 0; i < textureSize; i++)
		for (int j = 0; j < textureSize; j++) {
			pixelData[j * textureSize * 4 + i * 4] = pixelData[j * textureSize
					* 4 + i * 4 + 1] =
					pixelData[j * textureSize * 4 + i * 4 + 2] = pixelData[j
							* textureSize * 4 + i * 4 + 3] = (i + j) % 2 * 255;
		}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureSize, textureSize, 0,
	GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
	delete pixelData;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void drawMyMesh(float x, float y) {
	glPushMatrix();
	glTranslatef(x, y, 0);

	glNormal3f(0, 0, 1);
	glBegin(GL_TRIANGLES);

	glColor3f(1, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.5f, -0.5f, 0);

	glColor3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5f, -0.5f, 0);

	glColor3f(0, 0, 1);
	glTexCoord2f(0.5, 1);
	glVertex3f(0, 0.5f, 0);

	glEnd();

	glPopMatrix();
}

void display() {
	glClearColor(0.17f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 0.01, 100); //(aspect = 1)

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 1, 2, 0, 0, 0, 0, 1, 0);

	cgGLSetParameter3f(LightDir, 10, 20, 30);

	static float shift = 0;
	shift += dt * 0.1f;
	cgGLSetParameter2f(TextureShift, shift, 2 * shift);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	drawMyMesh(-0.5, -0.5);

	glutSolidSphere(0.15, 20, 20);

	static float rot = 0;
	rot += dt * 500;
	glRotatef(rot, 1, 1, 0);
	glTranslatef(0.5, 0.5, 0);
	glutSolidTeapot(0.2);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	glFinish();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'r':
		glutPostRedisplay();
		break;
	}
}

void idle() {
	static bool startup = true;
	if (startup) {
		glutPostRedisplay();
		startup = false;
	}

	static clock_t currentTime;
	currentTime = clock();
	static clock_t lastTime = currentTime;

	dt = (float) (currentTime - lastTime) / (float) CLOCKS_PER_SEC;

	if (dt < 0.1) {
		glutPostRedisplay();
		lastTime = currentTime;
	}
}

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutCreateWindow("GPGPU Lab1");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

	init();

	glutMainLoop();

	return 0;
}
