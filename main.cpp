////////////////////////////////////////////////////////////////
// main.cpp
//
// Kantapon Pornprasertsakul (2019).
////////////////////////////////////////////////////////////////

#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "getBMP.h"
#include "scene.h"
#include "lighting.h"
#include "Penquin.h"
#include "Obstracles.h"

// Global.
static int isAnimate = 1;
static int animationPeriod = (int) (1000.0f / 60.0f);
static float animationRatio = 0.0;
static float animateDiff = (60.0f / 1000.0f) * 2.0;
static float numGroundBox = 32.0;

// Services.
Scener sc;
Penquin penquin;
Obstracles obstracles = Obstracles(5);

// Drawing routine.
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    gluLookAt(0.0, 20.0, 30.0, 0.0, 10.0, 0.0, 0.0, 1.0, 0.0);

    sc.draw(animationRatio, numGroundBox);

    penquin.draw();

    // Draw obstacles that might not be opaque.
    obstracles.draw();

    glutSwapBuffers();
}

// Timer function.
void animate(int value)
{
    if (!isAnimate) return;

    animationRatio += animateDiff;
    if (animationRatio >= numGroundBox) animationRatio = 0.0;

    penquin.updateJump();
    obstracles.update(animationRatio, animateDiff, numGroundBox);
    if (obstracles.isHit(penquin.xPos, penquin.yPos, penquin.r)) {
        isAnimate = 0;
    }

    glutPostRedisplay();
    glutTimerFunc(animationPeriod, animate, 1);
}

// Initialization routine.
void setup()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST); // Enable depth testing.

    // Set lighting
    lightingSetup();

    // Set background.
    loadTextures();
    sc = Scener();

    // Set penquin.
    penquin = Penquin();

    // Start animation.
    animate(1);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-7.5, 7.5, -5.0, 5.0, 5.0, 300.0);

    glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyAction(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            exit(0);
        case ' ':
            if (isAnimate) isAnimate = 0;
            else {
                isAnimate = 1;
                animate(1);
            }
            break;
        default:
            break;
    }
}

// Callback routine for non-ASCII key entry.
void specialKeyAction(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) penquin.moveLeft();
    if (key == GLUT_KEY_RIGHT) penquin.moveRight();
    if (key == GLUT_KEY_UP) penquin.jump();
    glutPostRedisplay();
}

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
    glutKeyboardFunc(keyAction);
    glutSpecialFunc(specialKeyAction);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}
