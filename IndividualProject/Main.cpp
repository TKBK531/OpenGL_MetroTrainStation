#include <cstdlib>   // Include before GLUT to avoid redefinition issues
#include <GL/glut.h>
#include <iostream>


GLfloat camXInit = 0.0; GLfloat camYInit = 0.0; GLfloat camZInit = 0.0;
GLfloat sceRXInit = 0.0; GLfloat sceRYInit = 90.0; GLfloat sceRZInit = 0.0;
GLfloat sceTXInit = 0.0; GLfloat sceTYInit = 0.0; GLfloat sceTZInit = 0.0;

GLfloat openDoorAngle = 45; GLfloat openDoorZ = -0.05; GLfloat openDoorXInit = -0.4;
GLfloat closeDoorAngle = 0; GLfloat closeDoorZ = 0; GLfloat closeDoorXInit = -0.5;

GLfloat doorAngle = closeDoorAngle; GLfloat doorZ = closeDoorZ; GLfloat doorXInit = closeDoorXInit;

//variables to move the camera
GLfloat camX = camXInit; GLfloat camY = camYInit; GLfloat camZ = camZInit;

//variables to move the look at position
GLfloat lookX = 0.0; GLfloat lookY = 0.0; GLfloat lookZ = 0.0;

//variables to move the scene
GLfloat sceRX = sceRXInit; GLfloat sceRY = sceRYInit; GLfloat sceRZ = sceRZInit;
GLfloat sceTX = sceTXInit; GLfloat sceTY = sceTYInit; GLfloat sceTZ = sceTZInit;

////variables to move the objects
GLfloat objRX = 0.0; GLfloat objRY = 0.0; GLfloat objRZ = 0.0;
GLfloat objTX = 0.0; GLfloat objTY = 0.0; GLfloat objTZ = 0.0;

// Window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;



// Train and door variables
//GLfloat doorAngle = 0.0;
GLfloat doorX = -0.5;
GLfloat trainPosition = 0.0;
bool trainMovingForward = true;

// Function prototypes
void initOpenGL();
void display();
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void keyboardSpecial(int key, int x, int y);
void drawTrain();
void drawPlatform();
void setupLighting();
void animate(int);
void drawPillars();
void drawStationRoof();

// Main function
int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("3D Train Station");

    // Initialize OpenGL settings
    initOpenGL();

    // Register callback functions
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	glutTimerFunc(16, animate, 0);

    // Start the main loop
    glutMainLoop();
    return 0;
}

// Initialize OpenGL settings
void initOpenGL() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// Lighting setup
	GLfloat lightPos[] = { 1.0f, 3.0f, 2.0f, 1.0f };
	GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
}

// Set up the lighting for the scene
void setupLighting() {
    GLfloat lightPos[] = { 1.0f, 1.0f, 1.0f, 1.0f };  
    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
}

