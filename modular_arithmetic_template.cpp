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

/*  // SET WITH INDEXING
// Implements logarithmic find_by_order() and order_of_key()
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;
*/

/*  // RANDOM NUMBER GENERATOR
// rng() generates u.a.r. from [0, 2^32 - 1]
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
*/

constexpr ull MOD = 998244353;

inline ull add(ull a, ull b){
    return (a + b) % MOD; 
}
inline ull neg(ull a){
    return MOD - a;
}
inline ull sub(ull a, ull b){
    return add(a, neg(b));
}
inline ull mul(ull a, ull b){
    return a * b % MOD;
}
inline ull pow(ull a, ull b){
    ull p = 1;
    while(b){
        if(b & 1){
            p = mul(p, a);
        }
        a = mul(a, a);
        b >>= 1;
    }
    return p;
}
inline ull inv(ull a){
    return pow(a, MOD - 2);
}
inline ull div(ull a, ull b){
    return mul(a, inv(b));
}

constexpr size_t N = 1e5, M = 3e5;

ull a[N], f[M + 1];

inline ull aux_f(int i){
    if(i < 0) return 0;
    return f[i];
}

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)
    
    int n; cin >> n;
    ull s = 0;
    loop(i, n){
        cin >> a[i];
        s += a[i];
    }
    for(int i = 0; i <= M; ++i){
        ull b = sub(add(1, aux_f(i - 1)), aux_f(i - 2));
        ull c = div(mul(sub(i, 1), n - 1), s + 1 - i);
        f[i] = add(mul(b, c), aux_f(i - 1));
    }
    ull lo = 0;
    loop(i, n){
        lo = add(lo, f[a[i]]);
    }
    ull hi = add(f[s], mul(n - 1, f[0]));
    cout << sub(hi, lo) << endl;

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
