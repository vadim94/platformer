#pragma once

#include "ActorBase.h"

DECLARE_SMART(GroundActor, spGroundActor);
class GroundActor : public ActorBase
{
public:
    GroundActor(const PhysicalObject::Point& startPoint);
private:
    virtual void doUpdate(const oxygine::UpdateState& us) override;
};