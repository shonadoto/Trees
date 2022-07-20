#ifndef KUREVO_H
#define KUREVO_H

#include "iostream"
#include "QRandomGenerator"
#include "algorithm"
#include "vector"
#include "time.h"

extern std::random_device rd;
extern std::mt19937 mersenne;

namespace Kurevo {

  struct kurevo {
    int key, prior, height;
    kurevo* left, * right;
  };
  int height(kurevo* Tree);

  void Recalc(kurevo* Tree);

  kurevo* Merge(kurevo* TF, kurevo* TS);

  std::vector<kurevo*> Split(kurevo* Tree, int key);

  void Insert(kurevo*& Tree, int data);

  void Delete(kurevo*& Tree, int data);
  void Out(kurevo*& Tree);
}


#endif // KUREVO_H
