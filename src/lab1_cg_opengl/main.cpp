#define GL_GLEXT_PROTOTYPES

#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

void init()
{
	glewInit();
}

void display()
{
	glClearColor(0.17f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glFinish();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
  switch(key){
  case 27:
    exit(0);
    break;
  }
}

int main(int argc, char* argv[]){


  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(600, 600);
  glutCreateWindow("GPGPU Lab1");
	
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);

  init();
 
  glutMainLoop();

  return(0);
}
