// Solution to https://cses.fi/problemset/task/1688
#include <atcoder/dsu>
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

// Offline algorithm for q LCA queries on a tree with n nodes
// Time complexity: O(n + q)
constexpr size_t N = 2e5;

vector<int> adj[N];
vector<pair<int, int>> que[N];

int anc[N], sol[N], vis[N] = {0};

atcoder::dsu dsu;

void dfs(int s){
	vis[s] = 1;
	anc[s] = s;
	for(int v : adj[s]){
		if(!vis[v]){
			dfs(v);
			anc[dsu.merge(v, s)] = s;
		}
	}
	for(pair<int, int> other : que[s]){
		if(vis[other.f]){
			sol[other.s] = anc[dsu.leader(other.f)];
		}
	}
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
	loop(i, q){
		int a, b; cin >> a >> b; --a, --b;
		que[a].push_back({b, i});
		que[b].push_back({a, i});
	}
	dsu = atcoder::dsu(n);
	dfs(0);
	loop(i, q) cout << sol[i] + 1 << endl;
	cout << endl;

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
