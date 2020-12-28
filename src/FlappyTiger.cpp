//
// Created by Tigermouthbear on 12/28/20.
//

#include "FlappyTiger.h"

#include <iostream>
#include <vector>
#include "game/StartScreen.h"

FlappyTiger::FlappyTiger() {
    // create window and open start screen
    window = new Window("FlappyTiger", 550, 700);
    window->setIcon((std::string(INSTALL_PREFIX) + "/resources/tigerbird.png").c_str());
    screen = static_cast<Screen*>(new StartScreen(this));
    window->setInputsCallback(screen);
}

void FlappyTiger::run() {
    // create font renderer
    fontRenderer = new FontRenderer(std::string(INSTALL_PREFIX) + "/resources/font.ttf");
    if(!fontRenderer->init()) std::cout << "FLAPPYTIGER: Failed to load FontRenderer!" << std::endl;

    // load mesh
    std::vector<Point> points = {
            {-1, -1, 0, 0, 1},
            {-1, 1, 0, 0, 0},
            {1, 1, 0, 1, 0},
            {1, -1, 0, 1, 1},
    };
    std::vector<unsigned int> indices = { 0, 1, 2, 2, 0, 3 };
    mesh = new StaticMesh(&points, &indices);

    // load textures
    skyTexture = new Texture("sky.jpg");
    birdTexture = new Texture("tigerbird.png");
    pipeTexture = new Texture("pipe.png");
    skyTexture->load();
    birdTexture->load();
    pipeTexture->load();

    // load shader
    shader = new Shader("2d.vert", "2d_textured.frag");
    shaderModelUniform = new Uniform("model", shader);

    // fps counter
    double fpsLastTime = 0;
    double frameCount = 0;

    // render loop
    while(!window->shouldClose()) {
        // update delta time
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        // update fps counter
        double currentTime = glfwGetTime();
        frameCount++;
        if(currentTime - fpsLastTime >= 1.0 ) {
            fps = frameCount;
            frameCount = 0;
            fpsLastTime += 1.0;
        }

        // update viewport
        double width = (double) window->getHeight() / 700 * 550;
        glViewport((double) window->getWidth() / 2 - width / 2, 0, width, window->getHeight());

        glfwPollEvents(); // poll glfw

        screen->render(deltaTime);

        window->swapBuffers();
    }
}

float FlappyTiger::getTickDelta() const {
    return deltaTime;
}

int FlappyTiger::getFPS() const {
    return (int) fps;
}

int FlappyTiger::getHighScore() const {
    return highScore;
}

void FlappyTiger::setHighScore(int score) {
    highScore = score;
}

void FlappyTiger::shutdown() {
    glfwTerminate();
}

void FlappyTiger::openScreen(Screen* screenIn) {
    delete screen;
    this->screen = screenIn;
    this->window->setInputsCallback(screenIn);
}

FlappyTiger::~FlappyTiger() {
    delete window;
    delete mesh;
    delete fontRenderer;
    delete skyTexture;
    delete birdTexture;
    delete pipeTexture;
    delete shader;
    delete shaderModelUniform;
}
