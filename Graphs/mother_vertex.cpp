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

const int N = 10000;

vector<int> G[N];
bool visited[N];

void dfs(int v){
    visited[v] = true;
    for(int u : G[v]){
        if(!visited[u]){
            dfs(u);
        }
    }
}

int mother_vertex(int n = N){
    memset(visited, false, n * sizeof(visited[0]));
    int s;
    for(int v = 0; v < n; ++v){
        if(!visited[v]){
            s = v;
            dfs(v);
        }
    }
    return s;
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
        loop(i, m){
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);  // Need reversed graph
        }
        cout << mother_vertex(n) << endl;
    }

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
