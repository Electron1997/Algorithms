// Solution to https://atcoder.jp/contests/abc367/submissions/me
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

constexpr size_t N = 2e5;

int b[N], q[N], aux[N], aux2[N];

// O(n)
inline void apply(int *a, int *p, int n){
    loop(i, n){
        aux[i] = a[p[i]];
    }
    loop(i, n){
        a[i] = aux[i];
    }
}

// O(nlog(k))
inline void binexp(int *p, int n, ull k){
    loop(i, n) aux2[i] = i;
    while(k){
        if(k & 1){
            apply(aux2, p, n);
        }
        apply(p, p, n);
        k >>= 1;
    }
    loop(i, n) p[i] = aux2[i];
}

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    int n; ull k; cin >> n >> k;
    read(q, n);
    loop(i, n) --q[i];
    binexp(q, n, k);
    read(b, n);
    loop(i, n) --b[i];
    apply(b, q, n);
    loop(i, n) ++b[i];
    show(b, n);

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
