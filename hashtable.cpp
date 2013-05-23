#include <string.h>

// Half assed hash table
class fudgeTable {
    public:
        fudgeTable      (int s);
        ~fudgeTable     ();
        bool isPresent  (int value);
        void insert     (int value);
        void clear      ();
        void grow       ();
    private:
        int hash        (int value);
        int *table;
        int size;
};

fudgeTable::fudgeTable(int s) {
    size = s;
    table = new int[size];
    memset(table, 0, sizeof(int)*size);
}

fudgeTable::~fudgeTable() {
    delete [] table;
}

int fudgeTable::hash(int value) {
    return value % size;
}

bool fudgeTable::isPresent(int value) {
    int pos = hash(value);
    for (int i = 0; i < size; i++) { 
        if (table[(pos + i) % size] == value)
            return true;
        else if (table[(pos + i) % size] == 0)
            return false;
    }
    return false;
}

void fudgeTable::insert (int value) {
    int pos = hash(value);
    if (table[pos] == 0) {
        table[pos] = value;
        return;
    }
    for (int i = 1; i < size; i++) { 
        if (table[(pos + i) % size] == 0) {
            table[pos] = value;
            return;
        }
    }
    grow();
    insert(value);
}

void fudgeTable::grow() {
    size *= 2;
    int newtable[size];
    memset(newtable, 0, sizeof(int)*size);
    int *oldtable = table;
    table = newtable;
    for (int i = 0; i < size/2; i++)
        insert(oldtable[i]);
}
