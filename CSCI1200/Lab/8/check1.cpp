#include <iostream>

class Point {
public:
  Point(int x0, int y0) : x(x0), y(y0) {}
  int x, y;
};

bool find_road_1(Point pt, int& num) {
  if (pt.x == 0 || pt.y == 0) {
    num++;
    return true;
  }
  return  find_road_1(Point(pt.x-1, pt.y), num) + find_road_1(Point(pt.x, pt.y-1), num);
}

bool find_road_2(Point pt, int& num) {
  if (pt.x == 0 || pt.y == 0) {
    num++;
    return true;
  }
  return  find_road_2(Point(pt.x+1, pt.y), num) + find_road_2(Point(pt.x, pt.y-1), num);
}

bool find_road_3(Point pt, int& num) {
  if (pt.x == 0 || pt.y == 0) {
    num++;
    return true;
  }
  return  find_road_3(Point(pt.x+1, pt.y), num) + find_road_3(Point(pt.x, pt.y+1), num);
}

int find_road_4(Point pt, int& num) {
  if (pt.x == 0 || pt.y == 0) {
    num++;
    return true;
  }
  return  find_road_4(Point(pt.x-1, pt.y), num) + find_road_4(Point(pt.x, pt.y+1), num);
}

int main() {
  int x,y;
  std::cin >> x >> y;
  int num = 0;
  if (x >= 0 && y >= 0) find_road_1(Point(x,y), num);
  if (x <= 0 && y >= 0) find_road_2(Point(x,y), num);
  if (x <= 0 && y <= 0) find_road_3(Point(x,y), num);
  if (x >= 0 && y <= 0) find_road_4(Point(x,y), num);
  std::cout << "solution: " << num <<std::endl;
  return 0;
}