////////////////////////////////////////////////////////////////
// flawlessUnicorn.cpp
//
// This program draws a unicorn that roams around a circular road.
//
// Interaction:
// Press space to toggle between animation on and off.
// Press the up/down arrow keys to speed up/slow down animation.
// Press the x, X, y, Y, z, Z keys to rotate the scene.
//
// Kantapon Pornprasertsakul.
////////////////////////////////////////////////////////////////

#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

// Globals.
static int animationPeriod = 1000.0f / 30.0f; // Time interval between frames.


// Drawing routine.
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(30.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

    // Auto calculate normal for standard object
    glEnable(GL_AUTO_NORMAL); // Enable automatic normal calculation.
    glutSwapBuffers();
}

// Timer function.
void animate(int value)
{
    glutPostRedisplay();
    glutTimerFunc(animationPeriod, animate, 1);
}

void lightingSetup() {
    // Turn on OpenGL lighting.
    glEnable(GL_LIGHTING);

    // Light property vectors.
    float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDifAndSpec0[] = { 0.4, 0.4, 0.4, 1.0 };
    float lightDifAndSpec1[] = { 1.0, 1.0, 0.0, 1.0 };
    float a = 0.1;
    float globAmb[] = { a, a, a, 1.0 };
    float lightPos0[] = { 0.0, 0.0, 1.0, 1.0 };

    // Light0 properties.
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    // Light1 properties.
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec1);

    glEnable(GL_LIGHT0); // Enable particular light source.
    glEnable(GL_LIGHT1); // Enable particular light source.
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint

    // Material property vectors.
    float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
    float matShine[] = { 50.0 };
    float matDif[] = { 0.6, 0.6, 0.6, 1.0 };
    // Material properties.
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matDif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);

    // Enable color material mode.
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

// Initialization routine.
void setup()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST); // Enable depth testing.

    // Set lighting
    lightingSetup();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-7.5, 7.5, -5.0, 5.0, 5.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

//// Keyboard input processing routine.
//void keyInput(unsigned char key, int x, int y)
//{
//}
//
//// Callback routine for non-ASCII key entry.
//void specialKeyInput(int key, int x, int y)
//{
//    if (key == GLUT_KEY_DOWN) animationPeriod += 5;
//    if (key == GLUT_KEY_UP) if (animationPeriod > 5) animationPeriod -= 5;
//    glutPostRedisplay();
//}

// Main routine.
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Penquin the Adventure");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
//    glutKeyboardFunc(keyInput);
//    glutSpecialFunc(specialKeyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}
