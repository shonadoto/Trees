#ifndef AVL_H
#define AVL_H
#include <iostream>

namespace Avl {

  struct Avl {
    Avl* left, * right;
    int data, height;
  };

  int height(Avl* T);

  void fix_height(Avl* T);

  void left_turn(Avl*& T);

  void right_turn(Avl*& T);

  void balance(Avl*& T);

  void insert(Avl*& T, int x);

  void inorder_out(Avl* T);

  void right_swap_delete(Avl*& T, Avl*& S);

  void left_swap_delete(Avl*& T, Avl*& S);

  void delete_elem(Avl*& T, int x);

  void inorder_heights_check(Avl* T);
}


#endif // AVL_H
