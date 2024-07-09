#include "GLWindow.h"

#include <iostream>

GLWindow* GLWindow::instance = nullptr;

GLWindow::GLWindow() {
    window = nullptr;

    lastX = SCR_WIDTH / 2.0f;
    lastY = SCR_HEIGHT / 2.0f;
    firstMouse = true;
    camera = std::make_shared<GLCamera>(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), YAW, PITCH);
    mouseButtonPressed = false;

    instance = this;
}

GLWindow::~GLWindow(){

}

void GLWindow::init()
{
    createHints();
    createWindow();
}

GLFWwindow* GLWindow::getWindow()
{
    return window;
}

std::shared_ptr<GLCamera> GLWindow::getCamera()
{
    return camera;
}

void GLWindow::createHints() {
    // Crear hints para que openGL sepa la version y el perfil
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int GLWindow::createWindow() {
    //Crear una ventana
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpengl", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);
    //Llamada a la funciona callback del resize de la pantalla
    glfwSetFramebufferSizeCallback(window, GLWindow::framebuffer_size_callback_static);
    glfwSetCursorPosCallback(window, mouse_callback_static);
    glfwSetScrollCallback(window, scroll_callback_static);
    glfwSetMouseButtonCallback(window, mouse_button_callback_static);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Carga todos los punteros openGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    return 0;
}

void GLWindow::processInput()
{
    // Si se pulsa ESC se cierra la ventana
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (mouseButtonPressed) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera->ProcessKeyboard(Camera_Movement::FORWARD, camera->deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera->ProcessKeyboard(Camera_Movement::BACKWARD, camera->deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera->ProcessKeyboard(Camera_Movement::LEFT, camera->deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera->ProcessKeyboard(Camera_Movement::RIGHT, camera->deltaTime);
    } 
}

void GLWindow::framebuffer_size_callback_static(GLFWwindow* window, int width, int height)
{
    if (instance)
    {
        instance->framebuffer_size_callback(window, width, height);
    }
}

void GLWindow::mouse_callback_static(GLFWwindow* window, double xpos, double ypos)
{
    if (instance)
    {
        instance->mouse_callback(window, xpos, ypos);
    }
}

void GLWindow::scroll_callback_static(GLFWwindow* window, double xoffset, double yoffset)
{
    if (instance)
    {
        instance->scroll_callback(window, xoffset, yoffset);
    }
}

void GLWindow::mouse_button_callback_static(GLFWwindow* window, int button, int action, int mods)
{
    if (instance)
    {
        instance->mouse_button_callback(window, button, action, mods);
    }
}

void GLWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void GLWindow::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    if(mouseButtonPressed)
        camera->ProcessMouseMovement(xoffset, yoffset);
}

void GLWindow::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera->ProcessMouseScroll(static_cast<float>(yoffset));
}

void GLWindow::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        mouseButtonPressed = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        mouseButtonPressed = false;
    }
}
