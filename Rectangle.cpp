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
                 << bl->label << "\n";
        }
        void printSamba() {
            cout << "rectangle R" << label << " " << bl->x << " " << bl->y <<
                    " " << tr->x - tl->x << " " << tl->y - bl->y << " black outline" << "\n";
            cout << "text T" << label << " " << (tl->x + ((tr->x - tl->x) / 2)) << 
                    " " << (bl->y + ((tl->y - bl->y) / 2)) << " 1 black R" << label << "\n";
        }
        void printSambaPoint() {
            printSamba();
            tl->printSambaLabel();
            tr->printSambaLabel();
            br->printSambaLabel();
            bl->printSambaLabel();
        }
                    
};
