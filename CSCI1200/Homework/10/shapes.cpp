#include <vector>
#include <string>
#include <cassert>

#include "polygons.h"

// Prototypes of the helper functions
std::vector<Vector> getAllSides(std::vector<Point> points);
std::vector<double> getAllAngles(std::vector<Point> points);

// =========================================
//  QUADRILATERAL
// =========================================
Quadrilateral::Quadrilateral(const std::string& aName, const std::vector<Point>& points) {
  if (points.size() != 4) throw 0;
  name = aName;
  pts = points;
}

// =========================================
//  TRAPEZOID
// =========================================
Trapezoid::Trapezoid(const std::string& aName, const std::vector<Point>& points) {
  if (points.size() != 4) throw 0;
  // Make sure it has at least one pair of parallel sides
  std::vector<Vector> sides = getAllSides(points);
  assert(sides.size() == 4);
  if (!Parallel(sides[0], sides[2]) && !Parallel(sides[1], sides[3])) throw 0;
  name = aName;
  pts = points;
}

// =========================================
//  KITE
// =========================================
Kite::Kite(const std::string& aName, const std::vector<Point>& points) {
  if (points.size() != 4) throw 0;
  // Make sure it has two different pairs of neighbour equal sides
  std::vector<Vector> sides = getAllSides(points);
  assert(sides.size() == 4);
  if ((!EqualSides(sides[0].Length(), sides[1].Length()) ||
      !EqualSides(sides[2].Length(), sides[3].Length())) &&
      (!EqualSides(sides[0].Length(), sides[3].Length()) ||
      !EqualSides(sides[1].Length(), sides[2].Length())))
    throw 0;
  name = aName;
  pts = points;
}

// =========================================
//  ARROW
// =========================================
Arrow::Arrow(const std::string& aName, const std::vector<Point>& points) {
  if (points.size() != 4) throw 0;
  // Make sure it has a reflex angle
  std::vector<double> angles = getAllAngles(points);
  assert(angles.size() == 4);
  if (!ReflexAngle(angles[0]) && !ReflexAngle(angles[1]) &&
      !ReflexAngle(angles[2]) && !ReflexAngle(angles[3]))
    throw 0;
  if (!EqualAngles(angles[0], angles[2]) && !EqualAngles(angles[1], angles[3]))
    throw 0;
  name = aName;
  pts = points;
}

// =========================================
//  PARALLELOGRAM
// =========================================
Parallelogram::Parallelogram(const std::string& aName, const std::vector<Point>& points) {
  if (points.size() != 4) throw 0;
  // Make sure it has two pairs of parallel sides
  std::vector<Vector> sides = getAllSides(points);
  assert(sides.size() == 4);
  if (!Parallel(sides[0], sides[2]) || !Parallel(sides[1], sides[3])) throw 0;
  name = aName;
  pts = points;
}

// =========================================
//  ISOSCELESTRAPEZOID
// =========================================
IsoscelesTrapezoid::IsoscelesTrapezoid(const std::string& aName, const std::vector<Point>& points) {
  if (points.size() != 4) throw 0;
  // Make sure it has equal base angles
  std::vector<double> angles = getAllAngles(points);
  assert(angles.size() == 4);
  if ((!EqualAngles(angles[0], angles[3]) || !EqualAngles(angles[1], angles[2])) &&
      (!EqualAngles(angles[0], angles[1]) || !EqualAngles(angles[2], angles[3])))
    throw 0;
  name = aName;
  pts = points;
}

// =========================================
//  RHOMBUS
// =========================================
Rhombus::Rhombus(const std::string& aName, const std::vector<Point>& points) {
  if (points.size() != 4) throw 0;
  // Make sure all of its four sides are equal
  std::vector<Vector> sides = getAllSides(points);
  double len = sides[0].Length();
  if (!EqualSides(sides[1].Length(), len) || !EqualSides(sides[2].Length(), len) ||
      !EqualSides(sides[3].Length(), len))
    throw 0;
  name = aName;
  pts = points;
}

// =========================================
//  RECTANGLE
// =========================================
Rectangle::Rectangle(const std::string& aName, const std::vector<Point>& points) {
  if (points.size() != 4) throw 0;
  // Make sure all angles are equal to 90
  std::vector<double> angles = getAllAngles(points);
  assert(angles.size() == 4);
  if (!RightAngle(angles[0]) || !RightAngle(angles[1]) ||
      !RightAngle(angles[2]) || !RightAngle(angles[3]))
    throw 0;
  name = aName;
  pts = points;
}

