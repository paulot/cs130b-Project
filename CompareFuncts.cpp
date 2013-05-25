
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

int comparePointLabel(Point &p1, Point &p2) {
    return p1.label - p2.label;
}
