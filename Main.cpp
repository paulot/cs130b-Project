class Rectangle;
class Point;

#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Point.cpp"
#include "Rectangle.cpp"
#include "Map.cpp"
#include "LinkedList.cpp"
#include "CompareFuncts.cpp"
#include "Main-Helpers.cpp"

using std::cout;
using std::cin;

int main() {
    int gridWidth;
    int gridHeight;
    int numRects;
    int origin;
    int printType;
    Point tl;
    Point tr;
    Point br;
    Point bl;
    LinkedList<Point> linkedList;

    cin >> numRects;
    cin >> gridWidth;
    cin >> gridHeight;

    Tuple<Point, LinkedList<Point> >     *pointsByX[4 * numRects];
    Tuple<Rectangle, LinkedList<Point> > *rectangles[numRects];
    int pointsSize = 4 * numRects;

    Map <Point, LinkedList<Point> >     referencePoints     (4 * numRects);
    Map <Rectangle, LinkedList<Point> > referenceRects      (numRects);

    // Add referencePoints in rectangle 
    for (int i = 0, j = 0; i < numRects; i++) {
        cin >> tl.x;
        bl.x = tl.x;
        cin >> tl.y;
        tr.y = tl.y;
        cin >> br.x;
        tr.x = br.x;
        cin >> br.y;
        bl.y = br.y;

        Rectangle rect(-1);
        rectangles[i] = &referenceRects.insert(rect);

        tl.parent = rectangles[i]->key;
        tr.parent = rectangles[i]->key;
        br.parent = rectangles[i]->key;
        bl.parent = rectangles[i]->key;


        pointsByX[j++] = &referencePoints.insert(tl, linkedList);
        pointsByX[j++] = &referencePoints.insert(tr, linkedList);
        pointsByX[j++] = &referencePoints.insert(br, linkedList);
        pointsByX[j++] = &referencePoints.insert(bl, linkedList);
    }
    cin >> origin;
    cin >> printType;

    // TODO: change the sorting stuff!!
    qsort(pointsByX, pointsSize, sizeof(Tuple<Point, LinkedList<Point> > *), comparePointX);
    pointsSize = fixSizeLabelAndX(pointsByX, pointsSize);
    Tuple<Point, LinkedList<Point> > *pointsByY[pointsSize];
    memcpy(pointsByY, pointsByX, sizeof(Tuple<Point, LinkedList<Point> > *) * pointsSize);
    qsort(pointsByY, pointsSize, sizeof(Tuple<Point, LinkedList<Point> > *), comparePointY);
    fixY(pointsByY, pointsSize);

    
    //referencePoints.print();
    for (int i = 0; i < pointsSize; i++) {
        pointsByX[i]->print();
    }
    
    for (int i = 0; i < numRects; i++) {
        rectangles[i]->print();
    }

    return 0;
}
