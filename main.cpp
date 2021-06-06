#include <stdio.h>
//#include <iostream>
//#include <string.h>
#include <vector>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <bit.cpp>

using namespace std;
using namespace std::chrono;

int main(int argc, char **argv)
{
  BIT bit;
  double tInsere = 0, tSoma = 0, tSomaNaive = 0;
  
  int runs = 10;
  for (int r=0; r<runs; r++)
  {
    cout << r << "/" << runs << endl;
    
    vector<int> v(1000);
    auto f = []() -> int {return rand() % 1000;};
    generate(v.begin(), v.end(), f);
    
    auto startInsere = high_resolution_clock::now();
    for(unsigned int i=1; i<=v.size(); i++) 
      bit.insere(i, v[i]);
    auto stopInsere = high_resolution_clock::now();
    auto t1 = duration_cast<microseconds>(stopInsere - startInsere);
    tInsere += t1.count();
    
    auto startSoma = high_resolution_clock::now();
    for(unsigned int i=1; i<=v.size(); i++) 
      bit.soma(i);
    auto stopSoma = high_resolution_clock::now();
    auto t2 = duration_cast<microseconds>(stopSoma - startSoma);
    tSoma += t2.count();

    auto startSomaNaive = high_resolution_clock::now();
    for(unsigned int i=1; i<=v.size(); i++) 
      accumulate(v.begin(), v.begin() + i, 0);
    auto stopSomaNaive = high_resolution_clock::now();
    auto t3 = duration_cast<microseconds>(stopSomaNaive - startSomaNaive);
    tSomaNaive += t3.count();
  }
  
  cout << "Tempo médio (us)" << endl;
  cout << "  Insere BIT: " << tInsere / runs << endl;
  cout << "  Soma BIT: " << tSoma / runs << endl;
  cout << "  Soma accumulate: " << tSomaNaive / runs << endl;
  
//  int posicao = 4;
//  int valor = 7;
//  bit.insere(posicao, valor - v[posicao]);
  
//  cout << bit.soma(v.size()) << endl;
//  cout << bit.soma(v.size()) - bit.soma(floor(v.size() / 2)) << endl;
  
  return 0;
}
