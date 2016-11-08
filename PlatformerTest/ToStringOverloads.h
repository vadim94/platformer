#pragma once

#include <string>
#include <sstream>

#include "CppUnitTest.h"

#include "PhysicalObject.h"
#include "Unit.h"

namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

   template<> static std::wstring ToString<PhysicalObject::SpeedVector>(const PhysicalObject::SpeedVector& speed)
   {
      std::wostringstream ostr;
      ostr << "(" << speed.x.Value() << ", " << speed.y.Value() << ")";
      return ostr.str();
   }

   template<> static std::wstring ToString<Speed>(const Speed& speed)
   {
      std::wostringstream ostr;
      ostr << speed.Value() << "pixelPerSecond";
      return ostr.str();
   }

} } }