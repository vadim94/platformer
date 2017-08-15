#include "GameEngine.h"
#include "Direction.h"

#include "EndGameEvent.h"
#include "Stage.h"

static const PhysicalObject::SpeedVector kZeroSpeedVector{ Speed(0), Speed(0) };
static const PhysicalObject::AccelerationVector kZeroAccelerationVector{ Acceleration(0), Acceleration(0) };

GameEngine::GameEngine()
{
}

void GameEngine::RegistrateObject(PhysicalObject* actor)
{
    ground_actors_.push_back(actor);
}

void GameEngine::CheckGraySquareActorLocation(PhysicalObject* actor,
    const PhysicalObject::Point& old_location,
    const PhysicalObject::Point& new_location)
{
    Direction horisontal_direction = Direction::kNotChanged;
    Direction vertical_direction = Direction::kNotChanged;

    // Check end game (fall)
    if ((new_location.y + actor->GetSize().y) >= oxygine::getStage()->getSize().y * kPixel)
    {
        EndGameEvent ev;
        oxygine::Stage::instance->dispatchEvent(&ev);
    }

    if (old_location.x < new_location.x) {
        horisontal_direction = Direction::kRight;
    }
    else if (old_location.x > new_location.x) {
        horisontal_direction = Direction::kLeft;
    }

    if (old_location.y < new_location.y) {
        vertical_direction = Direction::kDown;
    }
    else if (old_location.y > new_location.y) {
        vertical_direction = Direction::kUp;
    }

    Distance new_x(actor->GetLocation().x.Value());
    Distance new_y(actor->GetLocation().y.Value());
    bool is_touched_horizontally = false;
    bool is_touched_vertically = false;

    Distance actor_old_upper_bound = old_location.y;
    Distance actor_new_upper_bound = new_location.y;
    Distance actor_old_lower_bound = old_location.y + actor->GetSize().y;
    Distance actor_new_lower_bound = new_location.y + actor->GetSize().y;
    Distance actor_left_bound = new_location.x;
    Distance actor_right_bound = new_location.x + actor->GetSize().x;
    Distance actor_old_left_bound = old_location.x;
    Distance actor_old_right_bound = old_location.x + actor->GetSize().x;

    for (PhysicalObject* barrier : ground_actors_)
    {
        Distance barrier_right_bound = barrier->GetLocation().x + barrier->GetSize().x;
        Distance barrier_left_bound = barrier->GetLocation().x;
        Distance barrier_upper_bound = barrier->GetLocation().y;
        Distance barrier_lower_bound = barrier->GetLocation().y + barrier->GetSize().y;

        // Set Y value
        switch (vertical_direction)
        {
        case Direction::kUp:
            if (barrier_lower_bound > actor_new_upper_bound &&
                barrier_lower_bound <= actor_old_upper_bound &&
                ((actor_left_bound >= barrier_left_bound &&
                    actor_left_bound < barrier_right_bound) ||
                    (actor_right_bound <= barrier_right_bound &&
                        actor_right_bound > barrier_left_bound) ||
                        (actor_left_bound < barrier_left_bound &&
                            actor_right_bound > barrier_right_bound)))
            {
                is_touched_vertically = true;
                if (new_y < barrier_lower_bound)
                {
                    new_y = barrier_lower_bound;
                }
            }
            break;
        case Direction::kDown:
            if (barrier_upper_bound < actor_new_lower_bound &&
                barrier_upper_bound >= actor_old_lower_bound &&
                ((actor_left_bound >= barrier_left_bound &&
                    actor_left_bound < barrier_right_bound) ||
                    (actor_right_bound <= barrier_right_bound &&
                        actor_right_bound > barrier_left_bound) ||
                        (actor_left_bound < barrier_left_bound &&
                            actor_right_bound > barrier_right_bound)))
            {
                is_touched_vertically = true;
                if (new_y > barrier_upper_bound - actor->GetSize().y)
                {
                    new_y = barrier_upper_bound - actor->GetSize().y;
                }
            }
            break;
        }

        // Set X value
        switch (horisontal_direction)
        {
        case Direction::kRight:
            if (barrier_left_bound < actor_right_bound &&
                barrier_left_bound >= actor_old_right_bound &&
                ((actor_new_upper_bound >= barrier_upper_bound &&
                    actor_new_upper_bound < barrier_lower_bound) ||
                    (actor_new_lower_bound > barrier_upper_bound &&
                        actor_new_lower_bound <= barrier_lower_bound) ||
                        (actor_new_upper_bound < barrier_upper_bound &&
                            actor_new_lower_bound > barrier_lower_bound)))
            {
                is_touched_horizontally = true;
                if (new_x > (barrier_left_bound - actor->GetSize().x))
                {
                    new_x = barrier_left_bound - actor->GetSize().x;
                }
            }
            break;
        case Direction::kLeft:
            if (barrier_right_bound > actor_left_bound &&
                barrier_right_bound <= actor_old_left_bound &&
                ((actor_new_upper_bound >= barrier_upper_bound &&
                    actor_new_upper_bound < barrier_lower_bound) ||
                    (actor_new_lower_bound > barrier_upper_bound &&
                        actor_new_lower_bound <= barrier_lower_bound) ||
                        (actor_new_upper_bound < barrier_upper_bound &&
                            actor_new_lower_bound > barrier_lower_bound)))
            {
                is_touched_horizontally = true;
                if (new_x < barrier_right_bound)
                {
                    new_x = barrier_right_bound;
                }
            }
            break;
        }
    }

    if (is_touched_horizontally || is_touched_vertically)
    {
        PhysicalObject::Point new_location(new_x, new_y);
        actor->SetLocation(new_location);
    }
    if (is_touched_horizontally)
    {
        actor->SetSpeed({ Speed(0), actor->GetSpeed().y });
        actor->SetAcceleration({ Acceleration(0), actor->GetAcceleration().y });
    }
    if (is_touched_vertically)
    {
        actor->SetSpeed({ actor->GetSpeed().x, Speed(0) });
        actor->SetAcceleration({ actor->GetAcceleration().x, Acceleration(0) });
    }
    return;
}

void GameEngine::Reset()
{
    ground_actors_.clear();
}

GameEngine& GameEngine::GetInstance()
{
    static GameEngine instance;
    return instance;
}