#pragma once

#include "ColorRectSprite.h"

#include "PhysicalObject.h"

DECLARE_SMART(ActorBase, spActorBase);
class ActorBase : public oxygine::ColorRectSprite, public PhysicalObject
{
public:
    virtual void SetLocation(const Point& location) override;
    virtual Point GetLocation() const override;
    virtual Size GetSize() const override;
    virtual void SetSize(const Size& size) override;
};

