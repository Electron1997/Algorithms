// Solution to https://codeforces.com/problemset/problem/920/E
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

set<int> adj[N], unvis;
int lbl[N], sz[N] = {0};

void dfs(int s, int id){
    // Could check, but a bit slower
    unvis.erase(s);
    lbl[s] = id;
    auto it = unvis.begin();
    if(it == unvis.end()) return;
    int v = *it;
    while(true){
        if(!adj[s].count(v)){
            dfs(v, id);
        }
        // Number of skips is in O(m)!
        auto it = unvis.upper_bound(v);
        if(it == unvis.end()) break;
        v = *it;
    }
}

// Time: O((n + m)log(n))
inline int count_components(int n){
    loop(i, n) unvis.insert(i);
    int cnt = 0;
    while(unvis.size()){
        dfs(*unvis.begin(), cnt);
        ++cnt;
    }
    return cnt;
}

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    int n, m; cin >> n >> m;
    loop(i, m){
        int u, v; cin >> u >> v; --u; --v;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    int cnt = count_components(n);
    loop(i, n){
        ++sz[lbl[i]];
    }
    sort(sz, sz + cnt);
    cout << cnt << endl;
    show(sz, cnt);

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
