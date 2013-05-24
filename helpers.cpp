#ifndef HELP
#define HELP

template <class T>
void printlist(T *list) {
    for (T *i = list; i != NULL; i++)
        i->print();
}

template <class T>
int compare(const void *p1, const void *p2) {
    return not ((((T*) p1)->y == ((T*) p2)->y and 
                        ((T*) p1)->x < ((T*) p2)->x) 
            or ((T*) p1)->y > ((T*) p2)->y);
}

template <class T>
int compareY(const void *p1, const void *p2) {
    return not ((((T*) p1)->x == ((T*) p2)->x and 
                        ((T*) p1)->y < ((T*) p2)->y) 
            or ((T*) p1)->x > ((T*) p2)->x);
}

void addList(AdjVertex *&v, int l, int d, int x, int y) {
    if (d == 0)
        return;
    if (v == NULL) {
        v = new AdjVertex(l, d, x, y);
        v->next = NULL;
    } else {
        AdjVertex *j = v;
        AdjVertex *i = v->next;
        if (i == NULL) {
            if (j->label > l) {
                v = new AdjVertex(l, d, x, y);
                v->next = j;
            } else {
                j->next = new AdjVertex(l, d, x, y);
                j->next->next = i;
            }
        } else {
            if (j->label > l) {
                v = new AdjVertex(l, d, x, y);
                v->next = j;
                return;
            }
            for (i, j;
                 i->next != NULL and i->label < l;
                 i = i->next, j = j->next);

            if (i->label > l and j->label < l) {
                j->next = new AdjVertex(l, d, x, y);
                j->next->next = i;
            } else {
                i->next = new AdjVertex(l, d, x, y);
                i->next->next = NULL;
            }
        }
    }
}

void addSSList(SVertex *&v, SVertex *&e, int l) {
    if (v == NULL) {
        v = new SVertex(l);
        v->next = NULL;
        e = v;
        e->next = NULL;
    } else if (e != NULL) {
        e->next = new SVertex(l);
        e = e->next;
        e->next = NULL;
    }
}

void addSList(SVertex *&v, int l) {
    if (v == NULL) {
        v = new SVertex(l);
        v->next = NULL;
    } else {
        SVertex *j = v;
        SVertex *i = v->next;
        if (i == NULL) {
            if (j->label > l) {
                v = new SVertex(l);
                v->next = j;
            } else {
                j->next = new SVertex(l);
                j->next->next = i;
            }
        } else {
            if (j->label > l) {
                v = new SVertex(l);
                v->next = j;
                return;
            }
            for (i, j;
                 i->next != NULL and i->label < l;
                 i = i->next, j = j->next);

            if (i->label > l and j->label < l) {
                j->next = new SVertex(l);
                j->next->next = i;
            } else {
                i->next = new SVertex(l);
                i->next->next = NULL;
            }
        }
    }
}

void printList(AdjVertex *v) {
    if (v == NULL) { cout << "NULL"; return; }
    AdjVertex *i = v;
    for (i; i != NULL; i = i->next)
        i->print();
}

void printSList(SVertex *v) {
    if (v == NULL) { cout << "NULL"; return; }
    SVertex *i = v;
    for (i; i != NULL; i = i->next)
        cout << i->label << " ";
}

template <class T>
int rcomp(const void *p1, const void *p2) {
    return ((T*)p1)->a->label > ((T*)p2)->a->label;
}



/*
typedef enum {
                ERROR = 0,
                ADD   = 1
} RVal;
    
int search(AdjVertex *list, int lbl, int d) {
    if (list == NULL) { return ERROR; }
    AdjVertex *i = list;
    for (i; i != NULL; i = i->next)
       if (i->label == lbl)
           return ADD;
        else
}
*/
#endif
