//
// Created by Tigermouthbear on 12/28/20.
//

#include "Window.h"

#include "../stb_image.h"

Window::Window(const char* name, GLint width, GLint height) {
    // initialize GLFW
    if(!glfwInit()) {
        printf("GLFW initializion failed!\n");
        glfwTerminate();
        return;
    }

    // push settings to glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // set version to
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // dont allow backwards compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // allow forward compatibility

    // create window
    glfwWindow = glfwCreateWindow(width, height, name, nullptr, nullptr);

    // make sure window was created
    if(!glfwWindow) {
        printf("GLFW window creation failed!\n");
        glfwTerminate();
        return;
    }

    // set buffer vars
    glfwGetFramebufferSize(glfwWindow, &bufferWidth, &bufferHeight);
    glfwSetFramebufferSizeCallback(glfwWindow, sizeCallback);

    // set context for GLEW
    glfwMakeContextCurrent(glfwWindow);

    // set callbacks for user input
    glfwSetKeyCallback(glfwWindow, handleKeys);
    glfwSetCursorPosCallback(glfwWindow, handleMouse);

    // allow modern extension features
    glewExperimental = GL_TRUE;

    // initialize GLEW, if fail destroy window
    if(glewInit() != GLEW_OK) {
        printf("GLEW initialization failed!\n");
        glfwDestroyWindow(glfwWindow);
        glfwTerminate();
        return;
    }

    // setup viewport
    glViewport(0, 0, bufferWidth, bufferHeight);

    // set user pointer so we can get the window on callbacks
    glfwSetWindowUserPointer(glfwWindow, this);
}

void Window::setIcon(const char* path) {
    GLFWimage images[1];
    images[0].pixels = stbi_load(path, &images[0].width, &images[0].height, 0, 4);
    glfwSetWindowIcon(glfwWindow, 1, images);
    stbi_image_free(images[0].pixels);
}

// handles key presses
void Window::handleKeys(GLFWwindow* glfwWinfdow, int key, int code, int action, int mode) {
    auto* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWinfdow));
    window->inputsCallback->handleKeys(window, key, code, action, mode);
}

// gets the change in mouse
void Window::handleMouse(GLFWwindow* glfwWindow, double mouseX, double mouseY) {
    auto* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
    window->inputsCallback->handleMouse(window, mouseX, mouseX);
}

void Window::sizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::swapBuffers() {
    glfwSwapBuffers(glfwWindow);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(glfwWindow);
}

int Window::getWidth() {
    int width;
    glfwGetWindowSize(glfwWindow, &width, nullptr);
    return width;
}

int Window::getHeight() {
    int height;
    glfwGetWindowSize(glfwWindow, nullptr, &height);
    return height;
}

double Window::getAspectRatio() {
    return (double) getWidth() / (double) getHeight();
}

void Window::setInputsCallback(InputsCallback* inputsCallback) {
    this->inputsCallback = inputsCallback;
}

void Window::close() {
    glfwSetWindowShouldClose(glfwWindow, GL_TRUE);
}
