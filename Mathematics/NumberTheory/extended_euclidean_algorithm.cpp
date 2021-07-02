// Solution to https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=364

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

// Time: O(log(ab))
tuple<ll, ll, ll> extended_euclidean_algorithm(ll r_0, ll r_1){
    ll s_0 = 1, s_1 = 0, t_0 = 0, t_1 = 1, q, u;
    /*
    if(r_0 < r_1){
        swap(r_0, r_1);     // r_0 must be >= r_1 !!!
    }
    */
    while(r_1){
        q = r_0 / r_1;
        u = r_0 - q * r_1;
        r_0 = r_1;
        r_1 = u;
        u = s_0 - q * s_1;
        s_0 = s_1;
        s_1 = u;
        u = t_0 - q * t_1;
        t_0 = t_1;
        t_1 = u;
    }
    return {r_0, s_0, t_0};
}

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    int T;
    cin >> T;
    loop(t, T){
        ll n, m;
        cin >> n >> m;
        tuple<ll, ll, ll> r = extended_euclidean_algorithm(n, m);
        cout << get<0>(r) << " " << get<1>(r) << " " << get<2>(r) << endl;
    }

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
