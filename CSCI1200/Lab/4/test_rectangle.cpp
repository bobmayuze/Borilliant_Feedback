#include <iostream>
#include <cassert>
#include <vector>
#include "Rectangle.h"
#include "Point2D.h"

int main() {
  Point2D lower_left1(11.1,55.5);
  Point2D upper_right1(55.5,99.9);
  Point2D lower_left2(33.3,77.7);
  Point2D upper_right2(111.1,111.1);
  Point2D point1(0,0);
  Point2D point2(100,100);
  Point2D point3(44.4,88.8);

  Point2D pt(50,50);
  pt.set(60,60);

  Rectangle rec1(lower_left1, upper_right1);
  Rectangle rec2(lower_left2, upper_right2);
  print_rectangle(rec1);
  print_rectangle(rec2);

  rec1.add_point(point1);
  rec1.add_point(point2);
  rec1.add_point(point3);
  print_rectangle(rec1);

  rec2.add_point(point1);
  rec2.add_point(point2);
  rec2.add_point(point3);
  print_rectangle(rec2);

  std::vector<Point2D> points_both = points_in_both(rec1, rec2);

  assert(rec1.is_point_within(point3) == true);
  assert(rec1.is_point_within(point1) == false);

  return 0;
}
