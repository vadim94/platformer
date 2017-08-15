#include "GameStage.h"
#include "GameEngine.h"

#include "SDL_events.h"
#include "SDL_main.h"
#include "SDL.h"

#include "core/oxygine.h"
#include "KeyEvent.h"
#include "DebugActor.h"

#include "GroundActor.h"
#include "GreySquareActor.h"
#include "PauseMenuActor.h"
#include "Direction.h"

#include "EndGameEvent.h"
#include "MoveEvent.h"

GameStage::GameStage(const oxygine::Vector2& size) : oxygine::Stage(true),
    game_level_(new GameLevelActor({ size.x * kPixel, size.y * kPixel }))
{
    addChild(game_level_);
    setSize(size);
    CreateAndAddSquare();
    CreateAndAddAllGround();
    CreateAndAddMenu();
}

void GameStage::CreateAndAddSquare()
{
    spGreySquareActor actor = new GreySquareActor(PhysicalObject::Point(50 * kPixel, 50 * kPixel));
    addEventListener(oxygine::KeyEvent::KEY_DOWN, [this, actor](oxygine::Event* event)
    {
        if (IsPaused() || IsEnded())
            return;

        switch (dynamic_cast<oxygine::KeyEvent*>(event)->data->keysym.scancode)
        {
        case SDL_SCANCODE_LEFT:
            actor->MoveHorizontally(Direction::kLeft);
            break;
        case SDL_SCANCODE_RIGHT:
            actor->MoveHorizontally(Direction::kRight);
            break;
        case SDL_SCANCODE_SPACE:
            actor->Jump();
            break;
        }
    });

    addEventListener(oxygine::KeyEvent::KEY_UP, [this, actor](oxygine::Event* event)
    {
        const auto scancode = dynamic_cast<oxygine::KeyEvent*>(event)->data->keysym.scancode;
        if (scancode == SDL_SCANCODE_LEFT || scancode == SDL_SCANCODE_RIGHT)
        {
            actor->StopMoveHorizontally();
        }
    });

    game_level_->addChild(actor);
}

void GameStage::CreateAndAddAllGround()
{
    GameEngine::GetInstance().Reset();

    CreateAndAddGround(PhysicalObject::Point(50 * kPixel, 500 * kPixel));
    CreateAndAddGround(PhysicalObject::Point(160 * kPixel, 550 * kPixel));
    CreateAndAddGround(PhysicalObject::Point(270 * kPixel, 500 * kPixel));
    CreateAndAddGround(PhysicalObject::Point(380 * kPixel, 550 * kPixel));
    CreateAndAddGround(PhysicalObject::Point(710 * kPixel, 500 * kPixel));
    CreateAndAddGround(PhysicalObject::Point(820 * kPixel, 550 * kPixel));
    CreateAndAddGround(PhysicalObject::Point(50 * kPixel, 50 * kPixel));
    CreateAndAddGround(PhysicalObject::Point(160 * kPixel, 100 * kPixel));
}

void GameStage::CreateAndAddGround(const PhysicalObject::Point& point)
{
    spGroundActor groundActor = new GroundActor(point);
    game_level_->AddAndExtend(groundActor);
}

void GameStage::CreateAndAddMenu()
{
    pause_menu_ = new PauseMenuActor();
    addEventListener(oxygine::KeyEvent::KEY_DOWN, [pauseMenu = pause_menu_](oxygine::Event* event)
    {
        if (dynamic_cast<oxygine::KeyEvent*>(event)->data->keysym.scancode == SDL_SCANCODE_ESCAPE)
            pauseMenu->Toggle();
    });
    addChild(pause_menu_);

    end_game_ = new EndGameActor();
    addEventListener(EndGameEvent::EVENT, [end_game_ = end_game_](oxygine::Event* event)
    {
        end_game_->Show();
        oxygine::Stage::instance->removeAllEventListeners();
    });
    addChild(end_game_);

    addEventListener(MoveEvent::EVENT, [this](oxygine::Event* event)
    {
        MoveEvent* move_event = dynamic_cast<MoveEvent*>(event);
        GameEngine::GetInstance().CheckGraySquareActorLocation(
            move_event->moved_object_, move_event->old_position_, move_event->new_position_);
        game_level_->ScrollToShow(move_event->moved_object_->GetLocation());
    });
}

bool GameStage::IsPaused()
{
    return pause_menu_->IsShown();
}

bool GameStage::IsEnded()
{
    return end_game_->IsShown();
}