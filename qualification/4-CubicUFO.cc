#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

// please use tau for any calculations, it just makes so much more sense :)
#define TAU 6.283185307179586476
#define THRESH 0.00000000001

using namespace std;

// here my thought process:
// first, the minimum area the cube will project is 1
// the maximum area the cube will project will be when
// it is with two opposed vertices in a vertical line
// casting a hexagonal shadow (area is 1+sqrt(2))

// to get a shadow between 1 and sqrt(2) we can simply
// rotate the cube on one of its axis
// if we want a bigger shadow then we will need two rotations

// in any case, since we can't just say the X and Y rotations
// we will need a function that rotates vertices around
// in order to calculate the centers

// idea: split problem in two cases and use binary search
// on one of the rotations only to determine the solution
// this way we greatly simplify the problem using only
// rotations around the x and z axis

// cube representation used
//   (+Y)
//    4-------5
//   /|      /|
//  / |     / |
// 7--|----6  |
// |  0----|--1  (+X)
// | /     | /
// 3-------2
// (+Z)


double mod(double a, double b) {
  return sqrt(a*a+b*b);
}


class Point {
public:
  double x,y,z;
  Point(double x,double y,double z) {
    this->x=x;
    this->y=y;
    this->z=z;
  };

  void rotateX(double angle) {
      if (z == 0 && y == 0) return;
      double m = mod(z,y);
      double a = atan2(z,y) + angle;
      y = cos(a)*m; z = sin(a)*m;
  };
  void rotateZ(double angle) {
      if (x == 0 && y == 0) return;
      double m = mod(y,x);
      double a = atan2(y,x) + angle;
      x = cos(a)*m; y = sin(a)*m;
  };
  void print() {
    cout << this->x << " " << this->y << " " << this->z << endl;
  }
};

class Obj {
public:
  vector<Point> v;
  inline void add(double x, double y, double z){
    Point p(x,y,z); v.push_back(p);
  }
  inline void rotateX(double rad) {
    for (int i = 0; i < v.size(); i++) v[i].rotateX(rad);
  }
  inline void rotateZ(double rad) {
    for (int i = 0; i < v.size(); i++) v[i].rotateZ(rad);
  }
  void print() {
    for (int i = 0; i < v.size(); i++) {
      cout << i << " ";
      v[i].print();
    }
  }
  void printCenters() {
    for (int i = 8; i < v.size(); i++) {
      v[i].print();
    }
  }
};


Obj getCube() {
  Obj o;
  double s = 0.5;
  // lower plane
  o.add(-s, -s, -s);
  o.add(+s, -s, -s);
  o.add(+s, -s, +s);
  o.add(-s, -s, +s);
  // upper plane
  o.add(-s, +s, -s);
  o.add(+s, +s, -s);
  o.add(+s, +s, +s);
  o.add(-s, +s, +s);
  // centers because meh
  o.add(s, 0, 0);
  o.add(0, s, 0);
  o.add(0, 0, s);

  return o;
}

double areaSmall(Obj &o) {
  // use vertices 0 and 7's z coordinate
  return abs(o.v[0].z - o.v[7].z);
}

void solveSmall(double area) {
  // we are only rotating on the X axis
  Obj orig = getCube();
  double min = 0;
  double max = TAU/8;

  Obj o = orig;
  double carea = areaSmall(o);
  while (abs(carea - area) > THRESH) {
    // still logarithmic even though we're using trionometric function
    double x = (min+max)/2;
    o = orig;
    o.rotateX(x);
    carea = areaSmall(o);
    if (carea < area) min = x;
    else max = x;
  }
  o.printCenters();
}

double areaLarge(Obj &o) {
  // use vertices 0 and 1's x coordinate times sqrt(2)
  // for the center rectangle
  double rect = sqrt(2) * abs(o.v[0].x - o.v[1].x);
  double triangles = sqrt(2) * abs(o.v[5].x - o.v[2].x);
  return rect+triangles;
}

void solveLarge(double area) {
  // we are rotating on both X and Z axis
  Obj orig = getCube();
  orig.rotateX(TAU/8);

  double min = 0;
  double max = TAU/8;

  Obj o = orig;
  double carea = areaLarge(o);
  while (abs(carea - area) > THRESH) {
    // still logarithmic even though we're using trionometric function
    double x = (min+max)/2;
    o = orig;
    o.rotateZ(x);
    carea = areaLarge(o);
    if (carea < area) min = x;
    else max = x;
  }
  o.printCenters();
}

void solve(int n) {
  cout << "Case #" << n << ":" << endl;

  double area; cin >> area;
  if (area < sqrt(2)) {
    solveSmall(area);
  } else {
    solveLarge(area);
  }
}

int main() {
  int n; cin >> n;
  for (int i = 0; i < n; i++) solve(i+1);
}
