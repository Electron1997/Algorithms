// Solution to https://www.spoj.com/problems/EZDIJKST

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

ull dist[N];
vector<pair<int, ull>> G[N];
priority_queue<pair<ull, int>, vector<pair<ull, int>>, greater<pair<ull, int>>> H;

// Returns the length of a shortest s-t-path in G (ULLONG_MAX if no s-t-path exists)
ull dijkstra(int s, int t, int n = N){
    H = priority_queue<pair<ull, int>, vector<pair<ull, int>>, greater<pair<ull, int>>>();
    for(int v = 0; v < n; ++v){
        dist[v] = ULLONG_MAX;
    }
    H.push({0, s});
    while(!H.empty()){
        pair<ull, int> p = H.top();
        H.pop();
        if(dist[p.second] > p.first){
            dist[p.second] = p.first;
            if(p.second == t){
                return p.first;
            }
            for(pair<int, ull> v : G[p.second]){
                H.push({p.first + v.second, v.first});
            }
        }
    }
    return ULLONG_MAX;
}

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    int T;
    cin >> T;
    loop($, T){
        int n, m;
        cin >> n >> m;
        loop(i, n){
            G[i].clear();
        }
        loop(i, m){
            int u, v, w;
            cin >> u >> v >> w;
            G[u - 1].push_back({v - 1, w});
        }
        int s, t;
        cin >> s >> t;
        ull d = dijkstra(s - 1, t - 1, n);
        if(d == ULLONG_MAX){
            cout << "NO" << endl;
        }else{
            cout << d << endl;
        }
    }

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
