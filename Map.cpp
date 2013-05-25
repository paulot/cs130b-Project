#include <iostream>
#include "Sort.cpp"

using namespace std;

// A Tuple to store key value pairs from the map class
template <class T, class Y>
class Tuple {
    public:
        Tuple() { 
            key = NULL;
            value = NULL;
        }
        Tuple(T& k, Y& v) {
            key = &k;
            value = &v;
        }
        T *key;
        Y *value;
        void print() {
            if (key != NULL)
                key->print();
            if (value != NULL)
                value->print();
        }
};

// Map Class
// T:   The type of key of the Map
// Y:   The type of the value of the Map
//
// A simple map class implemented as an array of Tuples
//
template <class T, class Y>
class Map {
    public:
        Map(int s): size(s) {
            index = 0;
            array = new Tuple<T,Y>[size];
        }
        ~Map();

        void insert(T& key);
        void insert(T& key, Y& value);

        // Search by array index (for fast sorting)
        Tuple<T,Y>& operator[] (int i);
        // Search by item
        Y&          operator[] (T& item);

        void print();
        void sort(int (*compar)(T &p1, T &p2));
    private:
        int size;
        int index;
        Tuple<T,Y> *array;
};

template <class T, class Y>
Map<T,Y>::~Map() {
    // That's what it allocates, that's what it deletes
    delete[] array;
}

template <class T, class Y>
void Map<T,Y>::insert(T& key) {
    array[index].key = &key;
    index++;
}

template <class T, class Y>
void Map<T,Y>::insert(T& key, Y& value) {
    array[index].key = &key;
    array[index].value = &value;
    index++;
}

template <class T, class Y>
Tuple<T,Y>& Map<T,Y>::operator[] (int i) {
    return array[i];
}

template <class T, class Y>
void Map<T,Y>::print() {
    for (int i = 0; i < index; i++) {
        array[i].print();
        cout << endl;
    }
}

template <class T, class Y>
Y& Map<T,Y>::operator[] (T& item) {
    for (int i = 0; i < index; i++) {
        if (item == *(array[i].key))
            return *(array[i].value);
    }
    insert(item);
    return *(array[index - 1].value);
}

template <class T, class Y>
void Map<T,Y>::sort(int (*compar)(T &p1, T &p2)) {
    psort<Tuple <T, Y> >(array, index, compar);
}
