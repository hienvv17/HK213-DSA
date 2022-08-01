#ifndef CACHE_H
#define CACHE_H
#include "main.h"
class Node {
public:
  Elem *node_data;
  int index;
  Node *left;
  Node *right;
  Node(Elem *elem, int index) {
    node_data = elem;
    left = right = NULL;
    this->index = index;
  }
};

class BST {
  Node *root;
  Node *removeRec(Node *&, int);
  Node *insertRec(Node *&, Elem *, int);
  void inorderRec(Node *);
  void preorderRec(Node *);
  Node *searchRec(Node *, int);
  Node *findMaxRight(Node *);
  Node *findMinLeft(Node *);

public:
  BST() { this->root = NULL; }
  void insert(Elem *, int);
  void remove(int);
  void preorder();
  void inorder();
  Node *search(int a);
};

class Cache {
  Elem **arr;
  int current_size;
  bool full;
  int head, tail;
  BST tree;

  // current size of the cache, base on params
  // head current head of array //

public:
  Cache(int s) {
    arr = new Elem *[s];
    current_size = 0;
    head = 0;
    tail = MAXSIZE - 1;
    full = false;
    // first of all head =0 and size=0;
    // head and tail save the index in linklist
  }
  ~Cache() { delete[] arr; }
  void setTail();
  void setHead();
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