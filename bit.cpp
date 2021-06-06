#include <iostream>
#include <string.h>

const int NMAX = 100000;

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

  int soma(int indice)
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
