
#include <GLUT/glut.h>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int currentLight = 0;
// 0 = Red, 1 = Yellow, 2 = Green

bool paused = false;
int remainingTime = 5;

void drawCircle(float x, float y, float radius,
                float r, float g, float b) {

    glColor3f(r, g, b);

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(x, y);

    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.14159f * i / 100;

        glVertex2f(
            x + radius * cos(angle),
            y + radius * sin(angle)
        );
    }

    glEnd();
}

void drawText(float x, float y, string text) {

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);

    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);

    // Background
    glColor3f(0.15f, 0.15f, 0.15f);

    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(500, 0);
        glVertex2f(500, 600);
        glVertex2f(0, 600);
    glEnd();

    // Traffic signal body
    glColor3f(0.05f, 0.05f, 0.05f);

    glBegin(GL_QUADS);
        glVertex2f(180, 150);
        glVertex2f(320, 150);
        glVertex2f(320, 510);
        glVertex2f(180, 510);
    glEnd();

    // Red light
    if (currentLight == 0)
        drawCircle(250, 440, 45, 1, 0, 0);
    else
        drawCircle(250, 440, 45, 0.25f, 0, 0);

    // Yellow light
    if (currentLight == 1)
        drawCircle(250, 330, 45, 1, 1, 0);
    else
        drawCircle(250, 330, 45, 0.25f, 0.25f, 0);

    // Green light
    if (currentLight == 2)
        drawCircle(250, 220, 45, 0, 1, 0);
    else
        drawCircle(250, 220, 45, 0, 0.25f, 0);

    // Pole
    glColor3f(0.5f, 0.5f, 0.5f);

    glBegin(GL_QUADS);
        glVertex2f(235, 50);
        glVertex2f(265, 50);
        glVertex2f(265, 150);
        glVertex2f(235, 150);
    glEnd();

    // Information
    drawText(160, 560, "TRAFFIC LIGHT SIMULATION");

    string status;

    if (currentLight == 0)
        status = "STOP - RED";
    else if (currentLight == 1)
        status = "WAIT - YELLOW";
    else
        status = "GO - GREEN";

    drawText(190, 100, status);

    drawText(190, 70,
        "Time: " + to_string(remainingTime) + " sec");

    if (paused)
        drawText(205, 30, "PAUSED");

    glutSwapBuffers();
}

// Automatic light switching
void timer(int value) {

    if (!paused) {

        remainingTime--;

        if (remainingTime <= 0) {

            currentLight = (currentLight + 1) % 3;

            if (currentLight == 0)
                remainingTime = 5;
            else if (currentLight == 1)
                remainingTime = 2;
            else
                remainingTime = 5;
        }
    }

    glutPostRedisplay();

    glutTimerFunc(1000, timer, 0);
}

// Keyboard controls
void keyboard(unsigned char key, int x, int y) {

    if (key == ' ') {
        paused = !paused;
    }

    if (key == 'r' || key == 'R') {
        currentLight = 0;
        remainingTime = 5;
        paused = false;
    }

    if (key == 27) {
        exit(0);
    }

    glutPostRedisplay();
}

// OpenGL initialization
void init() {

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, 500, 0, 600);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE | GLUT_RGB
    );

    glutInitWindowSize(500, 600);

    glutInitWindowPosition(200, 100);

    glutCreateWindow(
        "Traffic Light Simulation - OpenGL"
    );

    init();

    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);

    glutTimerFunc(1000, timer, 0);

    glutMainLoop();

    return 0;
}
