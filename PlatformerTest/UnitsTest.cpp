#include "stdafx.h"
#include "CppUnitTest.h"

#include "math/vector2.h"

#include "Unit.h"

#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace
{
   using Area = DUnit < 2, 0 > ; // Square pixel.

   double epsilon = 0.000001;
   double lessThenEpsilon = epsilon / 10;
   const Distance littleMoreThenPixel(pixel.Value() + lessThenEpsilon);
   const Distance twoPixels(2);
   const Distance zeroDistance(0);
}

namespace PlatformerTest
{
   TEST_CLASS(TestOfUnits)
   {
   public:

      TEST_METHOD(AreEqualTest)
      {
         Assert::IsTrue(pixel.AreEqual(pixel, epsilon));
         Assert::IsTrue(pixel.AreEqual(littleMoreThenPixel, epsilon));
         Assert::IsFalse(pixel.AreEqual(twoPixels, epsilon));
      }

      TEST_METHOD(DefaultConstructedUnit)
      {
         Distance dist;

         Assert::IsTrue(dist.AreEqual(zeroDistance, epsilon));
      }

      TEST_METHOD(UnitMultiplicationByValue)
      {
         auto unit = pixel;
         unit *= 2;

         Assert::IsTrue(unit.AreEqual(twoPixels, epsilon));
         Assert::IsTrue((pixel * 2).AreEqual(twoPixels, epsilon));
         Assert::IsTrue((2 * pixel).AreEqual(twoPixels, epsilon));
      }

      TEST_METHOD(UnitDivisionByValue)
      {
         auto unit = twoPixels;
         unit /= 2;

         Assert::IsTrue(unit.AreEqual(pixel, epsilon));
         Assert::IsTrue((twoPixels / 2).AreEqual(pixel, epsilon));
      }

      TEST_METHOD(UnitsSum)
      {
         auto unit = pixel;
         unit += pixel;

         Assert::IsTrue(unit.AreEqual(twoPixels, epsilon));
         Assert::IsTrue((pixel+pixel).AreEqual(twoPixels, epsilon));
      }

      TEST_METHOD(UnitsSubstract)
      {
         auto unit = twoPixels;
         unit -= pixel;

         Assert::IsTrue(unit.AreEqual(pixel, epsilon));
         Assert::IsTrue((twoPixels - pixel).AreEqual(pixel, epsilon));
      }

      TEST_METHOD(UnitMuliplicationByUnit)
      {
         auto unit = pixel * twoPixels;

         Assert::IsTrue(std::is_same<decltype(unit), Area>::value);
         Assert::IsTrue(unit.AreEqual(Area(2), epsilon));
      }

      TEST_METHOD(UnitDivisionByUnit)
      {
         auto unit = pixel / second;

         Assert::IsTrue(std::is_same<decltype(unit), Speed>::value);
         Assert::IsTrue(unit.AreEqual(Speed(1), epsilon));
      }
   };
}