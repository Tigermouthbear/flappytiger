//
// Created by Tigermouthbear on 12/28/20.
//

#include "StartScreen.h"

#include "IngameScreen.h"

StartScreen::StartScreen(FlappyTiger* flappyTiger): Screen(flappyTiger) {
}

void StartScreen::render(float delta) {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // render background
    flappyTiger->shader->attach();
    flappyTiger->skyTexture->bind();
    glUniformMatrix4fv(flappyTiger->shaderModelUniform->getID(), 1, GL_FALSE, glm::value_ptr(glm::mat4(1)));
    flappyTiger->mesh->render();

    // render bird
    // and translate based on waiting animation
    glm::mat4 model(1);
    model = glm::translate(model, glm::vec3(0, std::sin(animTime) / 20, 0));
    animTime += 0.0628;
    if(animTime > 9999) animTime = 0;
    model = glm::scale(model, glm::vec3((double) 40 / 550, (double) 40 / 700, 0));
    glUniformMatrix4fv(flappyTiger->shaderModelUniform->getID(), 1, GL_FALSE, glm::value_ptr(model));
    flappyTiger->birdTexture->bind();
    flappyTiger->mesh->render();

    std::string text = "FlappyTiger";
    flappyTiger->fontRenderer->drawString(
            text,
            0 - flappyTiger->fontRenderer->getStringWidth(text, 0.005F) / 2,
            0.6F,
            0.005F,
            glm::vec3(1, 0.4, 0)
    );

    text = "by Tigermouthbear";
    flappyTiger->fontRenderer->drawString(
            text,
            0 - flappyTiger->fontRenderer->getStringWidth(text, 0.002F) / 2,
            0.3F,
            0.002F,
            glm::vec3(0, 0, 0)
    );

    text = "Press Enter to Begin";
    flappyTiger->fontRenderer->drawString(
            text,
            0 - flappyTiger->fontRenderer->getStringWidth(text, 0.002F) / 2,
            -1 + flappyTiger->fontRenderer->getFontHeight(0.002F) * 1.5F,
            0.002F,
            glm::vec3(0, 0, 0)
    );
}

void StartScreen::handleMouse(Window* window, double mouseX, double mouseY) {
}

void StartScreen::handleKeys(Window* window, int key, int code, int action, int mode) {
    if(action == GLFW_PRESS) {
        switch(key) {
            case GLFW_KEY_ESCAPE:
                window->close();
                break;

            case GLFW_KEY_KP_ENTER:
            case GLFW_KEY_ENTER:
                flappyTiger->openScreen(new IngameScreen(flappyTiger));
                break;
        }
    }
}
