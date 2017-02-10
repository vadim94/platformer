#pragma once

#include "PhysicalObject.h"

class PhysicalObjectForTest : public PhysicalObject
{
public:
   PhysicalObjectForTest(const Point& location = { pixel * 0, pixel * 0 }) : location_(location) {}

   void SetLocation(const Point& location) override { location_ = location; }
   Point GetLocation() const override { return location_; }
private:
   Point location_;
};