#include <iostream>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;

#include "Sort.hpp"

class Num {
    public:
        Num() { }
        Num(int n): num(n) { }
        Num(const Num &other) {
            num = other.num;
        }
        int num;
        void print() {
            cout << num << " ";
        }
        Num & operator=(const Num &other) {
            if (this == &other) return *this;
            num = other.num;
            return *this;
        }
};

int compare (Num *&p1, Num *&p2) {
    return p1->num - p2->num;
}
int bla (const void*p1, const void *p2) {
    return (*((Num **) p1))->num - (*((Num **) p2))->num;
}

int cmp (Num &p1, Num &p2) {
    return p1.num - p2.num;
}

int main() {
    int inSize;
    cin >> inSize;

    Num nums[inSize];
    Num *array[inSize];

    for (int i = 0; i < inSize; i++) {
        cin >> nums[i].num;
        array[i] = &nums[i];
    }
    psort(array, 0, inSize - 1, compare);
    psort(nums, 0, inSize - 1, cmp);
    // qsort(array, inSize, sizeof(Num*), bla);
    /*
    Num tmp;
    SWAP(0,1,tmp);
    SWAP(0,1,tmp);
    */
    for (int i = 0; i < inSize; i++) {
        cout << array[i]->num << endl;
    }
}

