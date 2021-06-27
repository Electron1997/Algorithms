#include <bits/stdc++.h>

#define f first
#define s second
#define loop(i, n) for (int i = 0; i < n; ++i)
#define read(a, n) loop($, n) cin >> a[$];
#define show(a, n)                  \
    loop($, n) cout << a[$] << " "; \
    cout << endl;

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

/*  // RANDOM NUMBER GENERATOR
// rng() generates u.a.r. from [0, 2^32 - 1]
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
*/

ll power(ll base, ll exponent, ll modulo){
    ll p = 1;
    while(exponent){
        if(exponent & 1){
            p = (p * base) % modulo;
        }
        base = (base * base) % modulo;
        exponent >>= 1;
    }
    return p;
}

// Returns smallest x s.t. a^x = b (mod m) in O(sqrt(m)) (baby-step giant-step algorithm)
// base, rhs and modulo should be within [1, LLONG_MAX] with gcd(base, modulo) = 1
inline ll discrete_logarithm(ll base, ll rhs, ll modulo){
    base = base % modulo, rhs = rhs % modulo;
    if(rhs == 1){
        return 0;
    }
    ll n = sqrt(modulo) + 1;
    ll p = power(base, n, modulo), u = p, logarithm = LLONG_MAX;
    unordered_map<ll, ll> index;
    for(int i = 1; i <= n; ++i){
        if(index.count(u)){
            break;
        }
        index[u] = i;
        u = (u * p) % modulo;
    }
    for(int i = 0; i < n; ++i){
        if(index.count(rhs)){
            logarithm = min(logarithm, n * index[rhs] - i);
        }
        rhs = (rhs * base) % modulo;
    }
    if(logarithm == LLONG_MAX){
        logarithm = -1;   // logarithm does not exist
    }
    return logarithm;
}

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    ll a, m, b;
    while(true){
        cin >> a >> b >> m;
        if(a == 0){
            break;
        }
        ll log = discrete_logarithm(a, b, m);
        if(log == -1){
            cout << "No Solution" << endl;
        }else{
            cout << log << endl;
        }
    }

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
