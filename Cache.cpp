#include "Cache.h"

int Cache::indexOf(int addr)
{
    int size = current_size;
    if (size == 0)
    {
        return -1;
    }
    for (int i = 0; i < size; i++)
    {
        if (addr == arr[i]->addr)
        {
            return i;
        }
    }
    return -1;
}
void Cache::check_full()
{
    full = (current_size == MAXSIZE) ? true : false;
}

Data *Cache::read(int addr)
{
    int idx = indexOf(addr);
    if (idx == -1)
    {
        return NULL;
    }
    else
    {
        return arr[idx]->data;
    }
}
Elem *Cache::put(int addr, Data *cont)
{
    /* PUT TO NO FULL CACHE*/

    if (!full)
    {
        arr[current_size] = new Elem(addr, cont, true);
        current_size += 1;
        check_full();
        return NULL;
    }
    else
    {
    }

    /* PUT TO FULL LIST*/
    // return out_Elem;
}
Elem *Cache::write(int addr, Data *cont)
{
    int idx = indexOf(addr);
    // do not contain in the Cache
    if (idx == -1)
    {
        // add new but not full Cache full == false

        return NULL;

        // add to full Cache and need replace
        // return out_Elem;
    }

    // contain in Cache
    else
    {
        arr[idx]->data = cont;
        arr[idx]->sync = false;
        return NULL;
    }
}
void Cache::print()
{
    return;
}
void Cache::preOrder()
{
    return;
}
void Cache::inOrder()
{
    return;
}
