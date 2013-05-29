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
#include "PrintFuncts.cpp"
#include "Sort.hpp"



using std::cout;
using std::cin;

int main() {
    int gridWidth;
    int gridHeight;
    int numRects;
    int originSteps;
    int printType;
    Point tl(TL);
    Point tr(TR);
    Point br(BR);
    Point bl(BL);
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
        rectangles[i] = &referenceRects.insert(rect, linkedList);

        tl.parent = rectangles[i]->key;
        tr.parent = rectangles[i]->key;
        br.parent = rectangles[i]->key;
        bl.parent = rectangles[i]->key;


        pointsByX[j] = &referencePoints.insert(tl, linkedList);
        rectangles[i]->key->tl = pointsByX[j++]->key;
        pointsByX[j] = &referencePoints.insert(tr, linkedList);
        rectangles[i]->key->tr = pointsByX[j++]->key;
        pointsByX[j] = &referencePoints.insert(br, linkedList);
        rectangles[i]->key->br = pointsByX[j++]->key;
        pointsByX[j] = &referencePoints.insert(bl, linkedList);
        rectangles[i]->key->bl = pointsByX[j++]->key;
    }
    cin >> originSteps;
    cin >> printType;

#define pointEnd sizeof(Tuple<Point, LinkedList<Point> > *)
#define rectEnd  sizeof(Tuple<Rectangle, LinkedList<Point> > *)
#define pointStart pointsSize
#define rectStart numRects
    // qsort from Sort.hpp
    qsort(pointsByX, pointsSize, sizeof(Tuple<Point, LinkedList<Point> > *), comparePointX);
    // qsort<Tuple<Point, LinkedList<Point> > *>(pointsByX, 0, pointsSize - 1, comparePointX);

    pointsSize = fixSizeLabelAndX(pointsByX, pointsSize);

    Tuple<Point, LinkedList<Point> > *pointsByY[pointsSize];
    memcpy(pointsByY, pointsByX, sizeof(Tuple<Point, LinkedList<Point> > *) * pointsSize);

    // qsort from Sort.hpp
    qsort(pointsByY, pointsSize, sizeof(Tuple<Point, LinkedList<Point> > *), comparePointY);
    // qsort<Tuple<Point, LinkedList<Point> > *>(pointsByY, 0, pointsSize - 1, comparePointY);

    // qsort from Sort.hpp
    qsort(rectangles, numRects,  sizeof(Tuple<Rectangle, LinkedList<Point> > *), compareRectLabel);
    // qsort<Tuple<Rectangle, LinkedList<Point> > *>(rectangles, 0, numRects - 1, compareRectLabel);
    if (printType == 1) {
        addAdjecencies(pointsByX, pointsByY, pointsSize, rectangles, numRects);
        addRectAdjecencies(pointsByX, pointsByY, pointsSize, rectangles, numRects);
        

        /*
        for (int i = 0; i < pointsSize; i++) {
            pointsByX[i]->key->printRect();
            cout << "\n";
        }
        */
        //referencePoints.print();
        for (int i = 0; i < numRects; i++) {
            rectangles[i]->print(&printRectVal<Rectangle, LinkedList<Point> >);
        }
        for (int i = 0; i < numRects; i++) {
            rectangles[i]->print(&printKey<Rectangle, LinkedList<Point> >);
        }
        for (int i = 0; i < pointsSize; i++) {
            cout << i+1 << " " << pointsByX[i]->key->x << " " << pointsByX[i]->key->y << " ";
            pointsByX[i]->value->print(pointsByX[i]->key->x, pointsByX[i]->key->y);
            cout << "\n";
        }
    } else if (printType == 2) {
        // cout << "viewdef view " << gridWidth << " " << gridHeight << "\n";
        cout << "view MyView" << "\n";
        Point &origin = getOrigin(originSteps, pointsByX, pointsByY, pointsSize);
        origin.printSamba();
        for (int i = 0; i < numRects; i++) {
            rectangles[i]->key->printSambaPoint();
        }
    }

    return 0;
}
