#include <vector>
#include <string>

#include "polygons.h"

// =========================================
//  HELPER FUNCTIONS
// =========================================
// Helper function to get all sides of a polygon
std::vector<Vector> getAllSides(std::vector<Point> points) {
  std::vector<Vector> sides;
  for (unsigned int i = 0; i < points.size()-1; ++i) {
    sides.push_back(Vector(points[i], points[i+1]));
  }
  sides.push_back(Vector(points[points.size()-1], points[0]));
  return sides;
}

// Helper function to get all angles of a polygon
std::vector<double> getAllAngles(std::vector<Point> points) {
  std::vector<double> angles;
  for (unsigned int i = 0; i < points.size()-2; ++i) {
    angles.push_back(Angle(points[i], points[i+1], points[i+2]));
  }
  angles.push_back(Angle(points[points.size()-2], points[points.size()-1], points[0]));
  angles.push_back(Angle(points[points.size()-1], points[0], points[1]));
  return angles;
}

// =========================================
//  POLYGON
// =========================================
Polygon::Polygon(const std::string& aName, const std::vector<Point>& points) {
  name = aName;
  pts = points;
}

// The following functions are pretty straightforward
bool Polygon::HasAllEqualSides() const {
  std::vector<Vector> sides = getAllSides(pts);
  double len = sides[0].Length();
  for (unsigned int i = 1; i < sides.size(); ++i) {
    if (!EqualSides(len, sides[i].Length())) return false;
  }
  return true;
}

bool Polygon::HasAllEqualAngles() const {
  std::vector<double> angles = getAllAngles(pts);
  double ang = angles[0];
  for (unsigned int i = 1; i < angles.size(); ++i) {
    if (!EqualAngles(angles[i], ang)) return false;
  }
  return true;
}

bool Polygon::HasARightAngle() const {
  std::vector<double> angles = getAllAngles(pts);
  for (unsigned int i = 0; i < angles.size(); ++i) {
    if (RightAngle(angles[i])) return true;
  }
  return false;
}

bool Polygon::HasAnObtuseAngle() const {
  std::vector<double> angles = getAllAngles(pts);
  for (unsigned int i = 0; i < angles.size(); ++i) {
    if (ObtuseAngle(angles[i])) return true;
  }
  return false;
}

bool Polygon::HasAnAcuteAngle() const {
  std::vector<double> angles = getAllAngles(pts);
  for (unsigned int i = 0; i < angles.size(); ++i) {
    if (AcuteAngle(angles[i])) return true;
  }
  return false;
}

bool Polygon::IsConvex() const {
  std::vector<double> angles = getAllAngles(pts);
  for (unsigned int i = 0; i < angles.size(); ++i) {
    if (ReflexAngle(angles[i])) return false;
  }
  return true;
}

bool Polygon::IsConcave() const {
  std::vector<double> angles = getAllAngles(pts);
  for (unsigned int i = 0; i < angles.size(); ++i) {
    if (ReflexAngle(angles[i])) return true;
  }
  return false;
}
