#pragma once

#include "PhysicalObject.h"

class PhysicalObjectForTest : public PhysicalObject
{
public:
   PhysicalObjectForTest(const Point& location = { pixel * 0, pixel * 0 }) : location_(location) {}

   void SetLocation(const Point& location) override { location_ = location; }
   Point GetLocation() const override { return location_; }
   void SetSize(const Size& size) override {/*to be implemented*/}
   Size GetSize() const override { return{ 0 * pixel, 0 * pixel };/*to be implemented*/ }
private:
   Point location_;
};