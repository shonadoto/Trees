#include "avl.h"
#include <iostream>


namespace Avl {

  int height(Avl* T) {
    return T ? T->height : 0;
  }

  void fix_height(Avl* T) {
    if (!T)
      return;
    T->height = std::max(height(T->left), height(T->right)) + 1;
    return;
  }

  void left_turn(Avl*& T) {
    if (height(T->right->left) <= height(T->right->right)) { // small turn
      Avl* q = T->right;
      T->right = q->left;
      q->left = T;
      fix_height(T);
      fix_height(q);
      T = q;
      return;
    }
    // big turn
    Avl* q = T->right;
    Avl* z = q->left;
    T->right = z->left;
    q->left = z->right;
    z->left = T;
    z->right = q;
    fix_height(T);
    fix_height(z);
    fix_height(q);
    T = z;
    return;
  }

  void right_turn(Avl*& T) {
    if (height(T->left->right) <=  height(T->left->left)) { // small turn
      Avl* q = T->left;
      T->left = q->right;
      q->right = T;
      fix_height(T);
      fix_height(q);
      T = q;
      return;
    }
    // big turn
    Avl* q = T->left;
    Avl* z = q->right;
    T->left = z->right;
    q->right = z->left;
    z->right = T;
    z->left = q;
    fix_height(T);
    fix_height(z);
    fix_height(q);
    T = z;
    return;
  }

  void balance(Avl*& T) {
    int dif = height(T->left) - height(T->right);
    if (std::abs(dif) <= 1) {
      fix_height(T);
      return;
    }
    if (dif > 0) {
      right_turn(T);
      return;
    }
    left_turn(T);
    return;
  }

  void insert(Avl*& T, int x) {
    if (!T) {
      Avl* q = new Avl;
      q->data = x;
      q->left = NULL;
      q->right = NULL;
      q->height = 1;
      T = q;
      return;
    }
    if (x == T->data)
      return;
    if (x > T->data)
      insert(T->right, x);
    else if (x < T->data)
      insert(T->left, x);
    balance(T);
    fix_height(T);
    return;
  }

  void inorder_out(Avl* T) {
    if (!T)
      return;
    inorder_out(T->left);
    std::cout << T->data << ' ';
    inorder_out(T->right);
    return;
  }

  void right_swap_delete(Avl*& T, Avl*& S) {
    if (!T->right) {
      std::swap(T->data, S->data);
      Avl* q = T;
      T = T->left;
      delete(q);
      return;
    }
    right_swap_delete(T->right, S);
    balance(T);
    return;
  }

  void left_swap_delete(Avl*& T, Avl*& S) {
    if (!T->left) {
      std::swap(T->data, S->data);
      Avl* q = T;
      T = T->right;
      delete(q);
      return;
    }
    left_swap_delete(T->left, S);
    balance(T);
    return;
  }

  void delete_elem(Avl*& T, int x) {
    if (!T)
      return;

    if (x > T->data) {
      delete_elem(T->right, x);
      balance(T);
      return;
    }

    if (x < T->data) {
      delete_elem(T->left, x);
      balance(T);
      return;
    }

    if (height(T->left) > height(T->right)) {
      if (!T->left) {
        delete(T);
        T = NULL;
        return;
      }
      right_swap_delete(T->left, T);
      balance(T);
      return;
    }
    if (!T->right) {
      delete(T);
      T = NULL;
      return;
    }
    left_swap_delete(T->right, T);
    balance(T);
    return;
  }

  void inorder_heights_check(Avl* T) {
    if (!T)
      return;
    inorder_heights_check(T->left);
    // std::cout << '(' << height(T->left) << ", " << height(T->right) << ") ";
    std::cout << height(T->left) - height(T->right) << ' ';
    inorder_heights_check(T->right);
    return;
  }
}

