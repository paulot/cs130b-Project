#include <iostream>

using std::cout;
using std::endl;

class Point {
    public:
        Point() { }
        Point(const Point &p) {
            x = p.x;
            y = p.y;
            label = p.label;
            parent = p.parent;
        }
        Point(int xx, int yy): x(xx), y(yy) { }
        int x;
        int y;
        int label;
        Rectangle *parent;

        // Methods
        void print() {
            cout << label << " " << x << " " << y << endl;
        }
        bool operator==(Point &p1) {
            return p1.x == x and p1.y == y;
        }
        bool operator!=(Point &p1) {
            return p1.x != x or p1.y != y;
        }
};
