#ifndef RECT
#define RECT

#include "hashtable.cpp"

#define printlbl(af, bf, cf, df, ox)                                          \
        cout << af->label << " ";                                             \
        for (AdjVertex *i = af->next; i != NULL; i = i->next) {               \
            if (ox) {                                                         \
                if (i->label != bf->label and                                 \
                    i->label != cf->label and                                 \
                    i->label != df->label and                                 \
                    i->x >= a->x and                                          \
                    i->x <= b->x and                                          \
                    i->y == af->y and                                         \
                    not adjs.isPresent(i->label)) {                           \
                    adjs.insert(i->label);                                    \
                    i->fudgePrint();                                          \
                }                                                             \
            } else {                                                          \
                if (af->label == 27) {                                        \
                    cout << "looking at " << i->label << endl;                \
                    cout << (i->label != bf->label) << endl;                    \
                    cout << (i->label != cf->label) << endl;                    \
                    cout << (i->label != df->label) << endl;                    \
                    cout << (i->y <= a->y) << endl;                             \
                    cout << (i->y >= c->y) << endl;                             \
                    cout << (i->x == af->x) << endl;                            \
                    cout << (not adjs.isPresent(i->label)) << endl;             \
                }                                                             \
                if (i->label != bf->label and                                 \
                    i->label != cf->label and                                 \
                    i->label != df->label and                                 \
                    i->y <= a->y and                                          \
                    i->y >= c->y and                                          \
                    i->x == af->x and                                         \
                    not adjs.isPresent(i->label)) {                           \
                    adjs.insert(i->label);                                    \
                    i->fudgePrint();                                          \
                }                                                             \
            }                                                                 \
        }

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
        cout << av.label << " " << bv.label << " " << cv.label << " " << dv.label << endl;
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

    inline void fudgePrint() {
        fudgeTable adjs(4);

        printlbl(a, b, c, d, true)
        printlbl(b, c, d, a, false);
        printlbl(c, d, a, b, true);
        printlbl(d, c, b, a, false);

        cout << endl;
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
