// Solution for https://cses.fi/problemset/task/1683
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

// max number of nodes in directed graph
constexpr size_t N = 2e5;

vector<int> adj[N];
set<int> adj_scc[N]; // condensation DAG

// in_order[v]: number of nodes that have been visited before v plus 1
// low[v]: lowest index of a node u that can be reached from v using forward edges and at most one backward edge
// ind: counter for index
// index[v] == low[v] --> v is the root of a scc
int comp, ind, in_order[N], low[N], scc[N];

// node v active iff v has been reached but not exited by dfs
bool active[N];
stack<int> st;

void dfs(int v){
    active[v] = true;
    st.push(v);
    in_order[v] = low[v] = ind++;
    for(int u : adj[v]){
        if(!in_order[u]){
            dfs(u);
            low[v] = min(low[v], low[u]);
        }else if(active[u]){
            low[v] = min(low[v], in_order[u]);
        }
    }
    if(in_order[v] == low[v]){
        while(st.top() != v){
            scc[st.top()] = comp;
            active[st.top()] = false;
            st.pop();
        }
        scc[v] = comp++;
        st.pop();
        active[v] = false;
    }
}

void tarjan(int n){
    loop(v, n) active[v] = false;
    loop(v, n) in_order[v] = 0;
    comp = 1, ind = 1;
    loop(v, n){
        if(!in_order[v]){
            dfs(v);
        }
    }
}

void compute_condensation_DAG(int n){
    loop(v, n){
        for(int u : adj[v]){
            adj_scc[scc[v]].insert(scc[u]);
        }
    }
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
    }
    tarjan(n);
    cout << comp - 1 << endl;
    show(scc, n);

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
