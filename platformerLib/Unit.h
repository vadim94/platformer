#pragma once

#include <cmath>

template<class ValueType, int Distance, int Time>
class Unit {
public:

   explicit Unit(ValueType initVal = 0) : val_{ initVal } {}
   ValueType Value() const { return val_; }
   ValueType& Value() { return val_; }

   bool AreEqual(const Unit& other, double epsilon) const
   {
      return abs(val_ - other.val_) < epsilon;
   }

   Unit Abs() const
   {
      return Unit(std::abs(val_));
   }

   Unit& operator+=(const Unit& rhs)
   {
      val_ += rhs.val_;
      return *this;
   }

   Unit& operator-=(const Unit& rhs)
   {
      val_ -= rhs.val_;
      return *this;
   }

   Unit& operator*=(ValueType rhs)
   {
      val_ *= rhs;
      return *this;
   }

   Unit& operator/=(ValueType rhs)
   {
      val_ /= rhs;
      return *this;
   }

   bool operator <(const Unit& rhs) const
   {
      return !AreEqual(rhs, std::numeric_limits<ValueType>::epsilon()) && val_ < rhs.val_;
   }

   bool operator ==(const Unit& rhs) const
   {
      return this == &rhs || AreEqual(rhs, std::numeric_limits<ValueType>::epsilon());
   }

   bool operator !=(const Unit& rhs) const
   {
      return !(*this == rhs);
   }

   bool operator >(const Unit& rhs) const
   {
      return !(*this < rhs) && (*this != rhs);
   }

   bool operator >=(const Unit& rhs) const
   {
      return !(*this < rhs);
   }

   bool operator <=(const Unit& rhs) const
   {
      return !(*this > rhs);
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

template<class ValueType, int Distance, int Time>
Unit<ValueType, Distance, Time> operator-(const Unit<ValueType, Distance, Time>& value)
{
   return Unit<ValueType, Distance, Time>(-value.Value());
}

template<int Distance, int Time>
using DUnit = Unit < double, Distance, Time >;

using Distance = DUnit < 1, 0 > ;
using Time = DUnit< 0, 1 >;
using Speed = DUnit < 1, -1 > ;
using Acceleration = DUnit < 1, -2 > ;

const Distance kPixel = Distance(1);
const Time kSecond = Time(1);
const Speed kPixelPerSecond = kPixel / kSecond;
const Acceleration kPixelPerSquareSecond = kPixel / kSecond / kSecond;
