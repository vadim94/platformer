#pragma once
#include "Stage.h"

#include "ButtonAlignerActor.h"

class MainMenuStage : public oxygine::Stage
{
public:
    MainMenuStage(const oxygine::Vector2& size);

private:
    void AddButtons(spButtonAlignerActor main_menu_buttons);
    void Align(spButtonAlignerActor main_menu_buttons);
};

