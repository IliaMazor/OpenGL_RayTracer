#include "config.h"
#include "triangle_mesh.h"
#include "scene.h"

int main() {
    std::ifstream file;
    std::stringstream bufferdLines;
    std::string line;

    file.open("src/shaders/vertex.txt");
    





    generateWindow();
    return 0;
}

unsigned int make_shader(const std::string& file_path, const std::string& fragment_filepath){
    std::vector<unsigned int> modules;
    modules.push_back(make_module(file_path, GL_VERTEX_SHADER));
    modules.push_back(make_module(fragment_filepath, GL_FRAGMENT_SHADER));

    unsigned int shader= glCreateProgram();
    for (unsigned int shader_module : modules){
        glAttachShader(shader, shader_module);
    }
    glLinkProgram(shader);

    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if(!success){
        char errorLog[1024];
        glGetProgramInfoLog(shader, 1024, NULL, errorLog);
        std::cout << "ERROR::SHADER::LINKING_FAILED\n" << errorLog << std::endl;
        return 0;
    }

    for (unsigned int shader_module : modules){
        glDeleteShader(shader_module);
    }

    return shader;

}


unsigned int make_module(const std::string& file_path, unsigned int type){
    std::ifstream file;
    std::stringstream bufferdLines;
    std::string line;

    file.open(file_path);

    if(!file.is_open()){
        std::cout << "Failed to open file: " << file_path << std::endl;
        return 0;
    }
    
    
    while(std::getline(file, line)){
        //std::cout << line << std::endl;
        bufferdLines << line << "\n";
    }



    std::string shaderSource = bufferdLines.str();
    const char* shaderSrc = shaderSource.c_str();
    bufferdLines.str(""); //clear the buffer
    file.close();  

    unsigned int shaderModule = glCreateShader(type);
    glShaderSource(shaderModule, 1, &shaderSrc, NULL);
    glCompileShader(shaderModule);

    int success;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
    if(!success){
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << errorLog << std::endl;
        return 0;
    }

    return shaderModule;
}


void generateWindow(){
    //window initialization
    glfwInit(); // Initialize the GLFW library
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Set the major version of OpenGL to 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Set the minor version of OpenGL to 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Use the core profile

    GLFWwindow* window= glfwCreateWindow(800,800, "my window", NULL, NULL);
    if (window == NULL) {
        glfwTerminate(); // Terminate GLFW if window creation failed
        return;
    }
    glfwMakeContextCurrent(window); // Make the window's context current


    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate(); // Terminate GLFW if GLAD initialization failed
        return;
    }
    
    glViewport(0,0,800,800); // Set the viewport dimensions
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Set the framebuffer size callback
    
    TriangleMesh* triangleMesh= new TriangleMesh();

    unsigned int shader = make_shader("src/shaders/vertex.txt", "src/shaders/fragment.txt");

    Scene scene;
    glUseProgram(shader);
    scene.sendUniforms(shader);

    // int w,h;
    // glfwGetFramebufferSize(window, &w, &h); // Get the framebuffer size
    // glViewport(0,0,w,h);
    
    //render loop
    while(!glfwWindowShouldClose(window)) {
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  // teal-ish color
        // glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

        // glUseProgram(shader);
        triangleMesh->draw();
        glfwSwapBuffers(window); // Swap front and back buffers
        glfwPollEvents(); // Poll for and process events
    }


    //std:: cout << "Hello, World!" << std::endl;B
    glDeleteProgram(shader); // Delete the shader program
    delete triangleMesh; // Free the triangle mesh
    glfwTerminate(); // Terminate GLFW
}


// void ray_trace(unsigned int shader)
// {
//     // get uniform locations
//     int eyeLoc = glGetUniformLocation(shader, "eye");
//     int screenLoc = glGetUniformLocation(shader, "screenSize");
//     int lLoc = glGetUniformLocation(shader, "L");
//     int rLoc = glGetUniformLocation(shader, "R");
//     int bLoc = glGetUniformLocation(shader, "B");
//     int tLoc = glGetUniformLocation(shader, "T");
//     int nLoc = glGetUniformLocation(shader, "N");

//     // set values (do this after glUseProgram)
//     glUseProgram(shader);
//     glUniform3f(eyeLoc, 0.0f, 0.0f, 60.0f);      // same as your Processing eye
//     glUniform2f(screenLoc, 800.0f, 800.0f);
//     glUniform1f(lLoc, -10.0f);
//     glUniform1f(rLoc, 10.0f);
//     glUniform1f(bLoc, -10.0f);
//     glUniform1f(tLoc, 10.0f);
//     glUniform1f(nLoc, 16.0f);

// }


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  