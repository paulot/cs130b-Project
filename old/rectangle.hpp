#ifndef RECT
#define RECT

// Rectangle defined as such:
// a------------b
// |            |
// |            |
// d------------c
struct Rectangle {
    Vertex *a;  // Top left
    SVertex av;
    Vertex *b;  // Top right
    SVertex bv;
    Vertex *c;  // Bot right
    SVertex cv;
    Vertex *d;  // Bot left
    SVertex dv;
    int label;
    SVertex *next;
    SVertex *end;
    inline void printv() {
        cout << a->label << " " << bv.label << " " << cv.label << " " << dv.label << endl;
    }
    inline void print() {
        if (next == NULL) {
            cout << "NULL" << endl;
            return;
        }
        SVertex *i;
        for (i = next; i->next != NULL; i = i->next) {
            cout << i->label << " ";
        }
        cout << i->label << endl;
    }

    inline void sprint() {
        cout << "rectangle R" << label << " " <<
                d->x << " " << d->y << " " << b->x - a->x <<
                " " << a->y - d->y << " black outline" << endl;
        // text id xp yp cen color string
        /*
        cout << "text p" << label << "1 " << a->x << " " << a->y <<
                " 1 black v" << a->label << endl;
        cout << "text p" << label << "2 " << b->x << " " << b->y <<
                " 1 black v" << b->label << endl;
        cout << "text p" << label << "3 " << c->x << " " << c->y <<
                " 1 black v" << c->label << endl;
        cout << "text p" << label << "4 " << d->x << " " << d->y <<
                " 1 black v" << d->label << endl;
        */
    }
};
#endif
