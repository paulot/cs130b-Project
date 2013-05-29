#ifndef SO
#define SO
// Swap tuples
#define SWAP(a, b, tmp)               \
  tmp      = array[a];                \
  array[a] = array[b];                \
  array[b] = tmp;

#define MAX_THRESH 4

void qsort (Tuple<Point, LinkedList<Point> > * array[], int begin, int end, int (*compare)(Tuple<Point, LinkedList<Point> > * &, Tuple<Point, LinkedList<Point> > * &)) {
    if (end - begin <= 1) return;
    Tuple<Point, LinkedList<Point> > * tmp;
    // Use insertion sort if the size is smaller than thresh, one of Sedgewick's
    // optimizations
    if (begin - end + 1 <= MAX_THRESH) {
        int i, j;
        for (i = begin + 1; i <= end; i++) {
            j = i;
            while (j > 0 and (*compare)(array[j - 1], array[j]) > 0) {
                SWAP(j - 1, j, tmp);
                j--;
            }
        }
        return;
    }
    
    register int low = begin;
    register int hi  = end;
    register int mid = (hi + low) >> 1;

    // Order pivot, hi and low
    if ((*compare)(array[mid], array[low]) < 0) {
        SWAP(mid, low, tmp);
    } 
    if ((*compare)(array[hi], array[mid]) < 0) {
        SWAP(mid, hi, tmp);
    } else {
        goto jump;
    } if ((*compare)(array[mid], array[low]) > 0) {
        SWAP(mid, hi, tmp);
    }

jump:

    // Now they are somewhat in place
    low++;
    hi--;

    while (low <= hi) {
        while ((*compare)(array[low], array[mid]) < 0)
            low++;
        while ((*compare)(array[mid], array[hi])  < 0)
            hi--;
        if (low < hi) {
            SWAP(low, hi, tmp);
            hi--;
            low++;
        } else if (low == hi) {
            low++;
            hi--;
            break;
        }
    }

    if (begin < hi) {
        psort(array, begin, hi, compare);
    }
    if (low < end) {
        psort(array, low, end, compare);
    }
}

void qsort (Tuple<Rectangle, LinkedList<Point> > ** array[], int begin, int end, int (*compare)(Tuple<Rectangle, LinkedList<Point> > ** &, Tuple<Rectangle, LinkedList<Point> > ** &)) {
    if (end - begin <= 1) return;
    Tuple<Rectangle, LinkedList<Point> > ** tmp;
    if (begin - end + 1 <= MAX_THRESH) {
        int i, j;
        for (i = begin + 1; i <= end; i++) {
            j = i;
            while (j > 0 and (*compare)(array[j - 1], array[j]) > 0) {
                SWAP(j - 1, j, tmp);
                j--;
            }
        }
        return;
    }
    
    register int low = begin;
    register int hi  = end;
    register int mid = (hi + low) >> 1;

    // Order pivot, hi and low
    if ((*compare)(array[mid], array[low]) < 0) {
        SWAP(mid, low, tmp);
    } 
    if ((*compare)(array[hi], array[mid]) < 0) {
        SWAP(mid, hi, tmp);
    } else {
        goto jump;
    } if ((*compare)(array[mid], array[low]) > 0) {
        SWAP(mid, hi, tmp);
    }

jump:

    // Now they are somewhat in place
    low++;
    hi--;

    while (low <= hi) {
        while ((*compare)(array[low], array[mid]) < 0)
            low++;
        while ((*compare)(array[mid], array[hi])  < 0)
            hi--;
        if (low < hi) {
            SWAP(low, hi, tmp);
            hi--;
            low++;
        } else if (low == hi) {
            low++;
            hi--;
            break;
        }
    }

    if (begin < hi) {
        psort(array, begin, hi, compare);
    }
    if (low < end) {
        psort(array, low, end, compare);
    }
}
#endif
