// Solution to https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=364

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

typedef ll c_type;

const c_type ZERO = 0, INF = LLONG_MAX / 2;

struct edge{
    int u, v;
    c_type w;
};

const int N = 100;

c_type dist[N];
vector<edge> edges;

void bellman_ford(int s = 0, int n = N){
    for(int i = 0; i < n; ++i){
        dist[i] = INF;
    }
    dist[s] = 0;
    for(int i = 0; i < n; ++i){
        for(edge e : edges){
            dist[e.u] = min(dist[e.u], dist[e.v] + e.w);
            dist[e.v] = min(dist[e.v], dist[e.u] + e.w);  // undirected edges
        }
    }
}

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    int n;
    cin >> n;
    loop(i, n - 1){
        loop(j, i + 1){
            string w;
            cin >> w;
            if(w != "x"){
                edges.push_back({i + 1, j, stoll(w)});
            }
        }
    }

    bellman_ford(0, n);

    ll sol = 0;
    loop(i, n){
        sol = max(sol, dist[i]);
    }

    cout << sol << endl;

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
