#include <iostream>

template <class T>
class Node {
    public:
        Node(T& i):item(i) { 
            next = NULL;
        };
        T   &item;
        Node<T>   *next;
        void print(void (*fprint) (T &)) {
            fprint(item);
        }
        void print(int x, int y) {
            item.print(x, y);
        }
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
        LinkedList(const LinkedList<T> &l) {
            root = l.root;
            size = l.size;
        }
        ~LinkedList();
        Node<T> &getRoot();
        void insert(T& item, int (*compar) (T& p1, T& p2));
        void insertEnd(T& item);
        // Delete? what's that
        void print();
        void print(void (*fprint)(T &));
        void print(int x, int y);

        int size;
        Node<T>  *root;
        Node<T>  *last;
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
    for (Node<T> *i = root; i != NULL; i = i->next) {
        i->print();
    }
    cout << "\n";
}

template <class T>
void LinkedList<T>::print(void (*fprint)(T &)) {
    if (root == NULL) return;
    for (Node<T> *i = root; i != NULL; i = i->next)
        i->print(fprint);
}

template <class T>
void LinkedList<T>::print(int x, int y) {
    if (root == NULL) return;
    for (Node<T> *i = root; i != NULL; i = i->next)
        i->print(x, y);
}

// PARAMS
//  T item          item to be inserted
//  
// OUT
//  nada
template <class T>
void LinkedList<T>::insertEnd(T& item) {
    if (root == NULL) {
        root = new Node<T>(item);
        last = root;
        size++;
    } else {
        last->next = new Node<T>(item);
        last = last->next;
        size++;
    }
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
        last = root;
        size++;
        return;
    } else {
        Node<T> *first = root;
        Node<T> *second = root->next;
        if (compar(item, first->item) < 0) { // item is before
            root = new Node<T>(item);
            root->next = first;
            size++;
            return;
        } else if (compar(item, first->item) == 0) {
            return;
        } else {                             // item is after
            if (second == NULL) {
                    // NULL set?
                    first->next = new Node<T>(item);
                    last = first->next;
                    size++;
                    return;
            } else {                         // item is after
                for (first, second;
                     second->next != NULL and (compar(item, second->item) > 0);
                     first = first->next, second = second->next);

                if (compar(item, first->item) > 0 and compar(item, second->item) < 0) {
                    // In between them
                    first->next = new Node<T>(item);
                    first->next->next = second;
                    size++;
                    return;
                } else if (compar(item, first->item) == 0 or compar(item, second->item) == 0) {
                    return;
                } else {
                    second->next = new Node<T>(item);
                    last = second->next;
                    size++;
                    return;
                }
            }
        }
    }
}

template <class T>
Node<T>& LinkedList<T>::getRoot() {
    return root;
}

