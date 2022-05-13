#include <iostream>

struct Point {
    int x;
    int y;

    void IncX() {
        x = x + 1;
    }
};

void fun(Point p) {
    p.x;
    p.y;
}
Point fun1(Point p) {
    p.x = p.x + 1;
    return p;
}
int main() {
     Point p;
     p.x = 3;
     p.y = 5;
     p = fun1(p);
     std::cout << p.x << ' ' << p.y << '\n';
     p.IncX();
     std::cout << p.x << ' ' << p.y << '\n';
}
