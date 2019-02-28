#include "point.h"

class Circle
{
 private:
  Point center;
  const double radius;

 public:
  Circle(Point c, double r);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
