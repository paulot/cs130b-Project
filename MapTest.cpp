#include <iostream>
#include "Map.cpp"
#include "LinkedList.cpp"

using namespace std;

class Point {
    public:
        int x;
        int y;
        void print() {
            cout << x << " " << y << endl;
        }
        bool operator==(Point &p1) {
            return p1.x == x and p1.y == y;
        }
};

int compare (Point &p1, Point &p2) {
        return p1.x - p2.x;
}

int compar (Point &p1, Point &p2) {
        return p1.y - p2.y;
}

int cmp (Point &p1, Point &p2) {
        return p1.y * p2.y - p1.x * p2.x;
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
    cout << "List 1" << endl;
    linkedlist.print();


    LinkedList<Point> ll;
    ll.insert(p2, &compar);
    ll.insert(p3, &compar);
    ll.insert(p5, &compar);
    ll.insert(p1, &compar);
    ll.insert(p4, &compar);
    ll.insert(p6, &compar);
    cout << "List 2" << endl;
    ll.print();


    LinkedList<Point> llp;
    llp.insert(p2, &cmp);
    llp.insert(p3, &cmp);
    llp.insert(p5, &cmp);
    llp.insert(p1, &cmp);
    llp.insert(p4, &cmp);
    llp.insert(p6, &cmp);
    cout << "List 3" << endl;
    llp.print();

    
    cout << "map" << endl;
    Map<Point, LinkedList<Point> > mymap(10);
    mymap.insert(p1, ll);
    mymap.insert(p2, ll);
    mymap.insert(p3, ll);
    mymap.insert(p4, ll);
    mymap.insert(p5, llp);
    mymap.insert(p4, llp);
    mymap.insert(p2, llp);
    mymap.insert(p6, linkedlist);
    mymap.insert(p2, linkedlist);
    mymap.insert(p4, linkedlist);
    mymap.print();

    cout << "Testing []" << endl;
    mymap[1].print();
    cout << endl;
    mymap[2].print();
    cout << endl;
    mymap[3].print();
    
    cout << (p1 == p1) << endl;
    cout << (p1 == p2) << endl;
    cout << (p1 == p3) << endl;
    cout << (p1 == p4) << endl;
    cout << (p6 == p6) << endl;

    mymap[p2].print();
    cout << endl;
    mymap[p3].print();
    cout << endl;
    mymap[p4].print();
}
