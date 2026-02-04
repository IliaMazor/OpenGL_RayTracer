#pragma once
#include <glad/glad.h>

// ============ WINDOW CONSTANTS ============
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern const char* WINDOW_TITLE;

// ============ TIMING ============
extern float deltaTime;

// ============ CACHED UNIFORM LOCATIONS ============

// Light
extern GLint uLightSource;

// Plane
extern GLint uPlanePoint;
extern GLint uPlaneNormal;
extern GLint uPlaneColor;

// Sphere
extern GLint uSphereCenter;
extern GLint uSphereRadius;
extern GLint uSphereColor;
extern GLint uSphereReflectivity;

// Cylinder
extern GLint uCylinderCenter;
extern GLint uCylinderRadius;
extern GLint uCylinderHeight;
extern GLint uCylinderColor;

// Cube
extern GLint uCubeCenter;
extern GLint uCubeLength;
extern GLint uCubeColor;

// Shader program handle
extern GLuint shaderProgram;
