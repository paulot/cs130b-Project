#include <iostream>

typedef enum { TL = 1,
               TR = 2,
               BR = 3,
               BL = 4 } VType;

using namespace std;
struct Rectangle;
#include "vertex.hpp"
#include "adjlist.cpp"
#include "rectangle.hpp"

int main() {
    int gridSizeX, gridSizeY;
    int numRect;

    cin >> numRect;
    cin >> gridSizeX;
    cin >> gridSizeY;

    AdjList<Vertex>     vertexList1(numRect * 4, gridSizeX, gridSizeY);     // Maintains vertexes and their connections

    AdjList<Rectangle>  rectList(numRect, gridSizeX, gridSizeY);
    // Rectangle rects[numRect];

    for (int i = 0; i < numRect; i++) {
        // Define the vertexes
        Vertex a;
        Vertex b;
        Vertex c;
        Vertex d;
        // Fill them out
        cin >> a.x;
        d.x = a.x;
        cin >> a.y;
        b.y = a.y;
        cin >> c.x;
        b.x = c.x;
        cin >> c.y;
        d.y = c.y;

        a.next = NULL;
        b.next = NULL;
        c.next = NULL;
        d.next = NULL;

        Rectangle rect;
        rect.label = -1;
        Rectangle *r = &rectList.insert(rect);

        r->next = NULL;
        r->end = NULL;

        a.parent = r;
        b.parent = r;
        c.parent = r;
        d.parent = r;

        a.pos = TL;
        b.pos = TR;
        c.pos = BR;
        d.pos = BL;

        vertexList1.insert(a);
        vertexList1.insert(b);
        vertexList1.insert(c);
        vertexList1.insert(d);
    }

    int origin;
    int printType;

    cin >> origin;
    cin >> printType;

    if (printType == 1) {
        vertexList1.sort();
        vertexList1.label();
        vertexList1.rmDuplicates();
        vertexList1.addXAdj();

        rectList.rsort();
        rectList.addAdjVert(vertexList1.adjlist, vertexList1.index);

        vertexList1.sortY();
        rectList.addAdjYVert(vertexList1.adjlist, vertexList1.index);
        vertexList1.addYAdj();

        for (int i = 0; i < numRect; i++) {
            rectList[i].print();
        }
        for (int i = 0; i < numRect; i++) {
            rectList[i].printv();
        }

        vertexList1.sort();
        vertexList1.print();
    } else if (printType == 2) { // Samba print
        vertexList1.sort();
        vertexList1.label();
        // Delete repeated
        vertexList1.rmDuplicates();
        for (int i = 0; i < numRect; i++)
            rectList[i].sprint();
        vertexList1.sprint();
    }

    return 0;
}
