#include "global.h"

// Window constants
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const char* WINDOW_TITLE = "Ray Tracer";

// Timing
float deltaTime = 0.0f;

GLint uLightSource = -1;

GLint uPlanePoint = -1;
GLint uPlaneNormal = -1;
GLint uPlaneColor = -1;

GLint uSphereCenter = -1;
GLint uSphereRadius = -1;
GLint uSphereColor = -1;
GLint uSphereReflectivity = -1;

GLint uCylinderCenter = -1;
GLint uCylinderRadius = -1;
GLint uCylinderHeight = -1;
GLint uCylinderColor = -1;

GLint uCubeCenter = -1;
GLint uCubeLength = -1;
GLint uCubeColor = -1;

GLuint shaderProgram = 0;
