#include <bits/stdc++.h>
#define ll long long

using namespace std;

class ST
{
public:

  void cria(vector<int> &segtree, vector<int> &v, int n)
  {
    for (int i = 0; i < n; i++)
      segtree[n + i] = v[i];
    for (int i = n - 1; i >= 1; i--)
      segtree[i] = segtree[2 * i] + segtree[2 * i + 1];
  }

  void insere(vector<int> &segtree, int pos, int valor, int n)
  {
    pos += n;
    segtree[pos] = valor;
    while (pos > 1) 
    {
      pos >>= 1;
      segtree[pos] = segtree[2 * pos] + segtree[2 * pos + 1];
    }
  }

  int rsq(vector<int> &segtree, int left, int right, int n)
  {
    int s = 0;
    left += n;
    right += n;
    while (left < right) 
    {
      if (left & 1) 
      {
        s = s + segtree[left];
        left++;
      }
      if (right & 1) 
      {
        right--;
        s = s + segtree[right];
      }
      left /= 2;
      right /= 2;
    }
    return s;
  }
};
