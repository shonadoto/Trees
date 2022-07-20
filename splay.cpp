#include "splay.h"

namespace Splay {

  int height(SplayTree* Tree) {
    return Tree ? std::max(height(Tree->left), height(Tree->right)) + 1 : 0;
  }

  void Splay(SplayTree* Tree) {
    SplayTree* x = Tree;
    if (!x->parent)
      return;
    SplayTree* p = x->parent;
    if (!p->parent) {
      if (p->left == x) {
        p->left = x->right;
        if (p->left)
          p->left->parent = p;
        x->right = p;
        x->parent = p->parent;
        p->parent = x;
        return;
      }
      p->right = x->left;
      if (p->right)
        p->right->parent = p;
      x->left = p;
      x->parent = p->parent;
      p->parent = x;
      return;
    }

    SplayTree* g = p->parent;
    SplayTree* a, * b, * c, * d;
    if (p->left == x && g->left == p) {
      a = x->left;
      b = x->right;
      c = p->right;
      d = g->right;
      x->parent = g->parent;
      if (g->parent) {
        if (g == g->parent->left)
          g->parent->left = x;
        else
          g->parent->right = x;
      }
      p->parent = x;
      g->parent = p;

      x->left = a;
      if (a)
        a->parent = x;
      x->right = p;

      p->left = b;
      if (b)
        b->parent = p;
      p->right = g;

      g->left = c;
      if (c)
        c->parent = g;
      g->right = d;
      if (d)
        d->parent = g;
      Splay(x);
      return;
    }
    if (p->right == x && g->right == p) {
      a = g->left, b = p->left, c = x->left, d = x->right;
      x->parent = g->parent;
      if (g->parent) {
        if (g == g->parent->left)
          g->parent->left = x;
        else
          g->parent->right = x;
      }
      p->parent = x;
      g->parent = p;

      g->left = a;
      if (a)
        a->parent = g;
      g->right = b;
      if (b)
        b->parent = g;

      p->left = g;
      p->right = c;
      if (c)
        c->parent = p;

      x->left = p;
      x->right = d;
      if (d)
        d->parent = x;
      Splay(x);
      return;
    }
    if (p->right == x && g->left == p) {
      a = p->left, b = x->left, c = x->right, d = g->right;
      x->parent = g->parent;
      if (g->parent) {
        if (g == g->parent->left)
          g->parent->left = x;
        else
          g->parent->right = x;
      }
      p->parent = g->parent = x;

      p->left = a;
      if (a)
        a->parent = p;
      p->right = b;
      if (b)
        b->parent = p;

      g->left = c;
      if (c)
        c->parent = g;
      g->right = d;
      if (d)
        d->parent = g;

      x->left = p;
      x->right = g;
      Splay(x);
      return;
    }
    if (p->left == x && g->right == p) {
      a = g->left, b = x->left, c = x->right, d = p->right;
      x->parent = g->parent;
      if (g->parent) {
        if (g == g->parent->left)
          g->parent->left = x;
        else
          g->parent->right = x;
      }
      g->parent = p->parent = x;

      g->left = a;
      if (a)
        a->parent = g;
      g->right = b;
      if (b)
        b->parent = g;

      p->left = c;
      if (c)
        c->parent = p;
      p->right = d;
      if (d)
        d->parent = p;

      x->left = g;
      x->right = p;
      Splay(x);
      return;
    }
  }

  void insert(SplayTree*& Tree, int data, SplayTree* parent) {
    if (!Tree) {
      Tree = new SplayTree;
      Tree->data = data;
      Tree->left = Tree->right = NULL;
      Tree->parent = parent;
      Splay(Tree);
      return;
    }
    if (Tree->data == data)
      return;
    if (data < Tree->data)
      insert(Tree->left, data, Tree);
    else
      insert(Tree->right, data, Tree);
    return;
  }

  void insert(SplayTree*& Tree, int data) {
    insert(Tree, data, NULL);
    while (Tree->parent)
      Tree = Tree->parent;
    return;
  }

  SplayTree* Merge(SplayTree* L, SplayTree* R) {
      if (!L)
        return R;
      if (!R)
        return L;
      SplayTree* Lm = L->right;
      while (Lm && Lm->right)
        Lm = Lm->right;
      if (!Lm) {
        L->right = R;
        if (R)
          R->parent = L;
        return L;
      }
      Splay(Lm);
      while (Lm->parent)
        Lm = Lm->parent;
      Lm->right = R;
      if (R)
        R->parent = Lm;
      return Lm;
    }

    void del(SplayTree*& Tree, int data) {
      SplayTree* F = Tree;
      while (F && F->data != data) {
        if (data < F->data) {
          F = F->left;
        }
        else {
          F = F->right;
        }
      }
      if (!F)
        return;
      Splay(F);
      if (F->left)
        F->left->parent = NULL;
      if (F->right)
        F->right->parent = NULL;
      Tree = Merge(F->left, F->right);
      delete(F);
      return;
    }
}
