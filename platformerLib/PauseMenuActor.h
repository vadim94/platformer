#pragma once

#include "ColorRectSprite.h"

#include "vector"

#include "math/color.h"

#include "ButtonAlignerActor.h"



DECLARE_SMART(PauseMenuActor, spPauseMenuActor);
class PauseMenuActor : public oxygine::ColorRectSprite
{
public:
    PauseMenuActor();
    void Toggle();
    bool IsShown() const;

private:
    void Show();
    void Hide();
    void AddButtons();
    void SetupMenuVisualParameters();

private:
    static const oxygine::Color kBackgroundColor;

    spButtonAlignerActor button_formatter_;
};

