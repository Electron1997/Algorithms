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

constexpr ull MOD = 1e9 + 7;

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

constexpr size_t N = 2500, M = 1e5;

ull a[N], t[M + 1];

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    int n; cin >> n;
    ull b = 0;
    loop(i, n){
        cin >> a[i];
        b += a[i];
    }
    ull acc = 0;
    for(int i = 1; i <= M; ++i){
        acc = add(acc, inv(b - i + 1));
        t[i] = mul(b - 1, mul(sub(b, i), acc));
    }
    ull sol = 0;
    loop(i, n){
        sol = add(sol, t[a[i]]);
    }
    cout << sol << endl;

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
