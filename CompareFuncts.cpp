
int comparePointX(Tuple<Point, LinkedList<Point> > *&p1, Tuple<Point, LinkedList<Point> > *&p2) {
    return not ((p1->key->y == p2->key->y and p1->key->x < p2->key->x) 
                or p1->key->y > p2->key->y);
}


int comparePointY(Tuple<Point, LinkedList<Point> > *&p1, Tuple<Point, LinkedList<Point> > *&p2) {
    return not ((p1->key->x == p2->key->x and p1->key->y < p2->key->y) 
                or p1->key->x > p2->key->x);
}

int compareRectLabel(Tuple<Rectangle, LinkedList<Point> > *&p1, Tuple<Rectangle, LinkedList<Point> > *&p2) {
    return p1->key->label - p2->key->label;
}

int comparePointLabel(Point &p1, Point &p2) {
    return p1.label - p2.label;
}

int comparePointX(const void *pa, const void *pb) {
    Point *p1 = (*(Tuple<Point, LinkedList<Point> > **) pa)->key;
    Point *p2 = (*(Tuple<Point, LinkedList<Point> > **) pb)->key;
    return not ((p1->y == p2->y and p1->x < p2->x) 
                or p1->y > p2->y);
}

int comparePointY(const void *pa, const void *pb) {
    Point *p1 = (*(Tuple<Point, LinkedList<Point> > **) pa)->key;
    Point *p2 = (*(Tuple<Point, LinkedList<Point> > **) pb)->key;
    return not ((p1->x == p2->x and p1->y < p2->y) 
                or p1->x > p2->x);
}

int compareRectLabel(const void *p1, const void *p2) {
    return ((*(Tuple<Rectangle, LinkedList<Point> > **) p1)->key->label) - 
            ((*(Tuple<Rectangle, LinkedList<Point> > **) p2)->key->label);
}
