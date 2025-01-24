// Solution to https://codeforces.com/problemset/problem/190/E
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
constexpr size_t N = 5e5;
 
vector<int> adj[N];
int blocked[N] = {0};
vector<int> unvisited;
 
// Time: O(n + m)
inline vector<int> complement_bfs(int s){
	vector<int> component;
	queue<int> q;
	q.push(s);
	while(q.size()){
		int v = q.front();
		component.push_back(v);
		q.pop();
		vector<int> new_unvisited;
		for(int u : unvisited) blocked[u] = 1;
		for(int u : adj[v]) blocked[u] = 0;
		for(int u : unvisited){
			if(blocked[u]) q.push(u);
			else new_unvisited.push_back(u);
			blocked[u] = 0;
		}
		unvisited = new_unvisited;
	}
	return component;
}

// Time: O(n + m)
inline vector<vector<int>> complement_connected_components(int n){
	loop(v, n) unvisited.push_back(v);
	vector<vector<int>> components;
	loop(v, n){
		if(unvisited.size()){
			int s = unvisited.back();
			unvisited.pop_back();
			components.push_back(complement_bfs(s));
		}
	}
	return components;
}
 
int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)
 
	int n, m; cin >> n >> m;
    loop(i, m){
    	int u, v; cin >> u >> v; --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    auto components = complement_connected_components(n);
	cout << components.size() << endl;
   	for(auto component : components){
		cout <<  component.size() << " ";
        for(auto v : component) cout << v + 1 << " ";
		cout << endl;
    }
 
    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
