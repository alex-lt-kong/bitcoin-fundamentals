#include <float.h>
#include <iostream>
#include <stdexcept>
#include <limits.h>
#include <math.h>

using namespace std;

class Point {
  public:
    float a = 0;
    float b = 0;
    float x = 0;
    float y = 0;
    Point(float x, float y, float a, float b);
    bool operator==(const Point& other) const;
    Point operator+(const Point& other);
    string toString();
};

Point::Point(float x, float y, float a, float b) {
  this->a = a;
  this->b = b;
  this->x = x;
  this->y = y;
  
  if (this->x == FLT_MAX && this->y == FLT_MAX) { return; }

  if (pow(y, 2) != pow(x, 3) + a * x + b) {
    throw std::invalid_argument(
      "(" + to_string(x) + ", " + to_string(y) + ") is not on the curve"
    );
  }

}

bool Point::operator==(const Point& other) const
{
  ;
  // ICYW: This is overloading, not overriding
  return (
    this->a == other.a && this->b == other.b && 
    this->x == other.x && this->y == other.y
  );
}

Point Point::operator+(const Point& other)
{
  // ICYW: This is overloading, not overriding lol
  if (this->a != other.a || this->b != other.b) {
    throw std::invalid_argument("Two points are not on the same curve");
  }
  if (this->x == FLT_MAX) { return other; }
  if (other.x == FLT_MAX) { return *this; }
  if (this->x == other.x && this->y != other.y) { 
    return Point(FLT_MAX, FLT_MAX, this->a, this->b);
    }
  throw std::invalid_argument("Impossible!");
}

string Point::toString() {
  return "Point(" + (this->x == FLT_MAX ? "Inf" : to_string(this->x)) + ", "
                  + (this->y == FLT_MAX ? "Inf" : to_string(this->y))  + ")_"
                  + to_string(this->a) + "_" + to_string(this->b);
}

void testPointAddition() {
  Point p1 = Point(-1, -1, 5, 7);
  Point p2 = Point(-1, 1, 5, 7);
  Point pInf = Point(FLT_MAX, FLT_MAX, 5, 7);
  cout << "testPointAddition:\n"
       << (p1 + pInf).toString() << "\n"
       << (p2 + pInf).toString() << "\n"
       << (p1 + p2).toString() << endl;
  
}

int main() {
  Point p1 = Point(-1, -1, 5, 7);
  cout << "p1: "<< p1.toString() << endl;
  try{
    Point p2 = Point(-1, -2, 5, 7); }
  catch (const invalid_argument& ia) {
    cerr << "p2: Invalid argument: " << ia.what() << '\n';
  }
  try{
    Point p3 = Point(2, 4, 5, 7); }
  catch (const invalid_argument& ia) {
    cerr << "p3: Invalid argument: " << ia.what() << '\n';
  }
  try{
    Point p4 = Point(18, 77, 5, 7); }
  catch (const invalid_argument& ia) {
    cerr << "p4: Invalid argument: " << ia.what() << '\n';
  }
  try{
    Point p5 = Point(5, 7, 5, 7); }
  catch (const invalid_argument& ia) {
    cerr << "p5: Invalid argument: " << ia.what() << '\n';
  }
  testPointAddition();
  return 0;
}