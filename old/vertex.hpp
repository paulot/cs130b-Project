
#ifndef VERTEX
#define VERTEX

struct AdjVertex {
    inline AdjVertex(int l, int d, int X, int Y) { 
        label = l; 
        dist = d;
        x = X;
        y = Y;
    }
    int label;
    int dist;
    int x;
    int y;
    AdjVertex *next;
    inline void print() {
        cout << label << " " << dist << " ";
    }
    inline void fudgePrint() {
        cout << label << " ";
    }
};

struct Vertex {
    int x;
    int y;
    char pos;
    int label;
    AdjVertex    *next;
    union {
        Rectangle *parent;
        int rlabel;
    };
    inline void print() { 
       cout << label << " " << x << " " << y << " " << rlabel << " ";
    }
    inline bool operator!=(Vertex &rhs) {
        return rhs.label != label;
    }
};

struct SVertex {
    SVertex() { }
    SVertex(int l) { label = l; }
    int label;
    inline bool operator== (SVertex &rhs) {
        return label == rhs.label;
    }
    inline void print() {
        cout << label << " ";
    }
    SVertex *next;
};
#endif
