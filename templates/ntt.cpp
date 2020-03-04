#include <bits/stdc++.h>
using namespace std;
const int kMaxN = 1000000 + 10;
typedef long long LL;
const LL kMod = 998244353;
const LL kPriRoot = 3;
const LL kPriRootInv = 332748118;
inline LL FastPow(LL x, LL k) {
  LL ans = 1;
  for (; k; k >>= 1) {
    if (k & 1) ans = ans * x % kMod;
    x = x * x % kMod;
  }
  return ans;
}
inline LL FastAdd(LL x, LL y) {
  return (x += y) < kMod ? x : x - kMod;
}
inline LL FastDec(LL x, LL y) {
  return (x -= y) >= 0 ? x : x + kMod;
}
void RaderSort(LL* a, int n) { // Rader 排序的复杂度为 O(n)
  int j = 0;
  for (int i = 0; i < n; i++) {
    if (i < j) swap(a[i], a[j]);
    for (int l = (n >> 1); (j ^= l) < l; l >>= 1) continue;
  }
}
void Ntt(LL* a, int n, bool dft) {
  RaderSort(a, n);
  for (int len = 2; len <= n; len <<= 1) {
    LL unit = FastPow(dft ? kPriRoot : kPriRootInv, (kMod - 1) / len);
    for (int i = 0; i < n; i += len) {
      LL w = 1;
      int mid = i + (len >> 1);
      for (int j = 0; j < (len >> 1); j++) {
        LL tmp = w * a[mid + j] % kMod;
        a[mid + j] = FastDec(a[i + j], tmp);
        a[i + j] = FastAdd(a[i + j], tmp);
        w = w * unit % kMod;
      }
    }
  }
  if (!dft) {
    LL inv = FastPow(n, kMod - 2);
    for (int i = 0; i < n; i++)
      a[i] = a[i] * inv % kMod;
  }
}
int n, m, limit;
LL a[kMaxN << 2], b[kMaxN << 2];
int main() {
  scanf("%d %d", &n, &m);
  n++, m++;
  for (int i = 0; i < n; i++)
    scanf("%lld", &a[i]);
  for (int i = 0; i < m; i++)
    scanf("%lld", &b[i]);
  limit = 1;
  while (limit < n + m - 1) limit <<= 1;
  Ntt(a, limit, true);
  Ntt(b, limit, true);
  for (int i = 0; i < limit; i++)
    a[i] = a[i] * b[i] % kMod;
  Ntt(a, limit, false);
  for (int i = 0; i < n + m - 1; i++)
    printf("%lld ", a[i]);
  return 0;
}