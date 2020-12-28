//
// Created by Tigermouthbear on 12/28/20.
//

#ifndef FLAPPYTIGER_SCREEN_H
#define FLAPPYTIGER_SCREEN_H

class Screen;

#include "InputsCallback.h"
#include "../../FlappyTiger.h"



class FlappyTiger;

class Screen: public InputsCallback {
protected:
    FlappyTiger* flappyTiger;
public:
    explicit Screen(FlappyTiger* flappyTiger) {
        this->flappyTiger = flappyTiger;
    }

    virtual void render(float partialTicks) = 0;

    virtual ~Screen() = default;
};


#endif //FLAPPYTIGER_SCREEN_H
