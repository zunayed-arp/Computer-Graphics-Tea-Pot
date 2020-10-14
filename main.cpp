#include<windows.h>
#include "GL/glut.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>


using namespace std;

// Globals variables
GLuint color_counter = 0, angle=0;
GLfloat light_X_position = 0.0f; //horizontal light
GLfloat light_Y_position = 0.0f; // vertical light

// This is the list of points (3D vectors)
// This function is called whenever a "Normal" key press is received.
void keyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 27: // Escape key
        exit(0);
        break;
    case 'c':
        // add code to change color here
		color_counter += 1;
		glShadeModel(GL_SMOOTH);
		if(color_counter>5)
            color_counter=0;
        break;
    case 'r':
        angle+=6;
        break;
    default:
        cout << "Unhandled key press " << key << "." << endl;
    }
	// this will refresh the screen so that the user sees the color change
    glutPostRedisplay();
}
// This function is called whenever a "Special" key press is received.
// Right now, it's handling the arrow keys.
void specialFunc( int key, int x, int y )
{
    switch ( key )
    {
    case GLUT_KEY_UP:
        // add code to change light position
		light_Y_position += 0.5f;
		break;
    case GLUT_KEY_DOWN:
        // add code to change light position
		light_Y_position += -0.5f;
		break;
    case GLUT_KEY_LEFT:
        // add code to change light position
		light_X_position += -0.5f;
		break;
    case GLUT_KEY_RIGHT:
        // add code to change light position
		light_X_position += 0.5f;
		break;
    }
	// this will refresh the screen so that the user sees the light position
    glutPostRedisplay();
}
// This function is responsible for displaying the object.
void drawScene(void)
{
    int i;
    // Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Rotate the image
    glMatrixMode( GL_MODELVIEW );  // Current matrix affects objects positions
    glLoadIdentity();              // Initialize to the identity
    // Position the camera at [0,0,5], looking at [0,0,0],
    // with [0,1,0] as the up direction.
    gluLookAt(0.0, 0.0, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    // Set material properties of object
	// Here are some colors you might use - feel free to add more
    GLfloat different_color[6][4] = { {0.5, 0.5, 0.9, 1.0},
                                 {0.3, 0.5, 0.5, 1.0},
                                 {0.5, 0.5, 0.9, 1.0},
                                 {0.5, 0.8, 0.4, 1.0},
                                 {1.0, 0.0, 1.0, 1.0},
                                 {0.3, 0.6, 0.9, 1.0}};
	// Here we use the first color entry as the diffuse color
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, different_color[color_counter]);
	// Define specular color and shininess // rgba //a=alpha
    GLfloat specColor[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat shininess[] = {100.0};
	// Note that the specular color and shininess can stay constant
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    // Set light properties
    // Light color (RGBA)
    GLfloat Lt0diff[] = {1.0,1.0,1.0,1.0};
    // Light position
	GLfloat Lt0pos[] = {1.0f + light_X_position, 1.0f + light_Y_position, 5.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
    glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);
    glRotatef(angle,0,1,0);
	// This GLUT method draws a teapot.  You should replace
	// it with code which draws the object you loaded.
	glutSolidTeapot(1.0);
    // Dump the image to the screen.
    glutSwapBuffers();
}
// Initialize OpenGL's rendering modes
void initRendering()
{
    glEnable(GL_DEPTH_TEST);   // Depth testing must be turned on
    glEnable(GL_LIGHTING);     // Enable lighting calculations
    glEnable(GL_LIGHT0);       // Turn on light #0.
    glShadeModel(GL_SMOOTH);
}
// Called when the window is resized
// w, h - width and height of the window in pixels.
void reshapeFunc(int w, int h)
{
    // Always use the largest square viewport possible
    if (w > h) {
        glViewport((w - h) / 2, 0, h, h);
    } else {
        glViewport(0, (h - w) / 2, w, w);
    }
    // Set up a perspective view, with square aspect ratio
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 50 degree fov, uniform aspect ratio, near = 1, far = 100
    gluPerspective(50.0, 1.0, 1.0, 100.0); // field angle,near,far direction
}
void loadInput()
{
	// load the OBJ file here
}
// Main routine.
// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char** argv )
{
    loadInput();
    glutInit(&argc,argv);
    // We're going to animate it, so double buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    // Initial parameters for window position and size
    glutInitWindowPosition( 600, 60 );
    glutInitWindowSize( 360, 360 );
    glutCreateWindow("Tea Pot Assignment 16201102 ");
    // Initialize OpenGL parameters.
    initRendering();
    // Set up callback functions for key presses
    glutKeyboardFunc(keyboardFunc); // Handles "normal" ascii symbols
    glutSpecialFunc(specialFunc);   // Handles "special" keyboard keys
     // Set up the callback function for resizing windows
    glutReshapeFunc( reshapeFunc );
    // Call this whenever window needs redrawing
    glutDisplayFunc( drawScene );
    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop( );
    return 0;	// This line is never reached.

    }
