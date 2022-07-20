#ifndef SPLAY_H
#define SPLAY_H

#include <iostream>
#include <iostream>
#include <algorithm>

namespace Splay {
  struct SplayTree {
    int data;
    SplayTree* left, * right, * parent;
  };

  int height(SplayTree* Tree);

  void Splay(SplayTree* Tree);

  void insert(SplayTree*& Tree, int data, SplayTree* parent);

  void insert(SplayTree*& Tree, int data);

  SplayTree* Merge(SplayTree* L, SplayTree* R);

    void del(SplayTree*& Tree, int data);
}

#endif // SPLAY_H
