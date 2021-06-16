#include <iostream>
#include <string.h>

const int NMAX = 1e6;

class BIT
{
public:
  int elementos[NMAX];
  
  void insere(int indice, int valor)
  {
    while(indice < NMAX)
    {
      elementos[indice] += valor;
      indice += (indice & -indice);
    }
  }

  int rsq(int indice)
  {
    int s = 0;
    while(indice > 0)
    {
      s += elementos[indice];
      indice -= (indice & -indice);
    }
    return s;
  }
};
