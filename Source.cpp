#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#define D2R 0.01745329

// State of Some Keys
bool aKey = false, wKey = false, sKey = false, dKey = false;
bool leftKey = false, rightKey = false, upKey = false, downKey = false;

float camX = 0, camY = 22, camZ = 44;


// 3D Text with a Vector Font
void text(const char *string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
}

// 2D Text with a Bitmap Font
void print(int x, int y, void *font, const char *string, ...)
{
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
}

void circle(float x, float y, float r) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 10) {
		glVertex2f(x + r * cos(i * D2R), y + r * sin(i * D2R));
	}
	glEnd();
}



void display() {
	glClearColor(1, 1, 1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-camX, -camY, -camZ); // Inverse of Camera Transformation (View)

	

	int xAxis = -15;
	int zAxis = -20;
	glRotatef(5, 1, 0, 0);
	for (int i = 4; i > 0; i--) {
		for (int i = 4; i > 0; i--) {
			glPushMatrix();
			glTranslatef(xAxis, 10, zAxis);
			glScalef(10, 3, 10);
			
			glColor3f(0.7, 0.7, 1);
			glutSolidCube(1);
			glColor3f(0.5, 0.5, 0.8);
			glutWireCube(1);
			glPopMatrix();

			xAxis += 10;

		}
		xAxis = -15;
		zAxis += 10;
	}
	

	// Draw Cylinder
	// base radius: 1, height: 2, resolution: 20, 20
	glPushMatrix();
	glTranslatef(0, 0, -40);
	glColor3f(0.7, 0.2, 0.2);
	glRotatef(90, 1, 0, 0);

	glutSolidCylinder(8, 3, 20, 20);
	glColor3f(0.5, 0.0, 0.0);
	glutWireCylinder(8, 3, 20, 20);
	glPopMatrix();


	// Draw Cylinder
	// base radius: 1, height: 2, resolution: 20, 20
	
	glPushMatrix();
	glTranslatef(0, 20, -40);
	glColor3f(0.9, 0.8, 0.8);	
	glRotatef(90, 1, 0, 0);

	glutSolidCylinder(2, 20, 20, 20);
	glColor3f(0.5, 0.0, 0.0);
	glutWireCylinder(2, 20, 20, 20);
	glPopMatrix();


	// Draw Cylinder
	// base radius: 1, height: 2, resolution: 20, 20

	glPushMatrix();
	glTranslatef(0, 22, -40);
	glColor3f(0.9, 0.8, 0.8);
	glRotatef(-90, 0, 1, 0);

	glutSolidCylinder(2, 20, 20, 20);
	glColor3f(0.5, 0.0, 0.0);
	glutWireCylinder(2, 20, 20, 20);
	glPopMatrix();



	glPushMatrix();
	glTranslatef(1, 22, -50);
	glRotatef(90, 1, 0, 0);
	glColor3f(1, 0.5, 0.5);
	glutSolidSphere(3, 20, 20);
	glColor3f(0.8, 0.3, 0.3);
	glutWireSphere(3, 20, 20);
	glPopMatrix();


	// Draw Cylinder
// base radius: 1, height: 2, resolution: 20, 20

	glPushMatrix();
	glTranslatef(-16, 22, -40);
	glColor3f(0.9, 0.8, 0.8);
	glRotatef(-90, 0, 1, 0);

	glutSolidCylinder(1, 10, 20, 20);
	glColor3f(1, 0.0, 0.0);
	glutWireCylinder(1, 10, 20, 20);
	glPopMatrix();

	glutSwapBuffers();
}

void onResize(int w, int h) {
	// printf("Resize : %d %d\n", w, h);
	glViewport(0, 0, w, h); // use whole window

	// Update Projection Matrix in the Rendering Pipeline
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0f, 1.0f * w / h, 0.1f, 200.0f);

	glMatrixMode(GL_MODELVIEW);
}

void onClick(int button, int state, int x, int y) {
	// printf("Click : %d %d (%d %d)\n", button, state, x, y);
}

void onMoveDown(int x, int y) {
	// printf("MoveDown : %d %d\n", x, y);
}

void onMove(int x, int y) {
	// printf("Move : %d %d\n", x, y);
}

void onWheel(int button, int dir, int x, int y) {
	// printf("Wheel: %d\n", dir);
}

void onSpecialKeyDown(int key, int x, int y) {
	// printf("SpecialKeyDown: %d\n", key);

	switch (key) {
	case GLUT_KEY_LEFT: leftKey = true; break;
	case GLUT_KEY_RIGHT: rightKey = true; break;
	case GLUT_KEY_DOWN: downKey = true; break;
	case GLUT_KEY_UP: upKey = true; break;
	}
}
void onSpecialKeyUp(int key, int x, int y) {
	// printf("SpecialKeyUp: %d\n", key);

	switch (key) {
	case GLUT_KEY_LEFT: leftKey = false; break;
	case GLUT_KEY_RIGHT: rightKey = false; break;
	case GLUT_KEY_DOWN: downKey = false; break;
	case GLUT_KEY_UP: upKey = false; break;
	}
}

void onKeyDown(unsigned char key, int x, int y) {
	// printf("ASCII-Key-Down: %c (%d)\n", key, key);
	if (key == 27) exit(0);

	switch (key) {
	case 'a': aKey = true; break;
	case 'd': dKey = true; break;
	case 's': sKey = true; break;
	case 'w': wKey = true; break;
	}
}

void onKeyUp(unsigned char key, int x, int y) {
	// printf("ASCII-Key-Up: %c (%d)\n", key, key);
	switch (key) {
	case 'a': aKey = false; break;
	case 'd': dKey = false; break;
	case 's': sKey = false; break;
	case 'w': wKey = false; break;
	}
}

void gameLoop(int v) {
	glutTimerFunc(16, gameLoop, 0);

	glutPostRedisplay();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(1200, 800);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_MULTISAMPLE);
	glutCreateWindow("Freeglut");

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);
	/* Mouse related Events are registered */
	glutMouseFunc(onClick);
	glutMotionFunc(onMoveDown);
	glutPassiveMotionFunc(onMove);
	glutMouseWheelFunc(onWheel);

	/* Keyboard related Events */
	glutSpecialFunc(onSpecialKeyDown);
	glutSpecialUpFunc(onSpecialKeyUp);

	glutKeyboardFunc(onKeyDown);
	glutKeyboardUpFunc(onKeyUp);

	// Timer  setTimeout(fn, period)
	// frame locking. ( 16 ms --> 60 fps )
	glutTimerFunc(16, gameLoop, 0);

	glutMainLoop();

	return 0;
}