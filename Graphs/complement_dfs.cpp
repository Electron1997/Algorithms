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

set<int> adj[N], unvis;

// Time: O((n + m)log(n))
void complement_dfs(int s, vector<int>& component){
    unvis.erase(s);
	component.push_back(s);
    auto it = unvis.begin();
    if(it == unvis.end()) return;
    int v = *it;
    while(true){
        if(!adj[s].count(v)){
            complement_dfs(v, component);
        }
        // Number of skips is in O(m)
        auto it = unvis.upper_bound(v);
        if(it == unvis.end()) break;
        v = *it;
    }
}

// Time: O((n + m)log(n))
inline vector<vector<int>> complement_connected_components(int n){
    loop(i, n) unvis.insert(i);
    vector<vector<int>> components;
    while(unvis.size()){
		vector<int> component;
        complement_dfs(*unvis.begin(), component);
        components.push_back(component);
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
        adj[u].insert(v);
        adj[v].insert(u);
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
