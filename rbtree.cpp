#include "rbtree.h"
#include <iostream>
#include <algorithm>

#define BLACK 0
#undef max
#define RED 1


namespace Rb {



  int color(RBTree* Tree) {
    return Tree ? Tree->color : 0;
  }

  int height(RBTree* Tree) {
    return !Tree ? 0 : (std::max(height(Tree->left), height(Tree->right)) + 1 - Tree->color);
  }

  int full_height(RBTree* Tree) {
    return Tree ? std::max(full_height(Tree->left), full_height(Tree->right)) + 1 : 0;
  }

  void ins_turning(RBTree*& N, RBTree*& P, RBTree*& G, RBTree*& U) {
    if (G->parent) {
      RBTree* GG = G->parent;
      if (G->data < GG->data)
        GG->left = P;
      else
        GG->right = P;
    }
    P->parent = G->parent;

    if (P == G->left) {
      RBTree* S = P->right;

      P->left = N;
      if (N)
        N->parent = P;

      P->right = G;
      if (G)
        G->parent = P;

      G->right = U;
      if (U)
        U->parent = G;

      G->left = S;
      if (S)
        S->parent = G;
    }
    else {
      RBTree* S = P->left;

      P->right = N;
      if (N)
        N->parent = P;

      P->left = G;
      if (G)
        G->parent = P;

      G->left = U;
      if (U)
        U->parent = G;

      G->right = S;
      if (S)
        S->parent = G;
    }

    if (P)
      P->color = BLACK;
    if (G)
      G->color = RED;
    if (N)
      N->color = RED;
    return;
  }

  void ins_balance(RBTree* N) {
    RBTree* P = N->parent;
    if (!P) {
      N->color = BLACK;
      return;
    }

    if (color(N) != color(P))
      return;

    RBTree* G = P->parent;
    RBTree* U;
    if (P->data < G->data)
      U = G->right;
    else
      U = G->left;

    if (color(U) == RED) {
      U->color = BLACK;
      P->color = BLACK;
      G->color = RED;
      ins_balance(G);
      return;
    }
    if (P == G->left && N == P->left || P == G->right && N == P->right) {
      ins_turning(N, P, G, U);
      return;
    }
    if (N == P->right) {

      G->left = N;
      N->parent = G;

      P->right = N->left;
      if (P->right)
        P->right->parent = P;

      N->left = P;
      P->parent = N;

      ins_turning(P, N, G, U);
      return;
    }

    G->right = N;
    N->parent = G;

    P->left = N->right;
    if (P->left)
      P->left->parent = P;

    N->right = P;
    P->parent = N;

    ins_turning(P, N, G, U);
    return;
  }


  void insert(RBTree*& Tree, int x, RBTree* P) {
    if (!Tree) {
      Tree = new RBTree;
      Tree->data = x;
      Tree->left = Tree->right = NULL;
      Tree->color = RED;
      Tree->parent = P;
      ins_balance(Tree);
      return;
    }
    if (x == Tree->data)
      return;
    if (x < Tree->data)
      insert(Tree->left, x, Tree);
    else
      insert(Tree->right, x, Tree);
    return;
  }

  void insert(RBTree*& Tree, int x) {
    insert(Tree, x, NULL);
    while (Tree->parent != NULL)
      Tree = Tree->parent;
    return;
  }

  RBTree* find_del_tree(RBTree* Tree, int data) {
    if (!Tree)
      return NULL;
    if (Tree->data == data)
      return Tree;
    if (data < Tree->data)
      return find_del_tree(Tree->left, data);
    return find_del_tree(Tree->right, data);
  }

  RBTree* find_change_tree(RBTree* Tree) {
    if (!Tree)
      return NULL;
    if (!Tree->left)
      return Tree;
    return find_change_tree(Tree->left);
  }


