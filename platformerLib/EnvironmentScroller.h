#pragma once

#include <vector>

#include "PhysicalObject.h"
#include "Unit.h"

class EnvironmentScroller
{
public:
   EnvironmentScroller() {}

   void Add(PhysicalObject* object);
   void MoveBy(const Distance& distance);

private:
   std::vector<PhysicalObject*> environmentObjects_;
};

