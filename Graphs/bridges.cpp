// Solution to https://www.spoj.com/problems/EC_P

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

const int N = 1005;

int id, in[N];

vector<int> graph[N];

set<pair<int, int> > bridges;

int dfs(int v, int par){
    int low = in[v] = id++;
    for(int u : graph[v]){
        if(!in[u]){ 
            int lo = dfs(u, v);
            if(lo > in[v]){
                bridges.insert({min(u, v), max(u, v)});
            }
            low = min(low, lo);
        }else if(u != par){
            low = min(low, in[u]);
        }
    }
    return low;
}

void compute_bridges(int n = N){
    bridges.clear();
    id = 1;
    memset(in, 0, n * sizeof(int));
    dfs(0, -1);
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
        int n, m;
        cin >> n >> m;
        loop(i, n){
            graph[i].clear();
        }
        loop(i, m){
            int u, v;
            cin >> u >> v;
            graph[u - 1].push_back(v - 1);
            graph[v - 1].push_back(u - 1);
        }
        compute_bridges(n);
        cout << "Caso #" << t + 1 << endl;
        if(bridges.size()){
            cout << bridges.size() << endl;
            for(pair<int, int> e : bridges){
                cout << e.f + 1 << " " << e.s + 1 << endl;
            }
        }else{
            cout << "Sin bloqueos" << endl;
        }
    }


    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
