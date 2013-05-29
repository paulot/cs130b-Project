#define INSERT_RECT(item, arr, size)      \
    arr[size++]   =   item;
#define SO 
#define GET_X(p1) arrayByX[p1.xpos - 1]
#define GET_Y(p1) arrayByY[p1.ypos]


//  Housekeeping for the points array
//      "Removes" duplicates
//      Labels points
//      Fixes parent's label
//      Fixes parent's pointers
//      Adds rectangles that meet at that point
//@Params
//  array
//      Sorted array (by label)
//  size
//      Current size of the array
//
//@Out
//  New size of the array

int fixSizeLabelAndX(Tuple<Point, LinkedList<Point> > *array[], int size) {
    int label = 1;
    int rlabel = 1;
    array[0]->key->label = label;
    array[0]->key->parent->label = rlabel;

    int j = 0;

    for (int i = 1; i < size; i++) {
        // Run along i until they are no equal
        // for all the equal ones label the parent
        // and merge those labels at the first
        while (*(array[j]->key) == *(array[i]->key)) {
            // Update the parent's label
            if (array[i]->key->parent->label == -1) {
                rlabel++;
                array[i]->key->parent->label = rlabel;
            }

            // Update rectangle pointers
            switch (array[i]->key->pos) {
                case TL:
                    array[i]->key->parent->tl = array[j]->key;
                    break;
                case TR:
                    array[i]->key->parent->tr = array[j]->key;
                    break;
                case BR:
                    array[i]->key->parent->br = array[j]->key;
                    break;
                case BL:
                    array[i]->key->parent->bl = array[j]->key;
                    break;
            }
            i++;
        }
        j++;
        label++;
        array[j] = array[i];
        array[j]->key->label = label;
        if (array[j]->key->parent->label == -1) {
            rlabel++;
            array[j]->key->parent->label = rlabel;
        }
    }
    return j + 1;
}

// More housekeeping
// Add ajecencies to points
// Add y positions to points
//
//@Params
//  arrayByX
//      Sorted array (by X-label)
//  arrayByY
//      Sorted array (by Y-label)
//  size
//      Size of the array
//@Out
//  nada
void addAdjecencies(Tuple<Point, LinkedList<Point> > *arrayByX[], 
                    Tuple<Point, LinkedList<Point> > *arrayByY[], 
                    int pointsSize,
                    Tuple<Rectangle, LinkedList<Point> > *rectArray[],
                    int rectSize) {
    for (int i = 0; i < pointsSize; i++) {
        // Add y positions
        arrayByY[i]->key->ypos = i;
    }

    // For every rectangle add the points inside of it
    for (int i = 0; i < rectSize; i++) {
        // For every vertex, add the points inside the rectangle
        Point &tl = *(rectArray[i]->key->tl);
        Point &tr = *(rectArray[i]->key->tr);
        Point &br = *(rectArray[i]->key->br);
        Point &bl = *(rectArray[i]->key->bl);


        // Add the x adjacencies
        GET_X(tl)->value->insert(*arrayByX[tl.xpos]->key, comparePointLabel);
        GET_X(tr)->value->insert(*arrayByX[tr.xpos - 2]->key, comparePointLabel);
        GET_X(bl)->value->insert(*arrayByX[bl.xpos]->key, comparePointLabel);
        GET_X(br)->value->insert(*arrayByX[br.xpos - 2]->key, comparePointLabel);

        // Add the y adjacencies
        GET_Y(tl)->value->insert(*arrayByY[tl.ypos - 1]->key, comparePointLabel);
        GET_Y(bl)->value->insert(*arrayByY[bl.ypos + 1]->key, comparePointLabel);
        GET_Y(tr)->value->insert(*arrayByY[tr.ypos - 1]->key, comparePointLabel);
        GET_Y(br)->value->insert(*arrayByY[br.ypos + 1]->key, comparePointLabel);
    }
}


