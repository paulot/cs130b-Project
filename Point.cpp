#include <iostream>

using std::cout;
using std::endl;

typedef enum {
    TL = 0,
    TR = 1,
    BR = 2,
    BL = 3
} Positions;

class Point {
    public:
        Point() {
            rectanglesSize = 0;
        }
        Point(int p): pos(p) { 
            rectanglesSize = 0;
        }
        Point(const Point &p) {
            x = p.x;
            y = p.y;
            label = p.label;
            parent = p.parent;
            pos = p.pos;
            rectanglesSize = p.rectanglesSize;
            for (int i = 0; i < rectanglesSize; i++)
                rectangles[i] = p.rectangles[i];
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
        // Set of rectangles that this point belongs to
        int rectangles[4];
        int rectanglesSize;

        void printRect() {
            cout << label << " ";
            for (int i = 0; i < rectanglesSize; i++)
                cout << rectangles[i] << " ";
        }
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
                    " 80 black outline" << endl;
        }
        void printSambaLabel() {
            cout << "text P" << label << " " << x << 
                    " " << y << " 1 black V" << label << endl;
        }
        bool operator==(Point &p1) {
            return p1.x == x and p1.y == y;
        }
        bool operator!=(Point &p1) {
            return p1.x != x or p1.y != y;
        }
};
