#ifndef RBTREE_H
#define RBTREE_H


#include <iostream>
#include <iostream>
#include <algorithm>

#define BLACK 0
#undef max
#define RED 1

namespace Rb {
  struct RBTree {
    int color;
    int data;
    RBTree* left, * right, * parent;
  };

  int color(RBTree* Tree);

  int height(RBTree* Tree);

  int full_height(RBTree* Tree);

  void ins_turning(RBTree*& N, RBTree*& P, RBTree*& G, RBTree*& U);

  void insert(RBTree*& Tree, int x, RBTree* P);

  void insert(RBTree*& Tree, int x);

  RBTree* find_del_tree(RBTree* Tree, int data);

  RBTree* find_change_tree(RBTree* Tree);

  void del_modification(RBTree* N);

  void del(RBTree*& Tree, int data);

  void out(RBTree* Tree);

  bool check(RBTree* Tree);

}


#endif // RBTREE_H
