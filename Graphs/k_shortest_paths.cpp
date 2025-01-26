// Solution to https://cses.fi/problemset/task/1196/
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

constexpr size_t N = 1e5, K = 10;

vector<pair<ull, int>> adj[N];

int cnt[N] = {0};
ull d[N][K];

// Time: O(k(n + m)log(n)), maybe even O(knlog(n) + km)
// ASSUMES k DISTINCT PATHS FROM s TO t EXIST
void k_shortest_paths(int s, int t, int k, int n){
	priority_queue<pair<ull, int>, vector<pair<ull, int>>, greater<pair<ull, int>>> heap;
	heap.push({0, s});
	while(cnt[t] < k){
		pair<ull, int> v = heap.top();
		// show(cnt, n);
		heap.pop();
		if(cnt[v.s] < k){
			d[v.s][cnt[v.s]++] = v.f;
			for(pair<ull, int> u : adj[v.s]){
				if(cnt[u.s] != k){
					heap.push({v.f + u.f, u.s});
				}
			}
		}
	}
}

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)
	
	int n, m, k; cin >> n >> m >> k;
	loop(i, m){
		int u, v; ull c; cin >> u >> v >> c;
		adj[--u].push_back({c, --v});
	}
	k_shortest_paths(0, n - 1, k, n);
	loop(i, k){
		cout << d[n - 1][i] << " ";
	}
	cout << endl;
	
    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
