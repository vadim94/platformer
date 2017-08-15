#include "EndGameActor.h"
#include "GameStage.h"
#include "MainMenuStage.h"

#include "Stage.h"
#include "Clock.h"
#include "core/oxygine.h"
#include "DebugActor.h"

const oxygine::Color EndGameActor::kBackgroundColor = oxygine::Color(255, 0, 0, 100);

EndGameActor::EndGameActor()
{
    setVisible(false);
    setSize(oxygine::getStage()->getSize());
    setColor(kBackgroundColor);

    spButtonAlignerActor end_game_stage_buttons = new ButtonAlignerActor();
    AddButtons(end_game_stage_buttons);
    Align(end_game_stage_buttons);
}

void EndGameActor::AddButtons(spButtonAlignerActor end_game_stage_buttons)
{
    end_game_stage_buttons->AddButton("Restart")
        ->addEventListener(oxygine::TouchEvent::CLICK, [this](oxygine::Event*)
    {
        oxygine::Stage::instance = new GameStage(getSize());
        oxygine::DebugActor::show();
    });
    end_game_stage_buttons->AddButton("Main menu")
        ->addEventListener(oxygine::TouchEvent::CLICK, [](oxygine::Event*)
    { 
        oxygine::Stage::instance = new MainMenuStage(oxygine::core::getDisplaySize());
        oxygine::DebugActor::show();
    });
}

void EndGameActor::Align(spButtonAlignerActor end_game_stage_buttons)
{
    const oxygine::Vector2 button_formatter_top_left = (getSize() - end_game_stage_buttons->getSize()) / 2;
    end_game_stage_buttons->setPosition(button_formatter_top_left);
    addChild(end_game_stage_buttons);
}

void EndGameActor::Show()
{
    oxygine::getStage()->getClock()->pause();
    setVisible(true);
}

bool EndGameActor::IsShown() const
{
    return getVisible();
}