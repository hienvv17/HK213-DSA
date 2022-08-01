#include "Cache.h"
// to find index in the linklist ( array list)

Node* BST::insertRec(Node*& node, Elem* elem, int addr)
{
    if (node == NULL) {
        // cout << "nothing \t";
        node = new Node(elem, addr);
        return node;
    }
    if (node->node_data->addr > elem->addr) {
        node->left = insertRec(node->left, elem, addr);
    } else if (node->node_data->addr < elem->addr) {
        node->right = insertRec(node->right, elem, addr);
    }
    return node;
}

Node* BST::findMaxRight(Node* node)
{
    if (node->right == NULL) {
        return node;
    }

    return findMaxRight(node->right);
}

Node* BST::removeRec(Node*& node, int addr)
{
    // need check indexx in fixx with array.
    if (node == NULL) {
        return NULL;
    }
    if (node->node_data->addr > addr) {
        node->left = removeRec(node->left, addr);
    } else if (node->node_data->addr < addr) {
        node->right = removeRec(node->right, addr);
    } else {
        // only right sub tree
        if (node->left == NULL) {
            Node* temp = node;
            node = node->right;
            temp->right = NULL;
            delete temp;
            return node;
        }
        // only left sub tree
        else if (node->right == NULL) {
            Node* temp = node;
            node = node->left;
            temp->left = NULL;
            delete temp;
            return node;
        }
        // 2 sub tree
        else {
            Node* replace = node->right;
            while (replace->left != NULL) {
                replace = replace->left;
            }
            node->index = replace->index;
            node->node_data = replace->node_data;
            int newaddr = replace->node_data->addr; // new node need to delete
            replace = NULL;
            delete replace;
            node->right = removeRec(node->right, newaddr);
        }
    }
    return node;
}

Node* BST::searchRec(Node* node, int addr)
{
    if (node == NULL) {
        return NULL;
    } else if (node->node_data->addr == addr) {
        return node;
    } else if (node->node_data->addr > addr) {
        return searchRec(node->left, addr);
    } else {
        return searchRec(node->right, addr);
    }
}

void BST::inorderRec(Node* node)
{
    if (node == NULL) {
        return;
    }
    inorderRec(node->left);
    node->node_data->print();
    inorderRec(node->right);
}

void BST::preorderRec(Node* node)
{
    if (node == NULL)
        return;
    node->node_data->print();
    preorderRec(node->left);
    preorderRec(node->right);
}

// insert in BST will call recursive method in BST
void BST::insert(Elem* elem, int addr) { insertRec(root, elem, addr); }

void BST::remove(int addr) { removeRec(root, addr); }

void BST::preorder() { preorderRec(root); }

void BST::inorder() { inorderRec(root); }

Node* BST::search(int addr) { return searchRec(root, addr); }

void Cache::print()
{
    if (head == 0) // case 1 head at index 0 full or not full cache i same
    {
        for (int i = current_size - 1; i >= 0; i--) {
            arr[i]->print();
        }
    } else // case 2 is full cache
    {
        for (int j = head - 1; j >= 0; j--) {
            arr[j]->print();
        }
        for (int i = MAXSIZE - 1; i >= head; i--) {
            arr[i]->print();
        }
    }
}

void Cache::preOrder() { tree.preorder(); }

void Cache::inOrder() { tree.inorder(); }

// check if list is full or not
void Cache::check_full() { full = (current_size == MAXSIZE) ? true : false; }

// set head to handle life time
void Cache::setHead() { head = (head + 1 > MAXSIZE - 1) ? 0 : (head + 1); }

// set tail to handle life time
void Cache::setTail() { tail = (head - 1 >= 0) ? (head - 1) : (MAXSIZE - 1); }

Data* Cache::read(int addr)
{
    // search in BST
    int idx = (tree.search(addr) == NULL) ? -1 : tree.search(addr)->index;
    if (idx == -1) {
        return NULL;
    } else {
        return arr[idx]->data;
    }
}

Elem* Cache::put(int addr, Data* cont)
{
    /* PUT TO NOT FULL CACHE // CALL AFTER READ RETURN NULL
    Put to arr -> insert to tree -> update size, full
    */

    if (!full) {
        arr[current_size] = new Elem(addr, cont, true);
        tree.insert(new Elem(addr, cont, true), current_size);
        current_size += 1;
        check_full();
        return NULL;
    }
    /*PUT TO FULL CACHE

    */
    else {
        /* FIFO for even addr and LIFO for odd addr
        FIFO : put to arr -> remove addr in tree -> add new node to tree-> update
        head, tail;
         */
        Elem* replace = NULL;
        if (addr % 2 == 0) {
            replace = arr[head];
            arr[head] = new Elem(addr, cont, true);
            // remove node addr in tree with addr, and insert newnode with this
            tree.remove(replace->addr);
            tree.insert((new Elem(addr, cont, true)), head);
            // update tail and head of arr to fix queue
            setHead();
            setTail();
            return replace;
        } else {
            replace = arr[tail];
            arr[tail] = new Elem(addr, cont, true);
            // remove at tail so do not change
            tree.remove(replace->addr);
            tree.insert(new Elem(addr, cont, true), tail);
            return replace;
        }
    }
}

Elem* Cache::write(int addr, Data* cont)
{
    int idx = (tree.search(addr) == NULL) ? -1 : tree.search(addr)->index;
    // do not contain in the Cache
    if (idx == -1) {
        if (!full) {
            // add to arr-> insert tree witd index -> update size
            arr[current_size] = new Elem(addr, cont, false);
            tree.insert(new Elem(addr, cont, false), current_size);
            current_size += 1;
            check_full();
            return NULL;
        }
        /*WRITE TO FULL CACHE*/
        else {
            // FIFO for even addr and LIFO for odd addr
            // same logic with put but syn false
            Elem* replace = NULL;
            if (addr % 2 == 0) {
                replace = arr[head];
                arr[head] = new Elem(addr, cont, false);
                tree.remove(replace->addr);
                tree.insert((new Elem(addr, cont, false)), head);
                setHead();
                setTail();
                return replace;
            } else {
                replace = arr[tail];
                arr[tail] = new Elem(addr, cont, false);
                tree.remove(replace->addr);
                tree.insert((new Elem(addr, cont, false)), tail);
                return replace;
            }
        }
    }

    // contain in Cache
    else {
        arr[idx]->data = cont;
        arr[idx]->sync = false;
        tree.search(addr)->node_data->data = cont;
        tree.search(addr)->node_data->sync = false;
        return NULL;
    }
}