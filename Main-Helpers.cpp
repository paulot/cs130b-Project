
//  Housekeeping for the points array
//      "Removes" duplicates
//      Labels points
//      Adds adjecent items on the x
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
        if (*(array[i]->key) != *(array[j]->key)) {
            j++;
            label++;
            array[j] = array[i];
            array[j]->key->label = label;
            // Add X adjecencies:
            //      Add the last element (j-1) to your list
            //      Add the current element (j) to the last list's
            if (array[j - 1]->key->y == array[j]->key->y) {
                array[j - 1]->value->insert(*(array[j]->key), comparePointLabel);
                array[j]->value->insert(*(array[j - 1]->key), comparePointLabel);
            }
            // Update the parent's label
            if (array[j]->key->parent->label == -1) {
                rlabel++;
                array[j]->key->parent->label = rlabel;
            }
        }
    }
    return j + 1;
}

// More housekeeping
// Add adjecent points on a Y-sorted array
//
//@Params
//  array
//      Sorted array (by Y-label)
//  size
//      Size of the array
//@Out
//  nada

void fixY(Tuple<Point, LinkedList<Point> > *array[], int size) {
    for (int i = 1; i < size; i++) {
        if (array[i - 1]->key->x == array[i]->key->x) {
                array[i - 1]->value->insert(*(array[i]->key), comparePointLabel);
                array[i]->value->insert(*(array[i - 1]->key), comparePointLabel);
        }
    }
}

/*
// Add adjacent nodes on Y
template <class T>
void AdjList<T>::addYAdj() {
    addList(adjlist[0].next,
            adjlist[1].label,
            adjlist[1].y - adjlist[0].y,
            adjlist[1].x,
            adjlist[1].y);
    // add adj vertexes on adjancecy list and union them
    for (int i = 1; i < index - 1; i++) {
        // Add adj vertexes based on list
        if (adjlist[i - 1].x == adjlist[i].x) {
            // cout << "Adding adj1" << endl;
            addList(adjlist[i].next,
                    adjlist[i - 1].label,
                    adjlist[i].y - adjlist[i - 1].y,
                    adjlist[i - 1].x,
                    adjlist[i - 1].y);
        }
        if (adjlist[i + 1].x == adjlist[i].x) {
            // cout << "Adding adj3" << endl;
            addList(adjlist[i].next,
                    adjlist[i + 1].label,
                    adjlist[i + 1].y - adjlist[i].y,
                    adjlist[i + 1].x,
                    adjlist[i + 1].y);
        }
    }
    addList(adjlist[index - 1].next,
            adjlist[index - 2].label,
            adjlist[index - 1].y - adjlist[index - 2].y,
            adjlist[index - 2].x,
            adjlist[index - 2].y);
}
*/
