//
// Created by Tigermouthbear on 12/28/20.
//

#ifndef FLAPPYTIGER_INGAMESCREEN_H
#define FLAPPYTIGER_INGAMESCREEN_H

#include "../render/window/Screen.h"

class IngameScreen: public Screen {
private:
    const static int WAITING = 0;
    const static int PLAYING = 1;
    const static int GAME_OVER_ANIM = 2;

    struct Bird {
        double X;
        double Y;
        double motionY;
        double radius;
        double mass;
    };

    struct Pipe {
        double X{};
        double openingY{};
        double width = 100;
        double openingHeight = 200;
        bool counted = false;

        Pipe(int x, double y) {
            X = x;
            openingY = y;
        }
    };

    int gameState = WAITING;
    int score = 0;
    double animTime = 0;
    Bird bird = { 550 / 2.0,  700 / 2.0, 0, 40, 20 };
    std::vector<Pipe> pipes;

    void drawPipe(double x, double openingY, double width, double openingHeight);
    void reset();

public:
    explicit IngameScreen(FlappyTiger* flappyTiger);

    void render(float delta) override;
    void handleMouse(Window* window, double mouseX, double mouseY) override;
    void handleKeys(Window* window, int key, int code, int action, int mode) override;

    ~IngameScreen() override = default;
};


#endif //FLAPPYTIGER_INGAMESCREEN_H
