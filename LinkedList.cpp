#include <iostream>

template <class T>
class Node {
    public:
        Node(T& i):item(i) { 
            next = NULL;
        };
        T   &item;
        Node<T>   *next;
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
        Node<T> &getRoot();
        void insert(T& item, int (*compar) (T& p1, T& p2));
        // Delete? what's that
        void print();

    private:
        int size;
        Node<T>  *root;
};

template <class T>
LinkedList<T>::~LinkedList() {
    if (root == NULL) return;
    Node<T>* first = root;
    Node<T>* second = root->next;
    for (first, second;
         second != NULL;
         first = second, second = second->next)
        delete first;
}

template <class T>
void LinkedList<T>::print() {
    if (root == NULL) return;
    for (Node<T> *i = root; i != NULL; i = i->next)
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
        root = new Node<T>(item);
        size++;
    } else {
        Node<T> *first = root;
        Node<T> *second = root->next;
        if (compar(item, first->item) < 0) { // item is before
            root = new Node<T>(item);
            root->next = first;
            size++;
        } else {                             // item is after
            if (second == NULL) {
                    // NULL set?
                    first->next = new Node<T>(item);
                    size++;
            } else {                         // item is after
                for (first, second;
                     second->next != NULL and (compar(item, second->item) > 0);
                     first = first->next, second = second->next);

                if (compar(item, first->item) > 0 and compar(item, second->item) < 0) {
                    // In between them
                    first->next = new Node<T>(item);
                    first->next->next = second;
                    size++;
                } else {
                    second->next = new Node<T>(item);
                    size++;
                }
            }
        }
    }
}

template <class T>
Node<T>& LinkedList<T>::getRoot() {
    return root;
}

