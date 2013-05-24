#include <iostream>

template <class T>
class Tuple {
    public:
        Tuple(T& i):item(i) { 
            next = NULL;
        };
        T   &item;
        Tuple<T>   *next;
        void print() {
            item.print();
        }
};

template <class T>
class LinkedList {
    public:
        LinkedList(){
            root = NULL;
            size = 0;
        }
        ~LinkedList();
        Tuple<T> &getRoot();
        void insert(T& item, int (*compar) (T& p1, T& p2));
        // Delete? what's that
        void print();

    private:
        int size;
        Tuple<T>  *root;
};

template <class T>
LinkedList<T>::~LinkedList() {
    if (root == NULL) return;
    Tuple<T>* first = root;
    Tuple<T>* second = root->next;
    for (first, second;
         second != NULL;
         first = second, second = second->next)
        delete first;
}

template <class T>
void LinkedList<T>::print() {
    if (root == NULL) return;
    for (Tuple<T> *i = root; i != NULL; i = i->next)
        i->print();
}
     

// PARAMS
//  T   item        item to be inserted
//  (int)(*)        function to compare items
//          the comaprison fuction must return - if p1 comes
//          before p1, 0 if they're the same, + if p2 comes 
//          before p1
// OUT
//  nothing
template <class T>
void LinkedList<T>::insert(T& item, int (*compar) (T& p1, T& p2)) {
    if (root == NULL) {
        root = new Tuple<T>(item);
        size++;
    } else {
        Tuple<T> *first = root;
        Tuple<T> *second = root->next;
        if (compar(item, first->item) < 0) { // item is before
            root = new Tuple<T>(item);
            root->next = first;
            size++;
        } else {                             // item is after
            if (second == NULL) {
                    // NULL set?
                    first->next = new Tuple<T>(item);
                    size++;
            } else {                         // item is after
                for (first, second;
                     second->next != NULL and (compar(item, second->item) > 0);
                     first = first->next, second = second->next);

                if (compar(item, first->item) > 0 and compar(item, second->item) < 0) {
                    // In between them
                    first->next = new Tuple<T>(item);
                    first->next->next = second;
                    size++;
                } else {
                    second->next = new Tuple<T>(item);
                    size++;
                }
            }
        }
    }
}

template <class T>
Tuple<T>& LinkedList<T>::getRoot() {
    return root;
}

