#include "circle.h"

#include <cmath>
#define PI 3.141592653589793
// Reference: https://milania.de/blog/Intersection_area_of_two_circles_with_implementation_in_C%2B%2B
// Reference: https://www.xarg.org/2016/07/calculate-the-intersection-area-of-two-circles/

Circle::Circle(Point c, double r) : center(c), radius(r) {}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  const double distance = center.distanceFrom(otherCircle.center);
  if (distance >= radius + otherCircle.radius) {
    return 0.0;
  }
  if (distance <= std::abs(radius - otherCircle.radius)) {
    return PI * pow(fmin(radius, otherCircle.radius), 2);
  }
  const double a_pow = pow(radius, 2);
  const double b_pow = pow(otherCircle.radius, 2);
  /* Calculate distance */
  const double mid_distance1 = (a_pow - b_pow + pow(distance, 2)) / (2 * distance);
  const double mid_distance2 = distance - mid_distance1;
  const double height = sqrt(pow(radius, 2) - pow(mid_distance1, 2));

  /* Calculate angles */
  const double alpha = std::fmod(std::atan2(height, mid_distance1) * 2.0 + 2 * PI,
                                 2 * PI);  // first circle's central angle
  const double beta = std::fmod(std::atan2(height, mid_distance2) * 2.0 + 2 * PI,
                                2 * PI);  // second circle's central angle

  /* Calculate areas */
  const double A0 =
      std::pow(radius, 2) / 2.0 * (alpha - std::sin(alpha));  // Area of the first circula segment
  const double A1 = std::pow(otherCircle.radius, 2) / 2.0 *
                    (beta - std::sin(beta));  // Area of the second circula segment
  return A0 + A1;
}
