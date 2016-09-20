#pragma once

#include <memory>

#include "res/Resources.h"

class ResourceSingleton
{
public:
   static void Initialize();
   static const oxygine::Resources& GetRes();
   static void UnInitialize();

private:
   ResourceSingleton() = default;
   
private:
   static ResourceSingleton singleton;

   std::unique_ptr<oxygine::Resources> res_;
};