  void del_modification(RBTree* N) {
    RBTree* P = N->parent;
    if (!P)
      return;
    RBTree* S;
    if (N == P->left) {
      S = P->right;

      if (color(S) == RED) {
        RBTree* G;
        G = P->parent;

        if (G) {
          if (G->left == P)
            G->left = S;
          else
            G->right = S;
        }

        S->parent = G;

        P->right = S->left;
        if (P->right)
          P->right->parent = P;

        S->left = P;
        P->parent = S;

        S->color = BLACK;
        P->color = RED;
        del_modification(N);
        return;
      }

      if (color(S->left) == BLACK && color(S->right) == BLACK) {
        bool rec = color(P) == BLACK;
        P->color = BLACK;
        S->color = RED;
        if (rec)
          del_modification(P);
        return;
      }

      if (color(S->left) == RED && color(S->right) == BLACK) {
        S->left->color = BLACK;
        S->color = RED;

        P->right = S->left;
        if (P->right)
          P->right->parent = P;

        S->left = P->right->right;
        if (S->left)
          S->left->parent = S;

        P->right->right = S;
        S->parent = P->right;

        del_modification(N);
        return;
      }

      RBTree* G;
      G = P->parent;

      if (G) {
        if (G->left == P)
          G->left = S;
        else
          G->right = S;
      }

      S->color = P->color;
      S->right->color = BLACK;
      P->color = BLACK;

      S->parent = P->parent;

      P->right = S->left;
      if (P->right)
        P->right->parent = P;

      S->left = P;
      P->parent = S;

      return;
    }
    else {
      S = P->left;

      if (color(S) == RED) {
        RBTree* G;
        G = P->parent;

        if (G) {
          if (G->right == P)
            G->right = S;
          else
            G->left = S;
        }

        S->parent = G;

        P->left = S->right;
        if (P->left)
          P->left->parent = P;

        S->right = P;
        P->parent = S;

        S->color = BLACK;
        P->color = RED;
        del_modification(N);
        return;
      }

      if (color(S->right) == BLACK && color(S->left) == BLACK) {
        bool rec = color(P) == BLACK;
        P->color = BLACK;
        S->color = RED;
        if (rec)
          del_modification(P);
        return;
      }

      if (color(S->right) == RED && color(S->left) == BLACK) {
        S->right->color = BLACK;
        S->color = RED;

        P->left = S->right;
        if (P->left)
          P->left->parent = P;

        S->right = P->left->left;
        if (S->right)
          S->right->parent = S;

        P->left->left = S;
        S->parent = P->left;

        del_modification(N);
        return;
      }

      RBTree* G;
      G = P->parent;

      if (G) {
        if (G->right == P)
          G->right = S;
        else
          G->left = S;
      }

      S->color = P->color;
      S->left->color = BLACK;
      P->color = BLACK;

      S->parent = P->parent;

      P->left = S->right;
      if (P->left)
        P->left->parent = P;

      S->right = P;
      P->parent = S;

      return;
    }
  }

  void del(RBTree*& Tree, int data) {
    if (!Tree)
      return;
    RBTree* delTree = find_del_tree(Tree, data);
    if (!delTree)
      return;
    RBTree* changeTree = find_change_tree(delTree->right);
    if (changeTree == NULL)
      changeTree = delTree;
    std::swap(delTree->data, changeTree->data);
    if (changeTree->left) {
      if (changeTree->parent) {
        if (changeTree->parent->left == changeTree) {
          changeTree->parent->left = changeTree->left;
        }
        else {
          changeTree->parent->right = changeTree->left;
        }
      }
      else {
        Tree = changeTree->left;
      }
      changeTree->left->color = BLACK;
      changeTree->left->parent = changeTree->parent;
      delete(changeTree);
      return;
    }
    if (color(changeTree) == RED) {
      if (changeTree->parent) {
        if (changeTree->parent->left == changeTree) {
          changeTree->parent->left = NULL;
        }
        else {
          changeTree->parent->right = NULL;
        }
      }
      delete(changeTree);
      return;
    }
    del_modification(changeTree);
    if (changeTree->parent) {
      if (changeTree->parent->left == changeTree) {
        changeTree->parent->left = NULL;
      }
      else {
        changeTree->parent->right = NULL;
      }
    }
    if (changeTree == Tree) {
      Tree = NULL;
    }
    delete(changeTree);
    while (Tree != NULL && Tree->parent != NULL)
      Tree = Tree->parent;
    return;
  }

  void out(RBTree* Tree) {
    if (!Tree)
      return;
    out(Tree->left);
    std::cout << Tree->data << "/" << Tree->color << ' ';
    out(Tree->right);
    return;
  }

  bool check(RBTree* Tree) {
    if (!Tree)
      return true;
    if (Tree->parent && (Tree != Tree->parent->left && Tree != Tree->parent->right) || height(Tree->left) != height(Tree->right) || (Tree->left && Tree->right && Tree->left->data > Tree->right->data)) {
      std::cout << "BAAAAAAAAAAAAAAAAD\n";
      return false;
    }
    return check(Tree->left) && check(Tree->right);
  }

}

