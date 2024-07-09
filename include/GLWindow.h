#pragma once
#ifndef GLWINDOW_H
#define GLWINDOW_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "GLCamera.h"
#include "Constants.h"

class GLWindow
{

public:

    GLWindow();
    ~GLWindow();  
    
    static GLWindow* instance;

    void init();
    GLFWwindow* getWindow();
    std::shared_ptr<GLCamera> getCamera();
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void processInput();

    float lastX;
    float lastY;
    bool firstMouse;

private:

    void createHints();
    int createWindow();
    // Resize de la pantalla
      
    static void framebuffer_size_callback_static(GLFWwindow* window, int width, int height);
    static void mouse_callback_static(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback_static(GLFWwindow* window, double xoffset, double yoffset);
    static void mouse_button_callback_static(GLFWwindow* window, int button, int action, int mods);
    
    std::shared_ptr<GLCamera> camera;
    GLFWwindow* window;
    bool mouseButtonPressed;
};

#endif // !GLWINDOW_H