#include <cstdlib>

template <class T>
void psort(T *array, int numElements, int (*compar)(T &p1, T &p2)) {
    qsort((void *) array, numElements, sizeof(T), compar);
}