// Even more housekeeping...
// Add points on the edge of a rectangle
// Starting at the top left and goinf clockwise
// They all go to the list
// WARNING: Highly label dependent :(
void addRectAdjecencies(Tuple <Point, LinkedList<Point> > **pointsByX, 
                        Tuple <Point, LinkedList<Point> > **pointsByY, int pointsSize,
                        Tuple <Rectangle, LinkedList<Point> > **rectangles, int numRects) {
    int j;
    for (int i = 0; i < numRects; i++) {
        // Searches by X
        int tlX = rectangles[i]->key->tl->xpos - 1;
        int trX = rectangles[i]->key->tr->xpos - 1;
        int brX = rectangles[i]->key->br->xpos - 1;
        int blX = rectangles[i]->key->bl->xpos - 1;
        // Searches by Y
        int tlY = rectangles[i]->key->tl->ypos;
        int trY = rectangles[i]->key->tr->ypos;
        int brY = rectangles[i]->key->br->ypos;
        int blY = rectangles[i]->key->bl->ypos;

        /*
        cout << tlX << " " <<
                trX << " " <<
                brX << " " <<
                blX << " " <<
                tlY << " " <<
                trY << " " <<
                brY << " " <<
                blY << " " << "\n";

        for (int f = 0; f < pointsSize; f++) {
            pointsByX[f]->key->print();
            pointsByY[f]->key->print();
        }
        */

        for (j = tlX; j < trX; j++) {
            rectangles[i]->value->insertEnd(*(pointsByX[j]->key));
        }
        for (j = trY; j > brY; j--) {
            rectangles[i]->value->insertEnd(*(pointsByY[j]->key));
        }
        for (j = brX; j > blX; j--) {
            rectangles[i]->value->insertEnd(*(pointsByX[j]->key));
        }
        for (j = blY; j < tlY; j++) {
            rectangles[i]->value->insertEnd(*(pointsByY[j]->key));
        }
    }

}

// Finds the origin point of the graph
//@PARAM
//  originSteps
//      Steps to find the origin
//  pointsByX
//      Array sorted by x-label
//  pointsByY
//      Array sorted by y-label
//  pointsSize
//      size of the arrays
//
//@OUT
//  Point reference to point in the graph
Point &getOrigin(int steps, 
                 Tuple <Point, LinkedList<Point> > **pointsByX, 
                 Tuple <Point, LinkedList<Point> > **pointsByY,
                 int pointsSize) {
    int i = 0;
    int ref;
    int originSteps = steps;
    if (originSteps <= 1)
        return *(pointsByX[i]->key);
    while (originSteps > 1) {
        for (i = 0, originSteps; 
             pointsByX[i]->key->y == pointsByX[0]->key->y and originSteps > 1; 
             i++, originSteps--) {
        }
        if (pointsByX[i]->key->y != pointsByX[0]->key->y)
            originSteps++;
        if (originSteps == 1)
            return *(pointsByX[i]->key);
        i--;

        for (i = pointsByX[i]->key->ypos, originSteps;
             i > 0 and pointsByY[i]->key->x == pointsByY[0]->key->x and originSteps > 1; 
             i--, originSteps--) {
        }
        if (originSteps == 1)
            return *(pointsByY[i]->key);

        ref = pointsByY[i]->key->xpos - 1;
        for (i = ref, originSteps; 
             pointsByX[i]->key->y == pointsByX[ref]->key->y and originSteps > 1; 
             i--, originSteps--) {
        }
        if (pointsByX[i]->key->y != pointsByX[ref]->key->y)
            originSteps++;
        if (originSteps == 1)
            return *(pointsByX[i]->key);

        i--;

        ref = pointsByX[i]->key->ypos;
        for (i = ref, originSteps;
             i < pointsSize and pointsByY[i]->key->x == pointsByY[ref]->key->x and originSteps > 1; 
             i++, originSteps--) {
        }
        i--;
        if (originSteps == 1)
            return *(pointsByY[i]->key);
    } 
}
