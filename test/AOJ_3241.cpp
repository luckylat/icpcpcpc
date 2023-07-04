// verification-helper: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/3241

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll MOD = 998244353;

ll f(ll n) {
  n %= MOD;
  n += MOD;
  n %= MOD;
  return n;
}

ll modmul(ll a, ll b) {
  return f(a * b);
}

ll modadd(ll a, ll b) {
  return f(a + b);
}

ll modpow(ll a, ll b) {
  ll res = 1;
  while (b) {
    if (b & 1) {
      res = modmul(res, a);
    }
    a = modmul(a, a);
    b >>= 1;
  }
  return res;
}

ll modinv(ll a) {
  return modpow(a, MOD - 2);
}

ll moddiv(ll a, ll b) {
  return modmul(a, modinv(b));
}

int main() {
  ll t;
  cin >> t;

  vector<ll> dp(t + 1, 0);
  for (int i = 0; i < t; i++) {
    dp[i + 1] = modadd(dp[i], modinv(i + 1 + 1));
  }

  cout << dp[t] << endl;
}
