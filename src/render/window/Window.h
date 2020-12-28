//
// Created by Tigermouthbear on 12/28/20.
//

#ifndef FLAPPYTIGER_WINDOW_H
#define FLAPPYTIGER_WINDOW_H

#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "InputsCallback.h"

class Window {
private:
    GLFWwindow* glfwWindow;
    InputsCallback* inputsCallback = nullptr;

    GLint bufferWidth, bufferHeight;

    static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
    static void handleMouse(GLFWwindow* window, double xPos, double yPos);
    static void sizeCallback(GLFWwindow* window, int width, int height);

public:
    Window(const char* name, GLint width, GLint height);

    void setIcon(const char* path);

    void swapBuffers();

    GLfloat getBufferWidth() const { return bufferWidth; }

    GLfloat getBufferHeight() const { return bufferHeight; }

    bool shouldClose();

    int getWidth();

    int getHeight();

    double getAspectRatio();

    void setInputsCallback(InputsCallback* inputsCallback);

    void close();
};


#endif //FLAPPYTIGER_WINDOW_H
