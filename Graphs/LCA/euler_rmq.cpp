// Solution to https://cses.fi/problemset/task/1688
#include <atcoder/segtree>
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

/*
// SET WITH INDEXING
// Implements logarithmic find_by_order() and order_of_key()
// erase does not work with less_equal<T>!
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template<typename T>
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
*/

/*  // RANDOM NUMBER GENERATOR
// rng() generates u.a.r. from [0, 2^32 - 1]
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
*/

// Euler tour based algorithm with segtree
// Preprocessing complexity: O(n)
// Query complexity: O(log(n))
constexpr size_t N = 2e5;

vector<int> adj[N];

int first[N];

vector<pair<int, int>> euler;

pair<int, int> op(pair<int, int> a, pair<int, int> b){
	if(a.s < b.s) return a;
	return b;
}

pair<int, int> e(){
	return {0, INT_MAX};
}

atcoder::segtree<pair<int, int>, op, e> seg;

void dfs(int v, int p, int d){
	first[v] = euler.size();
	euler.push_back({v, d});
	for(int u : adj[v]){
		if(u != p){
			dfs(u, v, d + 1);
			euler.push_back({v, d});
		}
	}
}

void preprocessing(){
	dfs(0, -1, 0);
	seg = atcoder::segtree<pair<int, int>, op, e>(euler);
}

// Query
inline int lca(int u, int v){
	int i = first[u], j = first[v];
	if(i > j) swap(i, j);
	return seg.prod(i, j + 1).f;
}

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

	int n, q; cin >> n >> q;
	for(int u = 1; u < n; ++u){
		int v; cin >> v; --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	preprocessing();
	loop(i, q){
		int u, v; cin >> u >> v; --u, --v;
		cout << lca(u, v) + 1 << endl;
	}

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
