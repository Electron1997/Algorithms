// Strangely this solution is too slow
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
constexpr size_t N = 5e5, M = 1000;
 
vector<int> adj[N];
bool merged[N], visited[M] = {false};
int nid[N], inv[N], complement_adj[M][M] = {0};
 
// Solution based on trick described here https://codeforces.com/blog/entry/79880#comment-658132
 
// Time: O(n + m)
int merge_low_deg_node(int n){
	int ldn = 0, ld = INT_MAX;
	loop(v, n){
		if(adj[v].size() < ld){
			ldn = v;
			ld = adj[v].size();
		}
	}
	// cout << ldn << endl;
	loop(v, n) merged[v] = true;
	for(int v : adj[ldn]) merged[v] = false;
	int id = 1;
	loop(v, n){
		if(merged[v]) nid[v] = 0;
		else{
			nid[v] = id;
			inv[id] = v;
			++id;
		}
	}
	loop(u, n){
		for(int v : adj[u]){
			complement_adj[nid[u]][nid[v]] += 1;
		}
	}
	loop(u, id){
		loop(v, id){
			if(!u || !v){
				if(complement_adj[u][v] == n - ld) complement_adj[u][v] = 0;
			}else{
				complement_adj[u][v] = !complement_adj[u][v];
			}
		}
	}
	return id;
}
 
// Time: O(n + m)
void complement_dfs(int v, vector<int>& component, int nn){
	visited[v] = true;
	if(v) component.push_back(inv[v]);
	loop(u, nn){
		if(!visited[u] && complement_adj[v][u]) complement_dfs(u, component, nn);
	}
}
 
// Time: O(n + m)
inline vector<vector<int>> complement_connected_components(int n){
    int nn = merge_low_deg_node(n);	// Computes complement adjacency matrix after merging low deg node
	/*
	show(merged, n);
	show(nid, n);
	loop(i, nn){
		show(complement_adj[i], nn);
	}*/
	vector<vector<int>> components;
    loop(v, nn){
		if(!visited[v]){
			vector<int> component;
			if(!v){
				loop(u, n){
					if(merged[u]) component.push_back(u);
				}
			}
        	complement_dfs(v, component, nn);
        	components.emplace_back(component);
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
 
	int n, m; scanf("%d %d", &n, &m);
    loop(i, m){
    	int u, v; scanf("%d %d", &u, &v); --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    auto components = complement_connected_components(n);
	printf("%d\n", components.size());
   	for(auto component : components){
		printf("%d ", component.size());
        for(auto v : component) printf("%d ", v + 1);
        printf("\n");
    }
 
    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
