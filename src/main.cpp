//
// Created by Tigermouthbear on 12/28/20.
//
#define STB_IMAGE_IMPLEMENTATION
#include "FlappyTiger.h"

int main() {
    auto* flappyTiger = new FlappyTiger();
    flappyTiger->run();
    FlappyTiger::shutdown();
    delete flappyTiger;
}