// =========================================
//  SQUARE
// =========================================
Square::Square(const std::string& aName, const std::vector<Point>& points) {
  if (points.size() != 4) throw 0;
  // Make sure all angles are equal to 90 and all sides are equal
  std::vector<double> angles = getAllAngles(points);
  assert(angles.size() == 4);
  if (!RightAngle(angles[0]) || !RightAngle(angles[1]) ||
      !RightAngle(angles[2]) || !RightAngle(angles[3]))
    throw 0;
  std::vector<Vector> sides = getAllSides(points);
  assert(sides.size() == 4);
  double len = sides[0].Length();
  for (unsigned int i = 1; i < 4; ++i) {
    if (!EqualSides(len, sides[i].Length())) throw 0;
  }
  name = aName;
  pts = points;
}

// =========================================
//  TRIANGLE
// =========================================
Triangle::Triangle(const std::string& aName, const std::vector<Point>& points) {
  if (points.size() != 3) throw 0;
  name = aName;
  pts = points;
}

// =========================================
//  ISOSCELESTRIANGLE
// =========================================
IsoscelesTriangle::IsoscelesTriangle(const std::string& aName, const std::vector<Point>& points) {
  if (points.size() != 3) throw 0;
  // Make sure it has at least two equal sides
  std::vector<double> angles = getAllAngles(points);
  assert(angles.size() == 3);
  if (!EqualAngles(angles[0], angles[1]) && !EqualAngles(angles[1], angles[2]) &&
      !EqualAngles(angles[2], angles[0]))
    throw 0;
  name = aName;
  pts = points;
}

// =========================================
//  RIGHTTRIANGLE
// =========================================
RightTriangle::RightTriangle(const std::string& aName, const std::vector<Point>& points) {
  if (points.size() != 3) throw 0;
  // Make sure it has at least one right angle
  std::vector<double> angles = getAllAngles(points);
  assert(angles.size() == 3);
  if (!RightAngle(angles[0]) && !RightAngle(angles[1]) && !RightAngle(angles[2]))
    throw 0;
  name = aName;
  pts = points;
}

// =========================================
//  ISOSCELESRIGHTTRIANGLE
// =========================================
IsoscelesRightTriangle::IsoscelesRightTriangle(const std::string& aName, const std::vector<Point>& points) {
  if (points.size() != 3) throw 0;
  // Make sure it has at least one right angle and two equal sides
  std::vector<double> angles = getAllAngles(points);
  assert(angles.size() == 3);
  if (!EqualAngles(angles[0], angles[1]) && !EqualAngles(angles[1], angles[2]) &&
      !EqualAngles(angles[2], angles[0]))
    throw 0;
  if (!RightAngle(angles[0]) && !RightAngle(angles[1]) && !RightAngle(angles[2]))
    throw 0;
  name = aName;
  pts = points;
}

// =========================================
//  OBTUSETRIANGLE
// =========================================
ObtuseTriangle::ObtuseTriangle(const std::string& aName, const std::vector<Point>& points) {
  if (points.size() != 3) throw 0;
  // Make sure it has at least one obtuse angle
  std::vector<double> angles = getAllAngles(points);
  assert(angles.size() == 3);
  if (!ObtuseAngle(angles[0]) && !ObtuseAngle(angles[1]) && !ObtuseAngle(angles[2]))
    throw 0;
  name = aName;
  pts = points;
}

// =========================================
//  ISOSCELESOBTUSETRIANGLE
// =========================================
IsoscelesObtuseTriangle::IsoscelesObtuseTriangle(const std::string& aName, const std::vector<Point>& points) {
  if (points.size() != 3) throw 0;
  // Make sure it has at least one obtuse angle and two equal sides
  std::vector<double> angles = getAllAngles(points);
  assert(angles.size() == 3);
  if (!ObtuseAngle(angles[0]) && !ObtuseAngle(angles[1]) && !ObtuseAngle(angles[2]))
    throw 0;
  if (!EqualAngles(angles[0], angles[1]) && !EqualAngles(angles[1], angles[2]) &&
      !EqualAngles(angles[2], angles[0]))
    throw 0;
  name = aName;
  pts = points;
}

// =========================================
//  EQUILATERALTRIANGLE
// =========================================
EquilateralTriangle::EquilateralTriangle(const std::string& aName, const std::vector<Point>& points) {
  if (points.size() != 3) throw 0;
  // Make sure it has all equal angles
  std::vector<double> angles = getAllAngles(points);
  assert(angles.size() == 3);
  if (!EqualAngles(angles[0], angles[1]) || !EqualAngles(angles[1], angles[2]) ||
      !EqualAngles(angles[2], angles[0]))
    throw 0;
  name = aName;
  pts = points;
}

// =========================================