// Handle window resizing
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / (float)height, 0.01, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboardSpecial(int key, int x, int y) {
	if (key == GLUT_KEY_UP)
		camY += 0.2;

	if (key == GLUT_KEY_DOWN)
		camY -= 0.2;

	if (key == GLUT_KEY_LEFT)
		sceRY += 1;

	if (key == GLUT_KEY_RIGHT)
		sceRY -= 1;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'l')
		objRY += 1;

	if (key == 'r')
		objRY -= 1;

	if (key == 'Z')
		sceTZ += 1;

	if (key == 'z')
		sceTZ -= 1;

	if (key == 'a') {
		sceTX += 1;
		objTX -= 1;
	}

	if (key == 'd') {
		sceTX -= 1;
		objTX += 1;
	}

	if (key == 'w') {
		sceTZ += 1;
		objTZ -= 1;
	}

	if (key == 's') {
		sceTZ -= 1;
		objTZ += 1;
	}

	if (key == 'q') {
		sceTY += 1;
		objTY -= 1;
	}

	if (key == 'e') {
		sceTY -= 1;
		objTY += 1;
	}

	if (key == '6')
		lookX += 1;

	if (key == '4')
		lookX -= 1;

	if (key == '8')
		lookY += 1;

	if (key == '2')
		lookY -= 1;

	if (key == 'o') {
		doorAngle = openDoorAngle;
		doorZ = openDoorZ;
		doorXInit = openDoorXInit;
	}

	if (key == 'c') {
		doorAngle = closeDoorAngle;
		doorZ = closeDoorZ;
		doorXInit = closeDoorXInit;
	}


	if (key == '.') {
		lookX = 0;
		lookY = 0;
		lookZ = 0;

		camX = camXInit;
		camY = camYInit;
		camZ = camZInit;

		sceRX = sceRXInit;
		sceRY = sceRYInit;
		sceRZ = sceRZInit;

		sceTX = sceTXInit;
		sceTY = sceTYInit;
		sceTZ = sceTZInit;

		objRX = 0;
		objRY = 0;
		objRZ = 0;

		objTX = 0;
		objTY = 0;
		objTZ = 0;
	}

	if (key == '1')
		glEnable(GL_LIGHT0);

	if (key == '3')
		glDisable(GL_LIGHT0);

	if (key == '6')
		glShadeModel(GL_FLAT);

	if (key == '7')
		glShadeModel(GL_SMOOTH);

	glutPostRedisplay();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	// camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
	gluLookAt(0.0, 1.0 + camY, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// move the scene (all the rendered environment) using keyboard keys
	glTranslatef(sceTX, sceTY, sceTZ);
	glRotatef(sceRY, 0.0, 1.0, 0.0);

	drawPlatform();
	drawStationRoof();
	drawPillars();
	glPushMatrix();
	
	glTranslatef(0, -0.5, 1.5);
	drawTrain();
	glPopMatrix();

	glTranslatef(0, -0.5, -1.5);
	drawTrain();
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();

}

// Draw the train (to be developed)
void drawTrain() {
	glPushMatrix();
	glTranslatef(trainPosition, 0.5f, 0.0f);
	glColor3f(0.8f, 0.2f, 0.2f);
	glutSolidCube(1.0);

	// Draw doors on the train
	/*glPushMatrix();
	glTranslatef(-0.5f, 0.0f, -0.5f);
	glRotatef(doorAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(doorX, 0.0f, 0.0f);
	glColor3f(0.7f, 0.7f, 0.7f);
	glScalef(0.1f, 1.0f, 1.0f);
	glutSolidCube(1.0);
	glPopMatrix();*/

	glPopMatrix();
}

// Draw the platform (to be developed)
void drawPlatform() {
	glPushMatrix();
	glColor3f(0.6f, 0.6f, 0.6f);
	glScalef(6.0f, 0.1f, 2.0f);
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawStationRoof() {
	glPushMatrix();
	glColor3f(0.3f, 0.3f, 0.3f);
	glTranslatef(0.0f, 1.2f, 0.0f);
	glScalef(6.0f, 0.1f, 2.0f);
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawPillars() {
	glColor3f(0.5f, 0.5f, 0.5f);
	for (float i = -2.5f; i <= 2.5f; i += 2.5f) {
		glPushMatrix();
		glTranslatef(i, 0.6f, 0.9f);
		glScalef(0.1f, 1.2f, 0.1f);
		glutSolidCube(1.0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(i, 0.6f, -0.9f);
		glScalef(0.1f, 1.2f, 0.1f);
		glutSolidCube(1.0);
		glPopMatrix();
	}
}

void animate(int) {
	// Move train back and forth
	if (trainMovingForward) {
		trainPosition += 0.02;
		if (trainPosition > 3.0) trainMovingForward = false;
	}
	else {
		trainPosition -= 0.02;
		if (trainPosition < -3.0) trainMovingForward = true;
	}
	glutPostRedisplay();
	glutTimerFunc(16, animate, 0);
}