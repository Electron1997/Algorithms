// Solution to https://www.spoj.com/problems/ROHAAN

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

const int N = 50;
const ll INF = LLONG_MAX / 2;

ll dist[N][N];

// dist must be initialized to adjacency matrix before calling this function (INF for no edge)
inline void floyd_warshall(int n = N){
    for(int v = 0; v < n; ++v){
        for(int s = 0; s < n; ++s){
            for(int t = 0; t < n; ++t){
                dist[s][t] = min(dist[s][t], dist[s][v] + dist[v][t]);
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

    int T;
    cin >> T;
    loop(t, T){
        int n;
        cin >> n;
        loop(i, n){
            loop(j, n){
                cin >> dist[i][j];
            }
        }
        floyd_warshall(n);
        ll sol = 0;
        int r;
        cin >> r;
        loop(i, r){
            int s, t;
            cin >> s >> t;
            sol += dist[s - 1][t - 1];
        }
        cout << "Case #" << t + 1 << ": " << sol << endl;
    }

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
