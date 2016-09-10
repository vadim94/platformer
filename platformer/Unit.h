#pragma once

#include <cmath>

template<class ValueType, int Distance, int Time>
class Unit {
public:

   explicit Unit(ValueType initVal = 0) : val_{ initVal } {}
   ValueType Value() const { return val_; }
   ValueType& Value() { return val_; }

   bool AreEqual(const Unit<ValueType, Distance, Time>& other, double epsilon) const
   {
      return abs(val_ - other.val_) < epsilon;
   }

   Unit<ValueType, Distance, Time>& operator+=(const Unit<ValueType, Distance, Time>& rhs)
   {
      val_ += rhs.val_;
      return *this;
   }

   Unit<ValueType, Distance, Time>& operator-=(const Unit<ValueType, Distance, Time>& rhs)
   {
      val_ -= rhs.val_;
      return *this;
   }

   Unit<ValueType, Distance, Time>& operator*=(ValueType rhs)
   {
      val_ *= rhs;
      return *this;
   }

   Unit<ValueType, Distance, Time>& operator/=(ValueType rhs)
   {
      val_ /= rhs;
      return *this;
   }

private:
   ValueType val_;
};

template<class ValueType, int Distance, int Time>
Unit<ValueType, Distance, Time> operator+(const Unit<ValueType, Distance, Time>& lhs, const Unit<ValueType, Distance, Time>& rhs)
{
   return Unit<ValueType, Distance, Time>(lhs.Value() + rhs.Value());
}

template<class ValueType, int Distance, int Time>
Unit<ValueType, Distance, Time> operator-(const Unit<ValueType, Distance, Time>& lhs, const Unit<ValueType, Distance, Time>& rhs)
{
   return Unit<ValueType, Distance, Time>(lhs.Value() - rhs.Value());
}

template<class ValueType, int Distance, int Time, int DistanceOther, int TimeOther>
Unit<ValueType, Distance + DistanceOther, Time + TimeOther> operator*(const Unit<ValueType, Distance, Time>& lhs, const Unit<ValueType, DistanceOther, TimeOther>& rhs)
{
   return Unit<ValueType, Distance + DistanceOther, Time + TimeOther>(lhs.Value() * rhs.Value());
}

template<class ValueType, class Value, int Distance, int Time>
Unit<ValueType, Distance, Time> operator*(const Unit<ValueType, Distance, Time>& lhs, Value value)
{
   return Unit<ValueType, Distance, Time>(lhs.Value() * value);
}

template<class ValueType, class Value, int Distance, int Time>
Unit<ValueType, Distance, Time> operator*(Value value, const Unit<ValueType, Distance, Time>& rhs)
{
   return rhs * value;
}

template<class ValueType, int Distance, int Time, int DistanceOther, int TimeOther>
Unit<ValueType, Distance - DistanceOther, Time - TimeOther> operator/(const Unit<ValueType, Distance, Time>& lhs, const Unit<ValueType, DistanceOther, TimeOther>& rhs)
{
   return Unit<ValueType, Distance - DistanceOther, Time - TimeOther>(lhs.Value() / rhs.Value());
}

template<class ValueType, class Value, int Distance, int Time>
Unit<ValueType, Distance, Time> operator/(const Unit<ValueType, Distance, Time>& lhs, Value value)
{
   return Unit<ValueType, Distance, Time>(lhs.Value() / value);
}

template<class ValueType, class Value, int Distance, int Time>
Unit<ValueType, -Distance, -Time> operator/(Value value, const Unit<ValueType, Distance, Time>& rhs)
{
   return Unit<ValueType, -Distance, -Time>(value / lhs.Value());
}

template<class ValueType, int Distance, int Time>
bool operator==(const Unit<ValueType, Distance, Time>& lhs, const Unit<ValueType, Distance, Time>& rhs)
{
	return lhs.AreEqual(rhs, std::numeric_limits<ValueType>::epsilon());
}

template<int Distance, int Time>
using DUnit = Unit < double, Distance, Time >;

using Distance = DUnit < 1, 0 > ;
using Time = DUnit< 0, 1 >;
using Speed = DUnit < 1, -1 > ;
using Acceleration = DUnit < 1, -2 > ;

const Distance pixel = Distance(1);
const Time second = Time(1);
const Speed pixelPerSecond = pixel / second;
const Acceleration pixelPerSquareSecond = pixel / second / second;
