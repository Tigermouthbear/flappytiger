//
// Created by Tigermouthbear on 12/28/20.
//

#ifndef FLAPPYTIGER_FLAPPYTIGER_H
#define FLAPPYTIGER_FLAPPYTIGER_H

#include "render/window/Window.h"
#include "render/window/Screen.h"
#include "render/buffer/StaticMesh.h"
#include "render/FontRenderer.h"
#include "render/buffer/Texture.h"

class FlappyTiger {
private:
    Screen* screen;

    int highScore = 0;
    double fps = 0;

    // delta time vars
    float deltaTime = 0.0F;
    float lastTime = 0.0F;

public:
    Window* window;

    FlappyTiger();

    void run();
    static void shutdown();
    void openScreen(Screen* screenIn);

    float getTickDelta() const;
    int getFPS() const;
    int getHighScore() const;
    void setHighScore(int score);

    // rendering stuff
    StaticMesh* mesh{};
    FontRenderer* fontRenderer{};
    Texture* skyTexture;
    Texture* birdTexture;
    Texture* pipeTexture;
    Shader* shader;
    Uniform* shaderModelUniform;

    ~FlappyTiger();
};


#endif //FLAPPYTIGER_FLAPPYTIGER_H
