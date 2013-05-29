#include <iostream>

using std::cout;

typedef enum {
    TL = 0,
    TR = 1,
    BR = 2,
    BL = 3
} Positions;

class Point {
    public:
        Point() {
        }
        Point(int p): pos(p) { 
        }
        Point(const Point &p) {
            x = p.x;
            y = p.y;
            label = p.label;
            parent = p.parent;
            pos = p.pos;
        }
        Point(int xx, int yy): x(xx), y(yy) { }
        int x;
        int y;
        union {
            int label;
            int xpos;
        };
        int ypos;
        char pos;
        Rectangle *parent;

        // Methods
        void print() {
            cout << label << " ";
        }
        void print(int xx, int yy) {
            int d = (xx == x) ? y - yy : x - xx;
            if (d < 0) d = -d;
            cout << label << " " << d << " " ;
        }
        void printCoord() {
            cout << label << " " << x << " " << y;
        }
        void printSamba() {
            cout << "circle origin " << x << " " << y <<
                    " 80 black outline" << "\n";
        }
        void printSambaLabel() {
            cout << "text P" << label << " " << x << 
                    " " << y << " 1 black V" << label << "\n";
        }
        bool operator==(Point &p1) {
            return p1.x == x and p1.y == y;
        }
        bool operator!=(Point &p1) {
            return p1.x != x or p1.y != y;
        }
};
