#include <GL/glut.h>
#include <cmath>

float sphereAngle = 0.0;   // Rotation angle for the sphere
float cubeAngle = 0.0;     // Rotation angle for the cube
float satelliteAngle = 0.5; // Rotation angle for the satellite
float cubeTranslateX = 2.5; // Initial x-coordinate for the cube
float cubeTranslateZ = 0.0; // Initial z-coordinate for the cube
float cubeTranslateSpeed = 0.1;  // Translation speed for the cube
float cubeScale = 1.0;     // Initial scale factor for the cube
float cubePathRadius = 2.5; // Initial radius of the cube's path
bool moveLeft = false;
bool moveRight = false;

// Camera parameters
float eyeX = 0.0, eyeY = 0.0, eyeZ = 5.0; // Initial eye position
float centerX = 0.0, centerY = 0.0, centerZ = 0.0; // Initial center position
float upX = 0.0, upY = 1.0, upZ = 0.0; // Initial up direction

void drawSphere() {
    GLfloat mat_ambient[] = {0.0, 1.0, 0.0, 1.0}; // Green ambient material
    GLfloat mat_diffuse[] = {0.0, 0.5, 0.0, 1.0}; // Dark green diffuse material
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

    glPushMatrix();
    glRotatef(sphereAngle, 0.0, 1.0, 0.0);  // Rotate around the y-axis
    glutSolidSphere(1.0, 50, 50);  // Draw a solid sphere with radius 1.0
    glPopMatrix();
}

void drawCube() {
    GLfloat mat_ambient[] = {1.0, 0.0, 0.0, 1.0}; // Red ambient material
    GLfloat mat_diffuse[] = {0.5, 0.0, 0.0, 1.0}; // Dark red diffuse material
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

    glPushMatrix();
    glTranslatef(cubePathRadius * cos(cubeTranslateZ), 0.0, cubePathRadius * sin(cubeTranslateZ));  // Translate along circular path
    glRotatef(cubeAngle, 0.0, 1.0, 0.0);  // Rotate around the y-axis
    glScalef(cubeScale, cubeScale, cubeScale);  // Scale the cube
    glutSolidCube(0.5);  // Draw a solid cube with side length 0.5
    glPopMatrix();
}

void drawSatellite() {
    GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0}; // Gray ambient material
    GLfloat mat_diffuse[] = {0.7, 0.7, 0.7, 1.0}; // Light gray diffuse material
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

    glPushMatrix();
    glRotatef(satelliteAngle, 0.0, 0.0, 1.0); // Rotate around the y-axis
    glTranslatef(0.5, 0.0, 0.5); // Position relative to the sphere
    
    
    glRotatef(60,1,0,0);
    //body
    glPushMatrix();
    glColor3f(0.2,0.2,0.2);
    glScaled(1,0.6,1);
    glTranslatef(3.0,0,0.0);
    glutSolidCube(0.4);
    glPopMatrix();

    //Solar Panels

    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(3,0,0.0);
    glScaled(3.7,0.0,1);
    glutSolidCube(0.4);
    glPopMatrix();
    glPushMatrix();
    glColor3f(0.2,0.1,0.1);
    glTranslatef(3.0,0,-0.4);
    glScaled(0.5,0.5,0.5);
    glutSolidSphere(0.3,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.2,0.2,0.1);
    glTranslatef(3.0,0,0.4);
    glScaled(0.4,0.4,0.3);
    glutSolidTorus(0.3,0.2,20,20);
    glPopMatrix();

    glPopMatrix(); // Pop the satellite transformation
}

void drawSun() {
    GLfloat mat_ambient[] = {1.0, 1.0, 0.0, 1.0}; // Yellow ambient material for the sun
    GLfloat mat_diffuse[] = {1.0, 1.0, 0.0, 1.0}; // Yellow diffuse material for the sun
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

    glPushMatrix();
    glTranslatef(-5.0, 3.0, -5.0); // Position the sun at the top-left corner
    glutSolidSphere(1.0, 50, 50);  // Draw a solid sphere with radius 1.0 for the sun
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(eyeX, eyeY, eyeZ,  // Eye position
              centerX, centerY, centerZ,  // Look at position
              upX, upY, upZ);  // Up direction

    // Draw the sun
    drawSun();

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Set light properties
    GLfloat light_position[] = {-5.0, 3.0, -5.0, 1.0}; // Position of the sun
    GLfloat light_ambient[] = {0.2, 0.2, 0.2, 1.0}; // Ambient light
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0}; // Diffuse light
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    // Draw other objects
    drawSphere();
    drawCube();
    drawSatellite();

    glutSwapBuffers();
}

void update(int value) {
    if (moveLeft) {
        cubeTranslateZ -= cubeTranslateSpeed;
    } else if (moveRight) {
        cubeTranslateZ += cubeTranslateSpeed;
    }

    // Update the x-coordinate for the cube based on circular path
    cubeTranslateX = cubePathRadius * cos(cubeTranslateZ);

    // Update rotation angles
    sphereAngle += 2.0;
    if (sphereAngle > 360.0) {
        sphereAngle -= 360.0;
    }

    cubeAngle += 2.0;
    if (cubeAngle > 360.0) {
        cubeAngle -= 360.0;
    }

    satelliteAngle += 2.0;
    if (satelliteAngle > 360.0) {
        satelliteAngle -= 360.0;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);  // Set the timer for the next update
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            moveLeft = true;
            moveRight = false;
            break;
        case 'd':
            moveLeft = false;
            moveRight = true;
            break;
        case '+':
            cubeTranslateSpeed += 0.01;
            break;
        case '-':
            cubeTranslateSpeed -= 0.01;
            if (cubeTranslateSpeed < 0.01) {
                cubeTranslateSpeed = 0.01;
            }
            break;
        case 'w':
            cubeScale += 0.1;
            break;
        case 's':
            cubeScale -= 0.1;
            if (cubeScale < 0.1) {
                cubeScale = 0.1;
            }
            break;
        case 'q':
            cubePathRadius += 0.1;
            break;
        case 'e':
            cubePathRadius -= 0.1;
            if (cubePathRadius < 0.1) {
                cubePathRadius = 0.1;
            }
            break;
        case 'i':
            eyeY += 0.1; // Move the camera upwards
            break;
        case 'k':
            eyeY -= 0.1; // Move the camera downwards
            break;
        case 'j':
            eyeX -= 0.1; // Move the camera to the left
            break;
        case 'l':
            eyeX += 0.1; // Move the camera to the right
            break;
        case 'u':
            eyeZ -= 0.1; // Move the camera closer
            break;
        case 'o':
            eyeZ += 0.1; // Move the camera farther
            break;
        default:
            break;
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            moveLeft = false;
            break;
        case 'd':
            moveRight = false;
            break;
        default:
            break;
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Set background color to white
    glEnable(GL_DEPTH_TEST);  // Enable depth testing

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Set light properties
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0}; // Light position
    GLfloat light_ambient[] = {0.2, 0.2, 0.2, 1.0}; // Ambient light
    GLfloat light_diffuse[] = {0.7, 0.7, 0.7, 1.0}; // Diffuse light
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0}; // Specular light
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // Set material properties
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0}; // Material specular
    GLfloat mat_shininess[] = {50.0}; // Material shininess
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // Set up perspective projection
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 2.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(eyeX, eyeY, eyeZ,  // Eye position
              centerX, centerY, centerZ,  // Look at position
              upX, upY, upZ);  // Up direction

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Satellite Rotation");
    glutInitWindowSize(800, 600);
    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);  // Set the initial timer
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    init();
    glutMainLoop();
    return 0;
}



