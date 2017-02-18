#include "stdafx.h"
#include "CppUnitTest.h"

#include "EnvironmentScroller.h"
#include "PhysicalObjectForTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlatformerTest
{
   TEST_CLASS(TestOfEnvironmentScroller)
   {
   public:

      TEST_METHOD(ScrollByDoesScrollForAllAddedObjects)
      {
         PhysicalObject::Point location1{ 0 * kPixel, 0 * kPixel };
         PhysicalObject::Point location2{ 10 * kPixel, 0 * kPixel };
         PhysicalObject::Point transition_point{ 10 * kPixel, 0 * kPixel};
         PhysicalObjectForTest object1;
         PhysicalObjectForTest object2;
         object1.SetLocation(location1);
         object2.SetLocation(location2);
         EnvironmentScroller scroller;
         scroller.Add(&object1);
         scroller.Add(&object2);

         scroller.MoveBy(transition_point.x);

         Assert::IsTrue(object1.GetLocation() == (location1 + transition_point));
         Assert::IsTrue(object2.GetLocation() == (location2 + transition_point));
      }
   };
}