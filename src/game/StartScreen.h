//
// Created by Tigermouthbear on 12/28/20.
//

#ifndef FLAPPYTIGER_STARTSCREEN_H
#define FLAPPYTIGER_STARTSCREEN_H

#include "../render/window/Screen.h"

class StartScreen: public Screen {
private:
    double animTime = 0;

public:
    explicit StartScreen(FlappyTiger* flappyTiger);

    void render(float delta) override;
    void handleMouse(Window* window, double mouseX, double mouseY) override;
    void handleKeys(Window* window, int key, int code, int action, int mode) override;

    ~StartScreen() override = default;
};


#endif //FLAPPYTIGER_STARTSCREEN_H
