
template <class T>
class Vector {
    public:
        Vector(int maxSize): size(maxSize) {
            index = 0;
            array = new T[size];
        }
        T *array;
        int size;
        int index;
};
