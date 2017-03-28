#ifndef _SHAPES_H_
#define _SHAPES_H_

#include <vector>
#include <string>
#include "utilities.h"

// =========================================
//  POLYGON
// =========================================
// All of the shapes we may have are polygons, so Polygon is the base class
// All the member functions are marked with virtual, because the may be over-
// write in the children classes.
class Polygon {
public:
  Polygon() {}
  Polygon(const std::string& aName, const std::vector<Point>& points);
  virtual ~Polygon() {}
  const std::string& getName() const { return name; }
  const std::vector<Point>& getpt() const {return pts;}
  virtual bool HasAllEqualSides() const;
  virtual bool HasAllEqualAngles() const;
  virtual bool HasARightAngle() const;
  virtual bool HasAnObtuseAngle() const;
  virtual bool HasAnAcuteAngle() const;
  virtual bool IsConvex() const;
  virtual bool IsConcave() const;
protected:
  std::string name;
  std::vector<Point> pts;
};

// =========================================
//  QUADRILATERAL
// =========================================
// Polygon with four sides
class Quadrilateral: public Polygon {
public:
  Quadrilateral() {}
  Quadrilateral(const std::string& aName, const std::vector<Point>& points);
  virtual ~Quadrilateral() {}
};

// =========================================
//  TRAPEZOID
// =========================================
// Quadrilateral with at least one pair of parallel sides
// It is convex, not concave
class Trapezoid: virtual public Quadrilateral {
public:
  Trapezoid() {}
  Trapezoid(const std::string& aName, const std::vector<Point>& points);
  virtual ~Trapezoid() {}
  bool IsConvex() const { return true; }
  bool IsConcave() const { return false; }
};

// =========================================
//  KITE
// =========================================
// Quadrilateral with two different pairs of neighbour equal sides
class Kite: virtual public Quadrilateral {
public:
  Kite() {}
  Kite(const std::string& aName, const std::vector<Point>& points);
  virtual ~Kite() {}
};

// =========================================
//  ARROW
// =========================================
// Kite with one reflex angle
// It is concave, not convex. And it has at least two acute angles
class Arrow: public Quadrilateral {
public:
  Arrow() {}
  Arrow(const std::string& aName, const std::vector<Point>& points);
  ~Arrow() {}
  bool HasAnAcuteAngle() const { return true; }
  bool IsConvex() const { return false; }
  bool IsConcave() const { return true; }
};

// =========================================
//  PARALLELOGRAM
// =========================================
// Quadrilateral with two pairs of parallel sides
class Parallelogram: virtual public Trapezoid {
public:
  Parallelogram() {}
  Parallelogram(const std::string& aName, const std::vector<Point>& points);
  virtual ~Parallelogram() {}
};

// =========================================
//  ISOSCELESTRAPEZOID
// =========================================
// Trapezoid with equal base angles
class IsoscelesTrapezoid: virtual public Trapezoid {
public:
  IsoscelesTrapezoid() {}
  IsoscelesTrapezoid(const std::string& aName, const std::vector<Point>& points);
  virtual ~IsoscelesTrapezoid() {}
};

// =========================================
//  RHOMBUS
// =========================================
// Quadrilateral with all sides equal
class Rhombus: virtual public Parallelogram, public Kite {
public:
  Rhombus() {}
  Rhombus(const std::string& aName, const std::vector<Point>& points);
  virtual ~Rhombus() {}
  bool HasAllEqualSides() const { return true; }
};

// =========================================
//  RECTANGLE
// =========================================
// Rectangle is a parallelogram whose all angles are equal to 90
class Rectangle: virtual public Parallelogram, public IsoscelesTrapezoid {
public:
  Rectangle() {}
  Rectangle(const std::string& aName, const std::vector<Point>& points);
  virtual ~Rectangle() {}
  bool HasAllEqualAngles() const { return true; }
  bool HasARightAngle() const { return true; }
};

// =========================================
//  SQUARE
// =========================================
// Square is a rectangle whose all sides are equal
class Square: public Rectangle, public Rhombus {
public:
  Square() {}
  Square(const std::string& aName, const std::vector<Point>& points);
  ~Square() {}
};

// =========================================
//  TRIANGLE
// =========================================
// Triangle is a polygon with 3 sides
// It has at least two acute angles, and it is convex
class Triangle: public Polygon {
public:
  Triangle() {}
  Triangle(const std::string& aName, const std::vector<Point>& points);
  virtual ~Triangle() {}
  bool HasAnAcuteAngle() const { return true; }
  bool IsConvex() const { return true; }
  bool IsConcave() const { return false; }
};

// =========================================
//  ISOSCELESTRIANGLE
// =========================================
// IsoscelesTriangle is a triangle with at least two equal sides
class IsoscelesTriangle: virtual public Triangle {
public:
  IsoscelesTriangle() {}
  IsoscelesTriangle(const std::string& aName, const std::vector<Point>& points);
  virtual ~IsoscelesTriangle() {}
};

// =========================================
//  RIGHTTRIANGLE
// =========================================
// RightTriangle is a triangle with a right angle, and it does not has obtuse
// angles
class RightTriangle: virtual public Triangle {
public:
  RightTriangle() {}
  RightTriangle(const std::string& aName, const std::vector<Point>& points);
  virtual ~RightTriangle() {}
  bool HasARightAngle() const { return true; }
  bool HasAnObtuseAngle() const { return false; }
};

// =========================================
//  ISOSCELESRIGHTTRIANGLE
// =========================================
// IsoscelesTriangle is what it means
class IsoscelesRightTriangle: public IsoscelesTriangle, public RightTriangle {
public:
  IsoscelesRightTriangle() {}
  IsoscelesRightTriangle(const std::string& aName, const std::vector<Point>& points);
  ~IsoscelesRightTriangle() {}
};

// =========================================
//  OBTUSETRIANGLE
// =========================================
// ObtuseTriangle has one obtuse angle and two acute Triangles
class ObtuseTriangle: virtual public Triangle {
public:
  ObtuseTriangle() {}
  ObtuseTriangle(const std::string& aName, const std::vector<Point>& points);
  virtual ~ObtuseTriangle() {}
  bool HasARightAngle() const { return false; }
  bool HasAnAcuteAngle() const { return true; }
  bool HasAnObtuseAngle() const { return true; }
};

// =========================================
//  ISOSCELESOBTUSETRIANGLE
// =========================================
// IsoscelesTriangle is what it means
class IsoscelesObtuseTriangle: public ObtuseTriangle, public IsoscelesTriangle {
public:
  IsoscelesObtuseTriangle() {}
  IsoscelesObtuseTriangle(const std::string& aName, const std::vector<Point>& points);
  ~IsoscelesObtuseTriangle() {}
};

// =========================================
//  EQUILATERALTRIANGLE
// =========================================
// EquilateralTriangle is a triangle with all sides equal and all angles equal
class EquilateralTriangle: public IsoscelesTriangle {
public:
  EquilateralTriangle() {}
  EquilateralTriangle(const std::string& aName, const std::vector<Point>& points);
  ~EquilateralTriangle() {}
  bool HasAllEqualSides() const { return true; }
  bool HasAllEqualAngles() const { return true; }
  bool HasARightAngle() const { return false; }
  bool HasAnAcuteAngle() const { return true; }
  bool HasAnObtuseAngle() const { return false; }
};

#endif
