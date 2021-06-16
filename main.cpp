#include <stdio.h>
#include <vector>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <numeric>

#include <bit.cpp>
#include <segtree.cpp>

using namespace std;
using namespace std::chrono;

int main(int argc, char **argv)
{
  int n = 1000;
  
  BIT bit;
  ST st;
  double tInsereBIT = 0, tSomaBIT1 = 0, tSomaBIT2 = 0;
  double tInsereST = 0, tSomaST1 = 0, tSomaST2 = 0;
  double tSomaNaive1 = 0, tSomaNaive2 = 0;
  
  int runs = 10;
  for (int r=0; r<runs; r++)
  {
    cout << r << "/" << runs << endl;
    
    vector<int> v(n);
    auto f = [&n]() -> int {return rand() % n;};
    generate(v.begin(), v.end(), f);
    
    auto startInsereBIT = high_resolution_clock::now();
    for(unsigned int i=1; i<=v.size(); i++) 
      bit.insere(i, v[i]);
    auto stopInsereBIT = high_resolution_clock::now();
    auto t1 = duration_cast<microseconds>(stopInsereBIT - startInsereBIT);
    tInsereBIT += t1.count();
    
    auto startSomaBIT1 = high_resolution_clock::now();
    for(unsigned int i=1; i<=v.size(); i++) 
      bit.rsq(i);
    auto stopSomaBIT1 = high_resolution_clock::now();
    auto t2 = duration_cast<microseconds>(stopSomaBIT1 - startSomaBIT1);
    tSomaBIT1 += t2.count();
    
    auto startSomaBIT2 = high_resolution_clock::now();
    for(unsigned int i=1; i<v.size(); i++) 
    {
      bit.rsq(v.size());
      bit.rsq(i);
    }
    auto stopSomaBIT2 = high_resolution_clock::now();
    auto t3 = duration_cast<microseconds>(stopSomaBIT2 - startSomaBIT2);
    tSomaBIT2 += t3.count();
    
    auto startInsereST = high_resolution_clock::now();
    vector<int> segtree(2 * n);
    st.cria(segtree, v, n);
    auto stopInsereST = high_resolution_clock::now();
    auto t4 = duration_cast<microseconds>(stopInsereST - startInsereST);
    tInsereST += t4.count();
    
    auto startSomaST1 = high_resolution_clock::now();
    for(unsigned int i=1; i<=v.size(); i++) 
      st.rsq(segtree, 0, i, n);
    auto stopSomaST1 = high_resolution_clock::now();
    auto t5 = duration_cast<microseconds>(stopSomaST1 - startSomaST1);
    tSomaST1 += t5.count();
    
    auto startSomaST2 = high_resolution_clock::now();
    for(unsigned int i=1; i<v.size(); i++) 
      st.rsq(segtree, i, n, n);
    auto stopSomaST2 = high_resolution_clock::now();
    auto t6 = duration_cast<microseconds>(stopSomaST2 - startSomaST2);
    tSomaST2 += t6.count();

    auto startSomaNaive1 = high_resolution_clock::now();
    for(unsigned int i=1; i<=v.size(); i++) 
      accumulate(v.begin(), v.begin() + i, 0);
    auto stopSomaNaive1 = high_resolution_clock::now();
    auto t7 = duration_cast<microseconds>(stopSomaNaive1 - startSomaNaive1);
    tSomaNaive1 += t7.count();
    
    auto startSomaNaive2 = high_resolution_clock::now();
    for(unsigned int i=1; i<v.size(); i++) 
      accumulate(v.begin() + i, v.end(), 0);
    auto stopSomaNaive2 = high_resolution_clock::now();
    auto t8 = duration_cast<microseconds>(stopSomaNaive2 - startSomaNaive2);
    tSomaNaive2 += t8.count();
    
//    for (int i=0; i<10; i++)
//      printf("%d ", v[i]);
//    printf("\n%d\n", bit.soma(9));
//    printf("%d\n", segtree.getSum(st, n, 1, 9));
  }
  
  cout << "n = " << n << endl;
  cout << "Tempo médio (us)" << endl;
  cout << "  Insere BIT: " << tInsereBIT / runs << endl;
  cout << "  Soma BIT RSQ(0, r): " << tSomaBIT1 / runs << endl;
  cout << "  Soma BIT RSQ(l, n): " << tSomaBIT2 / runs << endl;  
  cout << "  Insere ST: " << tInsereST / runs << endl;
  cout << "  Soma ST RSQ(0, r): " << tSomaST1 / runs << endl;
  cout << "  Soma ST RSQ(l, n): " << tSomaST2 / runs << endl;
  cout << "  Soma naive: " << tSomaNaive1 / runs << endl;
  cout << "  Soma naive: " << tSomaNaive2 / runs << endl;
    
  return 0;
}
