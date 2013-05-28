#include <iostream>

using namespace std;
#include "LinkedList.cpp"


class Point {
    public:
        int x;
        int y;
        void print() {
            cout << x << " " << y << endl;
        }
};

int compare (Point &p1, Point &p2) {
    return p1.x - p2.x;
}

int compar (Point &p1, Point &p2) {
    return p1.y - p2.y;
}

int main() {
    Point p1;
    p1.x = 300;
    p1.y = 700;

    Point p2;
    p2.x = 400;
    p2.y = 800;
    
    Point p3;
    p3.x = 500;
    p3.y = 200;

    Point p4;
    p4.x = 600;
    p4.y = 40;

    Point p5;
    p5.x = 700;
    p5.y = 900;

    Point p6;
    p6.x = 800;
    p6.y = 500;

    LinkedList<Point> linkedlist;
    linkedlist.insert(p2, &compare);
    linkedlist.insert(p3, &compare);
    linkedlist.insert(p5, &compare);
    linkedlist.insert(p1, &compare);
    linkedlist.insert(p4, &compare);
    linkedlist.insert(p6, &compare);
    linkedlist.print();


    LinkedList<Point> ll;
    ll.insertEnd(p2);
    ll.insertEnd(p3);
    ll.insertEnd(p5);
    ll.insertEnd(p1);
    ll.insertEnd(p4);
    ll.insertEnd(p6);
    ll.print();

    return 0;
}
