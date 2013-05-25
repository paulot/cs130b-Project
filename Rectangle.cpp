#include <iostream>

using std::cout;

class Rectangle {
    public:
        Rectangle(int l): label(l) { }
        Point *tl;
        Point *tr;
        Point *br;
        Point *bl;
        int label;

        void print() {
            cout << tl->label << " "
                 << tr->label << " "
                 << br->label << " "
                 << bl->label << endl;
        }
};
