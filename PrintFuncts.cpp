
void printLabel(Point &p) {
    cout << p.label << " ";
}

template <class T, class Y>
void printKey(T *k, Y *v) {
    k->print();
}

template <class T, class Y>
void printRectVal(T *k, Y *v) {
    v->print();
}
