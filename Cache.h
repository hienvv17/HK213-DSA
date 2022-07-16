#ifndef CACHE_H
#define CACHE_H

#include "main.h"

class Cache
{
    Elem **arr;
    int current_size;
    bool full;
    int head;

    // current size of the cache, base on params
    // head current head of array //

public:
    Cache(int s)
    {
        arr = new Elem *[s];
        current_size = 0;
        head = 0;
        full = false;
        // first of all head =0 and size=0;
    }
    ~Cache()
    {
        delete[] arr;
    }
    int indexOf(int addr);
    void check_full();
    Data *read(int addr);
    Elem *put(int addr, Data *cont);
    Elem *write(int addr, Data *cont);

    void print();
    void preOrder();
    void inOrder();
};
#endif