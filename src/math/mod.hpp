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
