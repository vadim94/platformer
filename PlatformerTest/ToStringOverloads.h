#pragma once

#include <string>
#include <sstream>

#include "CppUnitTest.h"

#include "PhysicalObject.h"
#include "Unit.h"

namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

    template<int Distance, int Time>
    std::wstring UnitToString(const DUnit<Distance, Time>& unit, std::wstring label)
    {
        std::wostringstream ostr;
        ostr << unit.Value() << " " << label;
        return ostr.str();
    }

    template<> static std::wstring ToString<Speed>(const Speed& speed)
    {
        std::wostringstream ostr;
        ostr << UnitToString(speed, L"pixelPerSecond");
        return ostr.str();
    }

    template<> static std::wstring ToString<Distance>(const Distance& distance)
    {
        std::wostringstream ostr;
        ostr << UnitToString(distance, L"pixel");
        return ostr.str();
    }

    template<> static std::wstring ToString<PhysicalObject::SpeedVector>(const PhysicalObject::SpeedVector& speed)
    {
        std::wostringstream ostr;
        ostr << "(" << ToString(speed.x) << ", " << ToString(speed.y) << ")";
        return ostr.str();
    }

    template<> static std::wstring ToString<PhysicalObject::Point>(const PhysicalObject::Point& point)
    {
        std::wostringstream ostr;
        ostr << "(" << ToString(point.x) << ", " << ToString(point.y) << ")";
        return ostr.str();
    }
} } }