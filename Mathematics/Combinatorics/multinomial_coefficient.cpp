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

const int N = 1e5;
const ull MOD = 1e9 + 7; // Must be prime for inverse

ull factorial[N + 1];

inline void precompute_factorials(int n = N, ull mod = MOD){
    factorial[0] = factorial[1] = 1;
    for(int i = 2; i <= n; ++i){
        factorial[i] = factorial[i - 1] * i % mod;
    }
}

inline ull bin_exp(ull base, ull exp, ull mod = MOD){
    ull acc = 1;
    while(exp){
        if(exp & 1){
            acc = acc * base % mod;
        }
        base = base * base % mod;
        exp >>= 1;
    }
    return acc;
}

inline ull inverse(ull n, ull mod = MOD){
    return bin_exp(n, mod - 2);
}

inline ull binomial_coefficient(int n, int k, ull mod = MOD){
    if(k > n) return 0;
    ull den = factorial[k] * factorial[n - k] % mod;
    return factorial[n] * inverse(den, mod) % mod;
}

// ks must sum to n
inline ull multinomial_coefficient(int n, vector<int>& ks, ull mod = MOD){
    ull den = 1;
    for(ull k : ks){
        den = den * factorial[k] % mod;
    }
    return factorial[n] * inverse(den, mod) % mod;
}

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    int n, m; cin >> n >> m;
    precompute_factorials(n - m);
    vector<int> lights(m), gaps;
    read(lights, m);
    sort(lights.begin(), lights.end());
    int prev = 0, exp = 0;
    loop(i, m){
        int gap = lights[i] - prev - 1;
        if(gap){
            gaps.push_back(gap);
            if(i){
                exp += gap - 1;
            }
        }
        prev = lights[i];
    }
    gaps.push_back(n - prev);
    cout << multinomial_coefficient(n - m, gaps) * bin_exp(2, exp) % MOD << endl;

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
