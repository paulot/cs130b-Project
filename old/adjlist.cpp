#include <cstdlib>
#include "tuple.hpp"
#include "helpers.cpp"

#define MINSIZE 100

// An adjecency list class
template <class T>
class AdjList {
    public:
        AdjList(int s, int xs, int ys);
        ~AdjList();

        T& insert(T &item);
        // T& insert(T &item, Y &list);
        void shrink();
        void print();
        void sprint();          // Samba print
        void sort();
        void rsort();
        void label();
        void addXAdj();
        void addYAdj();

        void addAdjVert(Vertex *list, int n);
        void addAdjYVert(Vertex *list, int n);

        T&   operator[](int i) {
            return adjlist[i];
        }

        int index;
        T *adjlist;

        void updateParents();
        void sortY();
        void rmDuplicates();
    private:
        int size;
        int count;
        void Double();
        bool hash(T &p1, T &p2);
        // Tuple<T, Y> *adjlist;  // Dynamically allocated array of tuples
};

template <class T>
AdjList<T>::AdjList(int s, int xs, int ys) {
    size    = s;
    index   = 0;
    adjlist = new T[size];
}

template <class T>
AdjList<T>::~AdjList() {
    // TODO: Fix this
    delete [] adjlist;
}

template <class T>
void AdjList<T>::shrink() {
    size = count + 1;
    T *newlist = new T[size];
    // TODO: Try to do the following in constant time
    for (int i = 0; i < size; i++)
        newlist[i] = adjlist[i];
    delete [] adjlist;
    adjlist = newlist;
}

template <class T>
T& AdjList<T>::insert (T &item) {
    // Will never need to resize
    adjlist[index++] = item;
    return adjlist[index - 1];
}

template <class T>
void AdjList<T>::print() {
    for (int i = 0; i < index; i++) {
        adjlist[i].print();
        printList(adjlist[i].next);
        cout << endl;
    }
}

template <class T>
void AdjList<T>::sprint() {
    for (int i = 0; i < index; i++) {
        cout << "text V" << i << " " << adjlist[i].x << " " << adjlist[i].y << 
                " true black V" << adjlist[i].label << endl;
    }
}

template <class T>
void AdjList<T>::sort() {
    qsort(adjlist, index, sizeof(T), compare<T>);
}

template <class T>
void AdjList<T>::sortY() {
    qsort(adjlist, index, sizeof(T), compareY<T>);
}

template <class T>
void AdjList<T>::rsort() {
    qsort(adjlist, index, sizeof(T), rcomp<T>);
}

template <class T>
void AdjList<T>::label() {
    int label = 1;
    T ref = adjlist[0];
    adjlist[0].label = label;

    for (int i = 1; i < index; i++) {
        if (adjlist[i].x == ref.x and adjlist[i].y == ref.y) { 
            adjlist[i].label = label;
        } else {
            label++;
            ref = adjlist[i];
            adjlist[i].label = label;
        }

    }
}

template <class T>
void AdjList<T>::rmDuplicates() {
    int rlabel = 1;
    adjlist[0].parent->label = rlabel;
    adjlist[0].parent->av = adjlist[0].label;
    adjlist[0].parent->a = &adjlist[0];
    adjlist[0].rlabel = adjlist[0].parent->label;

    int j = 0;

    for (int i = 1; i < index; i++) {
        if (adjlist[i] != adjlist[j]) {
            j++; 
            adjlist[j] = adjlist[i];

        } 

        // Update i parent's label
        if (adjlist[i].pos == TL and adjlist[i].parent->label == -1) {
            rlabel++;
            adjlist[i].parent->label = rlabel;
        }

        // Update i's parent to point to j
        switch (adjlist[i].pos) {
            case TL:
                adjlist[i].parent->a = &adjlist[j];
                adjlist[i].parent->av = adjlist[j].label;
                break;
            case TR:
                adjlist[i].parent->b = &adjlist[j];
                adjlist[i].parent->bv = adjlist[j].label;
                break;
            case BR:
                adjlist[i].parent->c = &adjlist[j];
                adjlist[i].parent->cv = adjlist[j].label;
                break;
            case BL:
                adjlist[i].parent->d = &adjlist[j];
                adjlist[i].parent->dv = adjlist[j].label;
                break;
        }
        adjlist[j].rlabel = adjlist[i].parent->label;
    } 
    index = j + 1;
}

template <class T>
void AdjList<T>::updateParents() {
    for (int i = 1; i < index; i++) {
    }
}

template <class T>
void AdjList<T>::addAdjYVert(Vertex *list, int n) {
    // For every rectangle find av and add till bv
    for (int i = 0; i < index; i++) {
        for (int j = 0; j < n; j++) {
            if (adjlist[i].cv.label == list[j].label) {
                for (int z = j + 1; z < n; z++) {
                    if (list[z].label == adjlist[i].bv.label)
                        break;
                    addSSList(adjlist[i].next, adjlist[i].end, list[z].label);
                }
            } else if (adjlist[i].dv.label == list[j].label) {
                for (int z = j + 1; z < n; z++) {
                    if (list[z].label == adjlist[i].av.label)
                        break;
                    addSSList(adjlist[i].next, adjlist[i].end, list[z].label);
                }
                break;
            }
        }
    }
}

template <class T>
void AdjList<T>::addAdjVert(Vertex *list, int n) {
    // For every rectangle find av and add till bv
    for (int i = 0; i < index; i++) {
        for (int j = 0; j < n; j++) {
            if (adjlist[i].av.label == list[j].label) {
                for (int z = j; z < n; z++) {
                    addSSList(adjlist[i].next, adjlist[i].end, list[z].label);
                    if (list[z].label == adjlist[i].bv.label)
                        break;
                }
            } else if (adjlist[i].dv.label == list[j].label) {
                for (int z = j; z < n; z++) {
                    addSSList(adjlist[i].next, adjlist[i].end, list[z].label);
                    if (list[z].label == adjlist[i].cv.label)
                        break;
                }
                break;
            }
        }
    }
}

// Add adjacent nodes on X
template <class T>
void AdjList<T>::addXAdj() {
    addList(adjlist[0].next,
            adjlist[1].label,
            adjlist[1].x - adjlist[0].x,
            adjlist[1].x,
            adjlist[1].y);
    // add adj vertexes on adjancecy list and union them
    for (int i = 1; i < index - 1; i++) {
        // Add adj vertexes based on list
        if (adjlist[i - 1].y == adjlist[i].y) {
            // cout << "Adding adj1" << endl;
            addList(adjlist[i].next,
                    adjlist[i - 1].label,
                    adjlist[i].x - adjlist[i - 1].x,
                    adjlist[i - 1].x,
                    adjlist[i - 1].y);
        }
        if (adjlist[i + 1].y == adjlist[i].y) {
            // cout << "Adding adj3" << endl;
            addList(adjlist[i].next,
                    adjlist[i + 1].label,
                    adjlist[i + 1].x - adjlist[i].x,
                    adjlist[i + 1].x,
                    adjlist[i + 1].y);
        }
    }
    addList(adjlist[index - 1].next,
            adjlist[index - 2].label,
            adjlist[index - 1].x - adjlist[index - 2].x,
            adjlist[index - 2].x,
            adjlist[index - 2].y);
}

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

