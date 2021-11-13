#ifndef SimpleMap_h
#define SimpleMap_h

/*
SimpleMap by:
https://github.com/spacehuhn/SimpleMap

MIT License

Copyright (c) 2018 Stefan Kremser

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include <stddef.h>
#include <functional>

template<class T, class U>
struct SimpleMapNode {
    T                    key;
    U                    data;
    SimpleMapNode<T, U>* next;
};

template<typename T, typename U>
class SimpleMap {
    public:
        int (*compare)(T & a, T & b);

        SimpleMap(int (*compare)(T & a, T & b));
        virtual ~SimpleMap();

        virtual int size();
        virtual void clear();
        virtual void remove(T key);
        virtual void remove(int i);
        virtual void put(T key, U obj);
        virtual U get(T key);
        virtual T getKey(int i);
        virtual U getData(int i);
        virtual int getIndex(T key);
        virtual bool has(T key);

        virtual void lock();
        virtual void unlock();
        virtual bool isLocked();

    protected:
        int listSize;
        SimpleMapNode<T, U>* listBegin;
        SimpleMapNode<T, U>* listEnd;

        bool locked = false;

        // Helps get() method by saving last position
        SimpleMapNode<T, U>* lastNodeGot = NULL;
        int lastIndexGot                 = -1;
        bool isCached                    = false;

        virtual SimpleMapNode<T, U>* getNode(T key);
        virtual SimpleMapNode<T, U>* getNodeIndex(int index);
};

template<typename T, typename U>
SimpleMap<T, U>::SimpleMap(int (*compare)(T & a, T & b)) {
    SimpleMap<T, U>::compare = compare;
    listBegin                = NULL;
    listEnd                  = NULL;
    listSize                 = 0;
    isCached                 = false;
    lastIndexGot             = -1;
    lastNodeGot              = NULL;
}

// Clear Nodes and free Memory
template<typename T, typename U>
SimpleMap<T, U>::~SimpleMap() {
    clear();
}

template<typename T, typename U>
U SimpleMap<T, U>::get(T key) {
    SimpleMapNode<T, U>* h = getNode(key);
    return h ? h->data : U();
}

template<typename T, typename U>
SimpleMapNode<T, U>* SimpleMap<T, U>::getNode(T key) {
    if (listSize > 0) {
        if ((compare(key, listBegin->key) < 0) || (compare(key, listEnd->key) > 0)) return NULL;

        if (isCached) {
            if (compare(key, lastNodeGot->key) == 0) return lastNodeGot;
        }

        SimpleMapNode<T, U>* h = listBegin;

        int lowerEnd = 0;
        int upperEnd = listSize - 1;
        int res;
        int mid = (lowerEnd + upperEnd) / 2;

        int hIndex = 0;

        while (lowerEnd <= upperEnd) {
            h      = lastNodeGot;
            hIndex = lastIndexGot;

            res = compare(key, getNodeIndex(mid)->key);

            if (res == 0) {
                return lastNodeGot;
            } else if (res < 0) {
                // when going left, set cached node back to previous cached node
                lastNodeGot  = h;
                lastIndexGot = hIndex;
                isCached     = true;

                upperEnd = mid - 1;
                mid      = (lowerEnd + upperEnd) / 2;
            } else if (res > 0) {
                lowerEnd = mid + 1;
                mid      = (lowerEnd + upperEnd) / 2;
            }
        }
    }
    return NULL;
}

template<typename T, typename U>
SimpleMapNode<T, U>* SimpleMap<T, U>::getNodeIndex(int index) {
    if ((index < 0) || (index >= listSize)) {
        return NULL;
    }

    SimpleMapNode<T, U>* hNode = listBegin;
    int c                      = 0;

    if (isCached && (index >= lastIndexGot)) {
        c     = lastIndexGot;
        hNode = lastNodeGot;
    }

    while (hNode != NULL && c < index) {
        hNode = hNode->next;
        c++;
    }

    if (hNode) {
        isCached     = true;
        lastIndexGot = c;
        lastNodeGot  = hNode;
    }

    return hNode;
}

template<typename T, typename U>
void SimpleMap<T, U>::clear() {
    unlock();

    SimpleMapNode<T, U>* h = listBegin;
    SimpleMapNode<T, U>* toDelete;

    while (h != NULL) {
        toDelete = h;
        h        = h->next;
        delete toDelete;
    }

    listBegin = NULL;
    listEnd   = NULL;
    listSize  = 0;

    isCached     = false;
    lastIndexGot = -1;
    lastNodeGot  = NULL;
}

template<typename T, typename U>
int SimpleMap<T, U>::size() {
    return listSize;
}

template<typename T, typename U>
void SimpleMap<T, U>::put(T key, U obj) {
    // create new node
    SimpleMapNode<T, U>* newNode = new SimpleMapNode<T, U>();
    newNode->next = NULL;
    newNode->data = obj;
    newNode->key  = key;

    // look if already in list
    SimpleMapNode<T, U>* h = listBegin;
    SimpleMapNode<T, U>* p = NULL;
    bool found             = false;
    int  c                 = 0;

    if (listSize > 0) {
        while (h != NULL && !found) {
            if (compare(h->key, key) == 0) {
                found = true;
            } else {
                p = h;
                h = h->next;
                c++;
            }
        }
    }

    // replace old node with new one
    if (found) {
        if (h == listBegin) listBegin = newNode;

        if (h == listEnd) listEnd = newNode;

        if (p) p->next = newNode;
        newNode->next = h->next;
        delete h;

        lastIndexGot = c;
        lastNodeGot  = newNode;
        isCached     = true;
    }

    // create new node
    else if (!locked) {
        if (listSize == 0) {
            // add at start (first node)
            listBegin = newNode;
            listEnd   = newNode;

            lastIndexGot = 0;
        } else {
            if (compare(key, listEnd->key) >= 0) {
                // add at end
                listEnd->next = newNode;
                listEnd       = newNode;

                lastIndexGot = listSize;
            } else if (compare(key, listBegin->key) <= 0) {
                // add at start
                newNode->next = listBegin;
                listBegin     = newNode;

                lastIndexGot = 0;
            } else {
                // insertion sort
                h     = listBegin;
                p     = NULL;
                found = false;
                c     = 0;

                while (h != NULL && !found) {
                    if (compare(h->key, key) > 0) {
                        found = true;
                    } else {
                        p = h;
                        h = h->next;
                        c++;
                    }
                }
                newNode->next = h;

                if (p) p->next = newNode;

                lastIndexGot = c;
            }
        }

        listSize++;

        isCached    = true;
        lastNodeGot = newNode;
    }
}

template<typename T, typename U>
void SimpleMap<T, U>::remove(T key) {
    if ((listSize > 0) && !locked) {
        if ((compare(key, listBegin->key) < 0) || (compare(key, listEnd->key) > 0)) return;

        SimpleMapNode<T, U>* h = listBegin;
        SimpleMapNode<T, U>* p = NULL;
        bool found             = false;

        while (h != NULL && !found) {
            if (h->key == key) {
                found = true;
            } else {
                p = h;
                h = h->next;
            }
        }

        if (found) {
            if (p) p->next = h->next;
            else listBegin = h->next;

            if (listEnd == h) listEnd = p;
            listSize--;
            delete h;
        }
    }
}

template<typename T, typename U>
void SimpleMap<T, U>::remove(int i) {
    if (listSize > 0) {
        SimpleMapNode<T, U>* h = getNodeIndex(i);

        if (h != NULL) {
            SimpleMapNode<T, U>* p = getNodeIndex(i - 1);

            if (p != NULL) p->next = h->next;

            if (h == listBegin) listBegin = h->next;

            if (h == listEnd) listEnd = p;

            listSize--;
            delete h;
        }
    }
}

template<typename T, typename U>
bool SimpleMap<T, U>::has(T key) {
    return getNode(key) != NULL;
}

template<typename T, typename U>
T SimpleMap<T, U>::getKey(int i) {
    SimpleMapNode<T, U>* h = getNodeIndex(i);
    return h ? h->key : T();
}

template<typename T, typename U>
U SimpleMap<T, U>::getData(int i) {
    SimpleMapNode<T, U>* h = getNodeIndex(i);
    return h ? h->data : U();
}

template<typename T, typename U>
int SimpleMap<T, U>::getIndex(T key) {
    return getNode(key) ? lastIndexGot : -1;
}

template<typename T, typename U>
void SimpleMap<T, U>::lock() {
    locked = true;
}

template<typename T, typename U>
void SimpleMap<T, U>::unlock() {
    locked = false;
}

template<typename T, typename U>
bool SimpleMap<T, U>::isLocked() {
    return locked;
}

#endif // ifndef SimpleMap_h