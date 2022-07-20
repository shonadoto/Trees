#include "kurevo.h"
#include "iostream"
#include "QRandomGenerator"
#include "Windows.h"
#include "algorithm"
#include "vector"
#include "time.h"

std::random_device rd;
std::mt19937 mersenne(rd());


int my_max(int a, int b) {
  if (a < b)
    return b;
  return a;
}

namespace Kurevo {


  int height(kurevo* Tree) {
    if (!Tree)
      return 0;
    return Tree->height;
  }

  void Recalc(kurevo* Tree) {
    if (!Tree)
      return;
    Tree->height = my_max(height(Tree->left), height(Tree->right)) + 1;
    return;
  }

  kurevo* Merge(kurevo* TF, kurevo* TS) {
    if (!TF)
      return TS;
    if (!TS)
      return TF;
    if (TF->prior > TS->prior) {
      TF->right = Merge(TF->right, TS);
      Recalc(TF);
      return TF;
    }
    TS->left = Merge(TF, TS->left);
    Recalc(TS);
    return TS;
  }

  std::vector<kurevo*> Split(kurevo* Tree, int key) {
    if (!Tree)
      return { NULL, NULL, NULL };
    if (Tree->key < key) {
      std::vector<kurevo*> ss = Split(Tree->right, key);
      Tree->right = ss[0];
      Recalc(Tree);
      return { Tree, ss[1], ss[2] };
    }
    else if (Tree->key > key) {
      std::vector<kurevo*> ss = Split(Tree->left, key);
      Tree->left = ss[2];
      Recalc(Tree);
      return { ss[0], ss[1], Tree };
    }
    kurevo* left = Tree->left, * right = Tree->right;
    Tree->left = NULL;
    Tree->right = NULL;
    Recalc(Tree);
    return { left, Tree, right };
  }

  void Insert(kurevo*& Tree, int data) {
    std::vector<kurevo*> ss = Split(Tree, data);
    if (ss[1]) {
      Tree = Merge(Merge(ss[0], ss[1]), ss[2]);
      return;
    }
    kurevo* nw = new kurevo;
    nw->key = data;
    nw->prior = mersenne();
    nw->left = NULL;
    nw->right = NULL;
    Tree = Merge(Merge(ss[0], nw), ss[2]);
    return;
  }

  void Delete(kurevo*& Tree, int data) {
    std::vector<kurevo*> ss = Split(Tree, data);
    Tree = Merge(ss[0], ss[2]);
    return;
  }

  void Out(kurevo*& Tree) {
    if (!Tree)
      return;
    Out(Tree->left);
    std::cout << Tree->key << ' ';
    Out(Tree->right);
    return;
  }
}

