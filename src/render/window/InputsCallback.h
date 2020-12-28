//
// Created by Tigermouthbear on 12/28/20.
//

#ifndef FLAPPYTIGER_INPUTSCALLBACK_H
#define FLAPPYTIGER_INPUTSCALLBACK_H

class InputsCallback;

#include "Window.h"

class Window;

class InputsCallback {
public:
    virtual void handleKeys(Window* window, int key, int code, int action, int mode) = 0;

    virtual void handleMouse(Window* window, double mouseX, double mouseY) = 0;
};

#endif //FLAPPYTIGER_INPUTSCALLBACK_H
