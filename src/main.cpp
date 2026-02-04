#include "config.h"
#include "global.h"
#include "shader.h"
#include "screen_quad.h"
#include "scene.h"
#include "camera.h"
#include "input.h"

// Global objects
static ScreenQuad* screenQuad = nullptr;
static Scene* scene = nullptr;
static Camera* camera = nullptr;
static GLFWwindow* g_window = nullptr;

void init() {
    // Compile shaders
    shaderProgram = InitShader("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");
    if (shaderProgram == 0) {
        std::cerr << "Failed to initialize shaders" << std::endl;
        return;
    }
    glUseProgram(shaderProgram);

    // Create screen quad
    screenQuad = new ScreenQuad();

    // Initialize camera
    camera = new Camera();
    camera->cacheUniforms(shaderProgram);
    camera->sendUniforms();

    // Initialize scene (no longer handles camera)
    scene = new Scene();
    scene->cacheUniforms(shaderProgram);
    scene->sendUniforms();

    // Initialize input system
    Input::init(g_window, camera);
}

void render() {
    screenQuad->draw();
}

void cleanup() {
    delete screenQuad;
    delete scene;
    delete camera;
    glDeleteProgram(shaderProgram);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    // Update screen size in camera
    if (camera != nullptr) {
        camera->screenSize = glm::vec2(width, height);
        camera->sendUniforms();
    }
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Store window reference for init()
    g_window = window;

    // Initialize rendering
    init();

    // Timing
    float lastFrame = 0.0f;

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Calculate delta time
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Process input
        Input::processInput(window, deltaTime);

        // Update camera uniforms (position may have changed)
        camera->sendUniforms();

        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    cleanup();
    glfwTerminate();
    return 0;
}
