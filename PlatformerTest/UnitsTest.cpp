#include "stdafx.h"
#include "CppUnitTest.h"

#include "math/vector2.h"

#include "Unit.h"

#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace
{
   using Area = DUnit < 2, 0 > ; // Square pixel.

   const double kEpsilon = 0.000001;
   const double kLessThenEpsilon = kEpsilon / 10;
   const Distance kLittleMoreThenPixel{ kPixel.Value() + kLessThenEpsilon };
   const Distance kTwoPixels{ 2 };
   const Distance kZeroDistance{ 0 };
}

namespace PlatformerTest
{
   TEST_CLASS(TestOfUnits)
   {
   public:

      TEST_METHOD(AreEqualTest)
      {
         Assert::IsTrue(kPixel.AreEqual(kPixel, kEpsilon));
         Assert::IsTrue(kPixel.AreEqual(kLittleMoreThenPixel, kEpsilon));
         Assert::IsFalse(kPixel.AreEqual(kTwoPixels, kEpsilon));
      }

      TEST_METHOD(DefaultConstructedUnit)
      {
         Distance dist;

         Assert::IsTrue(dist.AreEqual(kZeroDistance, kEpsilon));
      }

      TEST_METHOD(UnitMultiplicationByValue)
      {
         auto unit = kPixel;
         unit *= 2;

         Assert::IsTrue(unit.AreEqual(kTwoPixels, kEpsilon));
         Assert::IsTrue((kPixel * 2).AreEqual(kTwoPixels, kEpsilon));
         Assert::IsTrue((2 * kPixel).AreEqual(kTwoPixels, kEpsilon));
      }

      TEST_METHOD(UnitDivisionByValue)
      {
         auto unit = kTwoPixels;
         unit /= 2;

         Assert::IsTrue(unit.AreEqual(kPixel, kEpsilon));
         Assert::IsTrue((kTwoPixels / 2).AreEqual(kPixel, kEpsilon));
      }

      TEST_METHOD(UnitsSum)
      {
         auto unit = kPixel;
         unit += kPixel;

         Assert::IsTrue(unit.AreEqual(kTwoPixels, kEpsilon));
         Assert::IsTrue((kPixel+kPixel).AreEqual(kTwoPixels, kEpsilon));
      }

      TEST_METHOD(UnitsSubstract)
      {
         auto unit = kTwoPixels;
         unit -= kPixel;

         Assert::IsTrue(unit.AreEqual(kPixel, kEpsilon));
         Assert::IsTrue((kTwoPixels - kPixel).AreEqual(kPixel, kEpsilon));
      }

      TEST_METHOD(UnitMuliplicationByUnit)
      {
         auto unit = kPixel * kTwoPixels;

         Assert::IsTrue(std::is_same<decltype(unit), Area>::value);
         Assert::IsTrue(unit.AreEqual(Area(2), kEpsilon));
      }

      TEST_METHOD(UnitDivisionByUnit)
      {
         auto unit = kPixel / kSecond;

         Assert::IsTrue(std::is_same<decltype(unit), Speed>::value);
         Assert::IsTrue(unit.AreEqual(Speed(1), kEpsilon));
      }
   };
}