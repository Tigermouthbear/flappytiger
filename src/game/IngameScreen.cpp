//
// Created by Tigermouthbear on 12/28/20.
//

#include "IngameScreen.h"

#include "StartScreen.h"

IngameScreen::IngameScreen(FlappyTiger* flappyTiger): Screen(flappyTiger) {
    // add pipes
    pipes.push_back({ 600, (double) (std::rand() % 426 + 100) });
    pipes.push_back({ 925, (double) (std::rand() % 426 + 100) });
}

void IngameScreen::render(float delta) {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // attach shader and create model
    flappyTiger->shader->attach();
    glm::mat4 model(1);

    // render background/sky
    flappyTiger->skyTexture->bind();
    glUniformMatrix4fv(flappyTiger->shaderModelUniform->getID(), 1, GL_FALSE, glm::value_ptr(model));
    flappyTiger->mesh->render();

    // calculate next position and velocity for bird if playing
    if(gameState == PLAYING) {
        double A = 3.14 * bird.radius * bird.radius / (10000);
        double Fy = -0.5 * 0.47 * A * 1.22 * bird.motionY * bird.motionY * bird.motionY / std::abs(bird.motionY);
        Fy = std::isnan(Fy) ? 0 : Fy;
        double ay = -9.81 + (Fy / bird.mass);
        bird.motionY += ay * flappyTiger->getTickDelta() * 3/2;
        bird.Y += (int) (bird.motionY * flappyTiger->getTickDelta() * 100);

        // if hit floor, game over
        if(bird.Y < (double) bird.radius / std::sqrt(2)) {
            gameState = GAME_OVER_ANIM;
            return;
        }
    } else if(gameState == GAME_OVER_ANIM) {
        if(bird.Y - bird.radius > -3) {
            bird.Y -= 10;
            bird.motionY = -100;
        }
        else if(animTime++ > 1500*flappyTiger->getTickDelta()) {
            gameState = WAITING;
            reset();
        }
    }

    // calculate rotation and clamp
    float angle = (float) bird.motionY / 12.0F;
    angle = angle < 0 ? std::max(-1.57F, angle) : std::min(1.0F, angle);

    // if playing render and move pipes
    for(auto& i: pipes) {
        Pipe pipe = i;
        drawPipe(pipe.X, pipe.openingY, pipe.width, pipe.openingHeight);

        // only move pipes and check for collisions if playing
        if(gameState != PLAYING) continue;

        // if pipe is behind bird and offscreen
        if(pipe.X + pipe.width / 2 < 0) {
            pipe.X = 600;
            pipe.openingY = std::rand() % 426 + 100;
            pipe.counted = false;
        }
        else pipe.X -= (int) (200 * flappyTiger->getTickDelta());

        // count score
        if(!pipe.counted && pipe.X + pipe.width < bird.X - bird.radius) {
            score++;
            pipe.counted = true;

            // update high score
            if(score > flappyTiger->getHighScore()) flappyTiger->setHighScore(score);
        }

        // check for collision
        double hitbox = bird.radius / std::sqrt(2) - 3;
        if(bird.X + bird.radius > pipe.X
           && bird.X - hitbox < pipe.X + pipe.width / 2
           && (bird.Y + hitbox > pipe.openingY + pipe.openingHeight
               || bird.Y - hitbox < pipe.openingY)) {
            gameState = GAME_OVER_ANIM;
            break;
        }

        i = pipe;
    }

    // render score
    std::string sscore = std::to_string(score);
    flappyTiger->fontRenderer->drawString(sscore, 0 - flappyTiger->fontRenderer->getStringWidth(sscore, 0.005F) / 2, 0.5, 0.005F, glm::vec3(1, 1, 1));

    // prepare bird render
    model = glm::translate(model, glm::vec3((double) (bird.X - 275) / 275, (double) (bird.Y - 350) / 350, 0));

    // translate based on waiting animation
    if(gameState == WAITING) {
        model = glm::translate(model, glm::vec3(0, std::sin(animTime) / 20, 0));
        animTime += 0.0628;
        if(animTime > 9999) animTime = 0;

        // render start indicator
        std::string text = "Press SPACE to fly";
        flappyTiger->fontRenderer->drawString(text, -flappyTiger->fontRenderer->getStringWidth(text, 0.001F) / 2, 0 - flappyTiger->fontRenderer->getFontHeight(0.001F) * 5, 0.001F);
    }

    // render bird
    flappyTiger->shader->attach();
    model = glm::scale(model, glm::vec3(bird.radius / 550, bird.radius / 700, 0));
    model = glm::rotate(model, angle, glm::vec3(0, 0, 1));
    glUniformMatrix4fv(flappyTiger->shaderModelUniform->getID(), 1, GL_FALSE, glm::value_ptr(model));
    flappyTiger->birdTexture->bind();
    flappyTiger->mesh->render();

    // render highscore
    std::string shighscore = "High Score: " + std::to_string(flappyTiger->getHighScore());
    flappyTiger->fontRenderer->drawString(shighscore, 1 - flappyTiger->fontRenderer->getStringWidth(shighscore, 0.002F) - 0.01F, 1 - flappyTiger->fontRenderer->getFontHeight(0.002F) - 0.01F, 0.002F);

    // render fps mark
    flappyTiger->fontRenderer->drawString(std::to_string(flappyTiger->getFPS()) + " FPS", -1 + 0.01F, 1 - flappyTiger->fontRenderer->getFontHeight(0.002F) - 0.01F, 0.002F);
}

void IngameScreen::drawPipe(double x, double openingY, double width, double openingHeight) {
    flappyTiger->pipeTexture->bind();
    glm::mat4 model(1);
    model = glm::translate(model, glm::vec3((double) (x - 275) / 275, -1 + openingY / (double) 350 - 0.75, 0));
    model = glm::scale(model, glm::vec3(width / 550, 0.75, 0));
    glUniformMatrix4fv(flappyTiger->shaderModelUniform->getID(), 1, GL_FALSE, glm::value_ptr(model));
    flappyTiger->mesh->render();
    model = glm::mat4(1);
    model = glm::translate(model, glm::vec3((double) (x - 275) / 275, -1 + (openingY + openingHeight) / (double) 350 + 0.75, 0));
    model = glm::scale(model, glm::vec3(width / 550, 0.75, 0));
    model = glm::rotate(model, 3.14F, glm::vec3(0, 0, 1));
    glUniformMatrix4fv(flappyTiger->shaderModelUniform->getID(), 1, GL_FALSE, glm::value_ptr(model));
    flappyTiger->mesh->render();
}

void IngameScreen::reset() {
    gameState = WAITING;

    // reset score
    score = 0;

    // reset anim time
    animTime = 0;

    // reset pipes
    pipes.clear();
    pipes.push_back({ 600, (double) (std::rand() % 426 + 100) });
    pipes.push_back({ 925, (double) (std::rand() % 426 + 100) });

    // reset bird
    bird = { 550 / 2.0,  700 / 2.0, 0, 40, 20 };
}

void IngameScreen::handleMouse(Window* window, double mouseX, double mouseY) {
}

void IngameScreen::handleKeys(Window* window, int key, int code, int action, int mode) {
    if(action == GLFW_PRESS) {
        if(code == glfwGetKeyScancode(GLFW_KEY_ESCAPE)) window->close();
        else if(code == glfwGetKeyScancode(GLFW_KEY_SPACE)) {
            if(gameState == WAITING) {
                gameState = PLAYING;
                animTime = 0; // make sure animation timer is reset
            }
            if(gameState == PLAYING) bird.motionY = 6.5;
        }
    }
}
